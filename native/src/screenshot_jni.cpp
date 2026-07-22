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

using GetCreatedJavaVMs_t = jint (*)(JavaVM **, jsize, jsize *);

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

// 缓存：LuaEngine 类 + snapShot 方法 + Bitmap.recycle 方法，避免每次截图重复查找
static jclass    g_luaEngineCls = nullptr;
static jmethodID g_snapMid      = nullptr;
static jmethodID g_recycleMid   = nullptr;

// 在 FFI native 线程上解析应用类 com.nx.assist.lua.LuaEngine。
// 先 FindClass（线程已带应用 ClassLoader 时直接成功），失败回退到 context ClassLoader。
static bool resolveLuaEngine(JNIEnv *env)
{
    if (g_luaEngineCls && g_snapMid)
        return true;

    jclass cls = env->FindClass("com/nx/assist/lua/LuaEngine");
    if (!cls)
    {
        env->ExceptionClear();
        // 回退：Thread.currentThread().getContextClassLoader().loadClass(...)
        jclass threadCls = env->FindClass("java/lang/Thread");
        if (!threadCls) { env->ExceptionClear(); return false; }
        jmethodID curMid       = env->GetStaticMethodID(threadCls, "currentThread", "()Ljava/lang/Thread;");
        jmethodID getCtxLoader = env->GetMethodID(threadCls, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
        if (!curMid || !getCtxLoader) { env->DeleteLocalRef(threadCls); return false; }

        jobject thread = env->CallStaticObjectMethod(threadCls, curMid);
        env->DeleteLocalRef(threadCls);
        if (env->ExceptionCheck()) env->ExceptionClear();
        if (!thread) return false;

        jobject loader = env->CallObjectMethod(thread, getCtxLoader);
        env->DeleteLocalRef(thread);
        if (env->ExceptionCheck()) env->ExceptionClear();
        if (!loader) return false;

        jclass loaderCls = env->FindClass("java/lang/ClassLoader");
        if (!loaderCls) { env->ExceptionClear(); env->DeleteLocalRef(loader); return false; }
        jmethodID loadClass = env->GetMethodID(loaderCls, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        env->DeleteLocalRef(loaderCls);
        if (!loadClass) { env->DeleteLocalRef(loader); return false; }

        jstring name = env->NewStringUTF("com.nx.assist.lua.LuaEngine");
        cls = (jclass)env->CallObjectMethod(loader, loadClass, name);
        env->DeleteLocalRef(name);
        env->DeleteLocalRef(loader);
        if (env->ExceptionCheck()) env->ExceptionClear();
        if (!cls) return false;
    }

    jmethodID mid = env->GetStaticMethodID(cls, "snapShot", "(IIII)Landroid/graphics/Bitmap;");
    if (!mid)
    {
        env->ExceptionClear();
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
    return true;
}

void *screenshotImpl(int x, int y, int x1, int y1)
{
    static JavaVM *vm = nullptr;
    if (!vm)
        vm = getJavaVM();
    if (!vm)
        return nullptr;

    JNIEnv *env = nullptr;
    bool attached = false;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
    {
        if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        {
            LOGE("AttachCurrentThread failed");
            return nullptr;
        }
        attached = true;
    }

    void *result = nullptr;
    do
    {
        if (!resolveLuaEngine(env))
        {
            LOGE("LuaEngine 解析失败（FindClass 与 contextClassLoader 均失败）");
            break;
        }

        jobject bmp = env->CallStaticObjectMethod(g_luaEngineCls, g_snapMid,
                                                   (jint)x, (jint)y, (jint)x1, (jint)y1);
        if (env->ExceptionCheck())
        {
            env->ExceptionClear();
            LOGE("LuaEngine.snapShot 抛出异常（截图服务未开启?）");
        }
        if (!bmp)
        {
            LOGE("snapShot 返回 null bitmap");
            break;
        }

        AndroidBitmapInfo info;
        if (AndroidBitmap_getInfo(env, bmp, &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        {
            if (g_recycleMid) env->CallVoidMethod(bmp, g_recycleMid);
            env->DeleteLocalRef(bmp);
            break;
        }
        void *pixels = nullptr;
        if (AndroidBitmap_lockPixels(env, bmp, &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        {
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
            result = nullptr;
        }
        else
        {
            result = fromMat(mat);
        }
    } while (0);

    if (attached)
        vm->DetachCurrentThread();
    return result;
}
