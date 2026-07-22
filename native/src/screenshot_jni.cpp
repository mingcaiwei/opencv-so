// 截图实现：三种路径，按速度优先级尝试
//
// 路径 1：JNI 截图（~30ms）— 通过 JavaVM 调 LuaEngine.snapShot(IIII) 返回 Bitmap
//   需要 getJavaVM 成功。Android 7+ 的 namespace 限制可能导致 dlopen("libart.so") 失败，
//   用 RTLD_DEFAULT 绕过 + 多路径 dlopen 兜底。
//
// 路径 2：screencap 命令截图（~50ms）— popen("screencap") 读取 raw RGBA，imdecode 不需要
//   无文件 I/O、无 PNG 编解码，root 模式可用，不依赖 JavaVM
//
// 路径 3：返回 nullptr，Lua 屄走 snapShot(path) 文件法（~175ms）
//
// 关键坑：.so 由 LuaJIT ffi.load(dlopen) 加载，调用截图的线程是 native 线程，
// AttachCurrentThread 后 FindClass 用【系统 ClassLoader】，找不到应用类。
// 修复：先 FindClass 兜底，失败回退到 Thread.currentThread().getContextClassLoader().loadClass()。
#include "common.h"

#include <jni.h>
#include <android/bitmap.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstring>
#include <vector>

using GetCreatedJavaVMs_t = jint (*)(JavaVM **, jsize, jsize *);

// 全局错误信息（供 Lua 层诊断 JNI 截图失败原因）
static char g_lastError[256] = "no error";

static JavaVM *getJavaVM()
{
    auto fn = (GetCreatedJavaVMs_t)nullptr;

    // 方式 1：RTLD_DEFAULT 在所有已加载库中查找（绕过 Android 7+ namespace 限制）
    // libart.so 由 Android 运行时加载，符号已在进程符号空间中
    fn = (GetCreatedJavaVMs_t)dlsym(RTLD_DEFAULT, "JNI_GetCreatedJavaVMs");

    // 方式 2：dlopen 多个可能的 libart.so 路径（旧 Android 或 RTLD_DEFAULT 失败时）
    if (!fn)
    {
        const char *paths[] = {
            "libart.so",
            "/system/lib64/libart.so",
            "/system/lib/libart.so",
            "/apex/com.android.art/lib64/libart.so",
            "/apex/com.android.art/lib/libart.so",
            "libdvm.so",
        };
        for (auto path : paths)
        {
            void *handle = dlopen(path, RTLD_NOW);
            if (handle)
            {
                fn = (GetCreatedJavaVMs_t)dlsym(handle, "JNI_GetCreatedJavaVMs");
                if (fn) break;
            }
        }
    }

    if (!fn)
    {
        LOGE("JNI_GetCreatedJavaVMs not found (RTLD_DEFAULT + libart.so paths all failed)");
        return nullptr;
    }
    JavaVM *vm = nullptr;
    jsize n = 0;
    if (fn(&vm, 1, &n) != JNI_OK || n < 1)
    {
        LOGE("no JavaVM created");
        return nullptr;
    }
    return vm;
}

// 通过 Thread.currentThread().getContextClassLoader().loadClass(name) 加载类
static jclass findClassViaContextLoader(JNIEnv *env, const char *name)
{
    jclass threadCls = env->FindClass("java/lang/Thread");
    if (!threadCls) { env->ExceptionClear(); return nullptr; }
    jmethodID curMid       = env->GetStaticMethodID(threadCls, "currentThread", "()Ljava/lang/Thread;");
    jmethodID getCtxLoader = env->GetMethodID(threadCls, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
    if (!curMid || !getCtxLoader) { env->DeleteLocalRef(threadCls); return nullptr; }

    jobject thread = env->CallStaticObjectMethod(threadCls, curMid);
    env->DeleteLocalRef(threadCls);
    if (env->ExceptionCheck()) env->ExceptionClear();
    if (!thread) return nullptr;

    jobject loader = env->CallObjectMethod(thread, getCtxLoader);
    env->DeleteLocalRef(thread);
    if (env->ExceptionCheck()) env->ExceptionClear();
    if (!loader) return nullptr;

    jclass loaderCls = env->FindClass("java/lang/ClassLoader");
    if (!loaderCls) { env->ExceptionClear(); env->DeleteLocalRef(loader); return nullptr; }
    jmethodID loadClass = env->GetMethodID(loaderCls, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    env->DeleteLocalRef(loaderCls);
    if (!loadClass) { env->DeleteLocalRef(loader); return nullptr; }

    jstring jname = env->NewStringUTF(name);
    jclass cls = (jclass)env->CallObjectMethod(loader, loadClass, jname);
    env->DeleteLocalRef(jname);
    env->DeleteLocalRef(loader);
    if (env->ExceptionCheck()) env->ExceptionClear();
    return cls;
}

// 缓存：LuaEngine 类 + snapShot 方法 + Bitmap.recycle 方法
static jclass    g_luaEngineCls = nullptr;
static jmethodID g_snapMid      = nullptr;
static jmethodID g_recycleMid   = nullptr;

// 在 FFI native 线程上解析应用类 com.nx.assist.lua.LuaEngine + snapShot 方法
static bool resolveLuaEngine(JNIEnv *env)
{
    if (g_luaEngineCls && g_snapMid)
        return true;

    jclass cls = env->FindClass("com/nx/assist/lua/LuaEngine");
    if (!cls)
    {
        env->ExceptionClear();
        cls = findClassViaContextLoader(env, "com.nx.assist.lua.LuaEngine");
        if (!cls)
        {
            snprintf(g_lastError, sizeof(g_lastError),
                     "FindClass和contextClassLoader均找不到com.nx.assist.lua.LuaEngine");
            return false;
        }
    }

    jmethodID mid = env->GetStaticMethodID(cls, "snapShot", "(IIII)Landroid/graphics/Bitmap;");
    if (!mid)
    {
        env->ExceptionClear();
        snprintf(g_lastError, sizeof(g_lastError),
                 "找到LuaEngine类,但snapShot(IIII)Bitmap方法不存在(方法名或签名不对)");
        env->DeleteLocalRef(cls);
        return false;
    }

    jclass bmpCls = env->FindClass("android/graphics/Bitmap");
    if (bmpCls)
    {
        g_recycleMid = env->GetMethodID(bmpCls, "recycle", "()V");
        env->DeleteLocalRef(bmpCls);
    }
    if (env->ExceptionCheck()) env->ExceptionClear();

    g_luaEngineCls = (jclass)env->NewGlobalRef(cls);
    g_snapMid = mid;
    env->DeleteLocalRef(cls);
    snprintf(g_lastError, sizeof(g_lastError), "ok");
    return true;
}

// 路径 2：screencap 命令截图（root 模式，无需 JavaVM）
// screencap 不加 -p 输出 raw 数据：头部4个int(width,height,stride,format) + 像素数据
// format: 1=RGBA_8888(4字节), 2=RGB_565(2字节)
static void *screenshotViaScreencap(int x, int y, int x1, int y1)
{
    FILE *fp = popen("screencap", "r");
    if (!fp)
    {
        snprintf(g_lastError, sizeof(g_lastError), "screencap: popen失败(非root?)");
        return nullptr;
    }

    // 读取头部：width, height, stride, format
    int header[4] = {0, 0, 0, 0};
    if (fread(header, sizeof(int), 4, fp) != 4 || header[0] <= 0 || header[1] <= 0)
    {
        pclose(fp);
        snprintf(g_lastError, sizeof(g_lastError), "screencap: 读取头部失败");
        return nullptr;
    }
    int width  = header[0];
    int height = header[1];
    int stride = header[2] > 0 ? header[2] : width;
    int format = header[3]; // 1=RGBA_8888, 2=RGB_565

    int bpp = (format == 2) ? 2 : 4;
    size_t rowBytes   = (size_t)width  * bpp;
    size_t strideBytes = (size_t)stride * bpp;
    size_t pixelSize  = (size_t)height * rowBytes;

    std::vector<uchar> data(pixelSize);

    if (stride == width)
    {
        // stride == width，直接读取所有像素
        size_t read = 0;
        while (read < pixelSize)
        {
            size_t n = fread(data.data() + read, 1, pixelSize - read, fp);
            if (n == 0) break;
            read += n;
        }
        pclose(fp);
        if (read < pixelSize)
        {
            snprintf(g_lastError, sizeof(g_lastError), "screencap: 像素数据不完整(%zu/%zu)", read, pixelSize);
            return nullptr;
        }
    }
    else
    {
        // stride != width，逐行读取（跳过每行末尾 padding）
        std::vector<uchar> row(strideBytes);
        bool ok = true;
        for (int r = 0; r < height; r++)
        {
            if (fread(row.data(), 1, strideBytes, fp) != strideBytes) { ok = false; break; }
            memcpy(data.data() + (size_t)r * rowBytes, row.data(), rowBytes);
        }
        pclose(fp);
        if (!ok)
        {
            snprintf(g_lastError, sizeof(g_lastError), "screencap: 逐行读取失败(stride=%d)", stride);
            return nullptr;
        }
    }

    // 转换为 cv::Mat
    cv::Mat *mat = new cv::Mat();
    if (format == 2) // RGB_565
    {
        cv::Mat rgb565(height, width, CV_8UC2, data.data());
        cv::cvtColor(rgb565, *mat, cv::COLOR_BGR5652BGR);
    }
    else // RGBA_8888（最常见）
    {
        cv::Mat rgba(height, width, CV_8UC4, data.data());
        cv::cvtColor(rgba, *mat, cv::COLOR_RGBA2BGR);
    }

    if (mat->empty())
    {
        delete mat;
        snprintf(g_lastError, sizeof(g_lastError), "screencap: cvtColor后Mat为空");
        return nullptr;
    }

    // 区域裁剪
    if (x1 > x && y1 > y)
    {
        cv::Rect roi(x, y, x1 - x, y1 - y);
        if (roi.x >= 0 && roi.y >= 0 &&
            roi.x + roi.width <= mat->cols &&
            roi.y + roi.height <= mat->rows)
        {
            cv::Mat *cropped = new cv::Mat((*mat)(roi).clone());
            delete mat;
            snprintf(g_lastError, sizeof(g_lastError), "screencap ok");
            return fromMat(cropped);
        }
    }
    snprintf(g_lastError, sizeof(g_lastError), "screencap ok");
    return fromMat(mat);
}

void *screenshotImpl(int x, int y, int x1, int y1)
{
    // 路径 1：JNI 截图（最快 ~30ms）
    static JavaVM *vm = nullptr;
    if (!vm)
        vm = getJavaVM();

    void *result = nullptr;

    if (vm)
    {
        JNIEnv *env = nullptr;
        bool attached = false;
        if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
        {
            if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
            {
                LOGE("AttachCurrentThread failed");
                snprintf(g_lastError, sizeof(g_lastError), "AttachCurrentThread失败");
            }
            else
            {
                attached = true;
            }
        }

        if (env)
        {
            do
            {
                if (!resolveLuaEngine(env))
                {
                    LOGE("LuaEngine 解析失败: %s", g_lastError);
                    break;
                }

                jobject bmp = env->CallStaticObjectMethod(g_luaEngineCls, g_snapMid,
                                                           (jint)x, (jint)y, (jint)x1, (jint)y1);
                if (env->ExceptionCheck())
                {
                    env->ExceptionClear();
                    snprintf(g_lastError, sizeof(g_lastError), "LuaEngine.snapShot抛异常(截图服务未开启?)");
                    LOGE("LuaEngine.snapShot 抛出异常");
                }
                if (!bmp)
                {
                    snprintf(g_lastError, sizeof(g_lastError), "snapShot返回null(截图服务未开启或坐标越界)");
                    LOGE("snapShot 返回 null bitmap");
                    break;
                }

                AndroidBitmapInfo info;
                if (AndroidBitmap_getInfo(env, bmp, &info) != ANDROID_BITMAP_RESULT_SUCCESS)
                {
                    snprintf(g_lastError, sizeof(g_lastError), "AndroidBitmap_getInfo失败");
                    if (g_recycleMid) env->CallVoidMethod(bmp, g_recycleMid);
                    env->DeleteLocalRef(bmp);
                    break;
                }
                void *pixels = nullptr;
                if (AndroidBitmap_lockPixels(env, bmp, &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
                {
                    snprintf(g_lastError, sizeof(g_lastError), "AndroidBitmap_lockPixels失败");
                    if (g_recycleMid) env->CallVoidMethod(bmp, g_recycleMid);
                    env->DeleteLocalRef(bmp);
                    break;
                }

                cv::Mat *mat = new cv::Mat();
                if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
                {
                    cv::Mat rgba((int)info.height, (int)info.width, CV_8UC4, pixels);
                    cv::cvtColor(rgba, *mat, cv::COLOR_RGBA2BGR);
                }
                else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565)
                {
                    cv::Mat rgb565((int)info.height, (int)info.width, CV_8UC2, pixels);
                    cv::cvtColor(rgb565, *mat, cv::COLOR_BGR5652BGR);
                }
                else
                {
                    cv::Mat rgba((int)info.height, (int)info.width, CV_8UC4, pixels);
                    cv::cvtColor(rgba, *mat, cv::COLOR_RGBA2BGR);
                }
                AndroidBitmap_unlockPixels(env, bmp);

                if (g_recycleMid)
                {
                    if (env->ExceptionCheck()) env->ExceptionClear();
                    env->CallVoidMethod(bmp, g_recycleMid);
                    if (env->ExceptionCheck()) env->ExceptionClear();
                }
                env->DeleteLocalRef(bmp);

                if (mat->empty())
                {
                    delete mat;
                    snprintf(g_lastError, sizeof(g_lastError), "cvtColor后Mat为空");
                    result = nullptr;
                }
                else
                {
                    result = fromMat(mat);
                    snprintf(g_lastError, sizeof(g_lastError), "jni ok");
                }
            } while (0);

            if (attached)
                vm->DetachCurrentThread();
        }
    }
    else
    {
        snprintf(g_lastError, sizeof(g_lastError), "getJavaVM失败(dlopen libart.so或RTLD_DEFAULT)");
    }

    // 路径 2：screencap 命令截图（root 模式 ~50ms，无需 JavaVM）
    if (!result)
    {
        result = screenshotViaScreencap(x, y, x1, y1);
    }

    return result;
}

// 诊断：返回最近一次截图的错误信息
extern "C" const char *getScreenshotError()
{
    return g_lastError;
}

// 诊断：用 Java 反射列出 LuaEngine 类含 snap/capture/screen/bitmap 的方法
extern "C" const char *dumpLuaEngineMethods()
{
    static char buf[4096];
    buf[0] = 0;

    static JavaVM *vm = nullptr;
    if (!vm) vm = getJavaVM();
    if (!vm) { strcpy(buf, "no JavaVM"); return buf; }

    JNIEnv *env = nullptr;
    bool attached = false;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
    {
        if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        { strcpy(buf, "AttachCurrentThread failed"); return buf; }
        attached = true;
    }

    jclass cls = env->FindClass("com/nx/assist/lua/LuaEngine");
    if (!cls)
    {
        env->ExceptionClear();
        cls = findClassViaContextLoader(env, "com.nx.assist.lua.LuaEngine");
    }
    if (!cls)
    {
        if (env->ExceptionCheck()) env->ExceptionClear();
        strcpy(buf, "无法加载com.nx.assist.lua.LuaEngine类(FindClass和contextClassLoader均失败)");
        if (attached) vm->DetachCurrentThread();
        return buf;
    }

    jclass classCls = env->FindClass("java/lang/Class");
    if (classCls)
    {
        jmethodID getMethodsMid = env->GetMethodID(classCls, "getMethods", "()[Ljava/lang/reflect/Method;");
        jobjectArray methodsArray = (jobjectArray)env->CallObjectMethod(cls, getMethodsMid);
        if (env->ExceptionCheck()) env->ExceptionClear();

        if (methodsArray)
        {
            jclass methodCls = env->FindClass("java/lang/reflect/Method");
            if (methodCls)
            {
                jmethodID toStringMid = env->GetMethodID(methodCls, "toString", "()Ljava/lang/String;");
                jsize n = env->GetArrayLength(methodsArray);
                for (jsize i = 0; i < n; i++)
                {
                    jobject m = env->GetObjectArrayElement(methodsArray, i);
                    if (!m) continue;
                    jstring str = (jstring)env->CallObjectMethod(m, toStringMid);
                    if (env->ExceptionCheck()) env->ExceptionClear();
                    if (str)
                    {
                        const char *cstr = env->GetStringUTFChars(str, nullptr);
                        if (cstr)
                        {
                            if (strstr(cstr, "nap") || strstr(cstr, "apture") ||
                                strstr(cstr, "creen") || strstr(cstr, "itmap"))
                            {
                                strncat(buf, cstr, sizeof(buf) - strlen(buf) - 2);
                                strncat(buf, "\n", sizeof(buf) - strlen(buf) - 1);
                            }
                            env->ReleaseStringUTFChars(str, cstr);
                        }
                        env->DeleteLocalRef(str);
                    }
                    env->DeleteLocalRef(m);
                }
                env->DeleteLocalRef(methodCls);
            }
            env->DeleteLocalRef(methodsArray);
        }
        env->DeleteLocalRef(classCls);
    }
    env->DeleteLocalRef(cls);
    if (env->ExceptionCheck()) env->ExceptionClear();

    if (strlen(buf) == 0)
        strcpy(buf, "LuaEngine类已加载但无含snap/capture/screen/bitmap的方法");

    if (attached) vm->DetachCurrentThread();
    return buf;
}
