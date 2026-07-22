// 截图实现：通过 JNI_GetCreatedJavaVMs 获取懒人精灵进程的 JavaVM，
// 调用 com.nx.assist.lua.LuaEngine.snapShot(IIII)Landroid/graphics/Bitmap;
// 再用 AndroidBitmap_lockPixels 把像素转为 cv::Mat。
//
// 关键坑：.so 由 LuaJIT ffi.load(dlopen) 加载，调用截图的线程是 native 线程，
// AttachCurrentThread 后 FindClass 用【系统 ClassLoader】，找不到应用类 com/nx/assist/lua/LuaEngine。
// 修复：先用 FindClass 兜底（线程已带应用 ClassLoader 时直接成功），失败则回退到
//       Thread.currentThread().getContextClassLoader().loadClass() 加载应用类。
//       java/lang/Thread、java/lang/ClassLoader、android/graphics/Bitmap 是系统/框架类，FindClass 可用。
#include "common.h"

#include <jni.h>
#include <android/bitmap.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstring>

using GetCreatedJavaVMs_t = jint (*)(JavaVM **, jsize, jsize *);

// 全局错误信息（供 Lua 层诊断 JNI 截图失败原因）
static char g_lastError[256] = "no error";

static JavaVM *getJavaVM()
{
    void *handle = dlopen("libart.so", RTLD_NOW);
    if (!handle)
        handle = dlopen("libdvm.so", RTLD_NOW);
    if (!handle)
    {
        LOGE("dlopen libart.so failed");
        return nullptr;
    }
    auto fn = (GetCreatedJavaVMs_t)dlsym(handle, "JNI_GetCreatedJavaVMs");
    if (!fn)
    {
        LOGE("JNI_GetCreatedJavaVMs symbol not found");
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
// 用于 FindClass 在 native 线程找不到应用类时的回退
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

// 缓存：LuaEngine 类 + snapShot 方法 + Bitmap.recycle 方法，避免每次截图重复查找
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

    // Bitmap.recycle() 用于立即释放原生像素内存（文档要求释放，避免截图循环内存堆积）
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

void *screenshotImpl(int x, int y, int x1, int y1)
{
    static JavaVM *vm = nullptr;
    if (!vm)
        vm = getJavaVM();
    if (!vm)
    {
        snprintf(g_lastError, sizeof(g_lastError), "getJavaVM失败(dlopen libart.so或JNI_GetCreatedJavaVMs)");
        return nullptr;
    }

    JNIEnv *env = nullptr;
    bool attached = false;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
    {
        if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        {
            LOGE("AttachCurrentThread failed");
            snprintf(g_lastError, sizeof(g_lastError), "AttachCurrentThread失败");
            return nullptr;
        }
        attached = true;
    }

    void *result = nullptr;
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
            // 兜底按 RGBA 处理
            cv::Mat rgba((int)info.height, (int)info.width, CV_8UC4, pixels);
            cv::cvtColor(rgba, *mat, cv::COLOR_RGBA2BGR);
        }
        AndroidBitmap_unlockPixels(env, bmp);

        // 立即回收 Bitmap 原生像素内存（cvtColor 已拷贝像素到独立 Mat，回收安全）
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
            snprintf(g_lastError, sizeof(g_lastError), "ok");
        }
    } while (0);

    if (attached)
        vm->DetachCurrentThread();
    return result;
}

// 诊断：返回最近一次 JNI 截图的错误信息（供 Lua 层调用）
extern "C" const char *getScreenshotError()
{
    return g_lastError;
}

// 诊断：用 Java 反射列出 LuaEngine 类含 snap/capture/screen/bitmap 的方法
// 帮助定位正确的截图方法名和签名（当 snapShot(IIII) 不存在时用）
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

    // getMethods() 含继承方法
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
                            // 只记录含 snap/capture/screen/bitmap 的方法（避免输出过长）
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
