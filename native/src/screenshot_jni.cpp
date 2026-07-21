// 截图实现：通过 JNI_GetCreatedJavaVMs 获取懒人精灵进程的 JavaVM，
// 调用 com.nx.assist.lua.LuaEngine.snapShot(IIII)Landroid/graphics/Bitmap;
// 再用 AndroidBitmap_lockPixels 把像素转为 cv::Mat。
// 这样不依赖 libengine.so，完全独立。
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
        jclass cls = env->FindClass("com/nx/assist/lua/LuaEngine");
        if (!cls)
        {
            LOGE("LuaEngine class not found");
            break;
        }
        jmethodID mid = env->GetStaticMethodID(cls, "snapShot", "(IIII)Landroid/graphics/Bitmap;");
        if (!mid)
        {
            LOGE("snapShot method not found");
            env->DeleteLocalRef(cls);
            break;
        }

        jobject bmp = env->CallStaticObjectMethod(cls, mid, (jint)x, (jint)y, (jint)x1, (jint)y1);
        env->DeleteLocalRef(cls);
        if (env->ExceptionCheck())
        {
            env->ExceptionClear();
            LOGE("LuaEngine.snapShot threw exception");
        }
        if (!bmp)
        {
            LOGE("snapShot returned null bitmap (截图服务未开启?)");
            break;
        }

        AndroidBitmapInfo info;
        if (AndroidBitmap_getInfo(env, bmp, &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        {
            env->DeleteLocalRef(bmp);
            break;
        }
        void *pixels = nullptr;
        if (AndroidBitmap_lockPixels(env, bmp, &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        {
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
