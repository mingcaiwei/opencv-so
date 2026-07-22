// 截图实现：三种路径，按速度优先级尝试
//
// 路径 1：JNI 截图（~30ms）— 通过 JavaVM 调 LuaEngine.snapShot(IIII) 返回 Bitmap
//   getJavaVM 用三层查找：ELF 手动解析 → RTLD_DEFAULT → dlopen 多路径
//   ELF 解析直接从 /proc/self/maps 找 libart.so 基地址，解析 ELF 符号表，
//   完全绕过 Android 7+ namespace 对 dlsym 的限制
//
// 路径 2：screencap 命令截图（~50ms）— popen 读取输出
//   自动识别 PNG（imdecode）和 raw RGBA（直接解析）两种格式
//   非 root 失败时自动尝试 su -c（root 模式）
//
// 路径 3：返回 nullptr，Lua 层走 snapShot(path) 文件法（~175ms）
#include "common.h"

#include <jni.h>
#include <android/bitmap.h>
#include <dlfcn.h>
#include <elf.h>
#include <link.h>   // ElfW 宏定义在此（bionic 的 elf.h 不含 ElfW）
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>

// 兜底：如果 link.h 仍未定义 ElfW，用手动定义
#ifndef ElfW
#if defined(__LP64__)
#define ElfW(type) Elf64_##type
#else
#define ElfW(type) Elf32_##type
#endif
#endif

using GetCreatedJavaVMs_t = jint (*)(JavaVM **, jsize, jsize *);

// 全局错误信息（供 Lua 层诊断 JNI 截图失败原因）
static char g_lastError[512] = "no error";

// =====================================================================
// ELF 手动符号解析：从 /proc/self/maps 找到库的基地址，解析 ELF 符号表
// 直接从内存中查找符号地址，绕过 Android 7+ 的 namespace 对 dlsym 的限制
// =====================================================================
static void *findSymbolInLib(const char *libname, const char *symname)
{
    // 1. 读 /proc/self/maps，找包含 libname 的第一行，取基地址
    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp)
    {
        LOGE("findSymbolInLib: 无法打开 /proc/self/maps");
        return nullptr;
    }

    char line[512];
    uintptr_t base_addr = 0;
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, libname))
        {
            // 行格式：地址范围 权限 偏移 ... 路径
            // 例如：7b1234000-7b1245000 r--p 00000000 ... libart.so
            unsigned long addr_val = 0;
            sscanf(line, "%lx", &addr_val);
            base_addr = (uintptr_t)addr_val;
            break;
        }
    }
    fclose(fp);

    if (base_addr == 0)
    {
        LOGE("findSymbolInLib: /proc/self/maps 中未找到 %s", libname);
        return nullptr;
    }

    // 2. 验证 ELF 魔数
    ElfW(Ehdr) *ehdr = (ElfW(Ehdr) *)base_addr;
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
    {
        LOGE("findSymbolInLib: %s 的 ELF 魔数不匹配", libname);
        return nullptr;
    }

    // 3. 遍历 program headers，计算 load_bias 并找 PT_DYNAMIC
    // load_bias = base_addr - 第一个 PT_LOAD 段的 p_vaddr（通常 p_vaddr=0）
    uintptr_t load_bias = base_addr;
    bool found_load = false;
    ElfW(Dyn) *dyn = nullptr;

    for (int i = 0; i < ehdr->e_phnum; i++)
    {
        ElfW(Phdr) *phdr = (ElfW(Phdr) *)(base_addr + ehdr->e_phoff + (size_t)i * ehdr->e_phentsize);
        if (phdr->p_type == PT_LOAD && !found_load)
        {
            load_bias = base_addr - phdr->p_vaddr;
            found_load = true;
        }
        else if (phdr->p_type == PT_DYNAMIC)
        {
            dyn = (ElfW(Dyn) *)(load_bias + phdr->p_vaddr);
        }
    }

    if (!dyn)
    {
        LOGE("findSymbolInLib: %s 中未找到 PT_DYNAMIC", libname);
        return nullptr;
    }

    // 4. 从 dynamic 段提取 DT_SYMTAB、DT_STRTAB、DT_HASH
    // 注意：d_ptr 是相对库基址的虚拟地址，需加 load_bias 得到实际地址
    const ElfW(Sym) *symtab = nullptr;
    const char *strtab = nullptr;
    const uint32_t *hash = nullptr;

    for (ElfW(Dyn) *d = dyn; d->d_tag != DT_NULL; d++)
    {
        switch (d->d_tag)
        {
        case DT_SYMTAB:
            symtab = (const ElfW(Sym) *)(load_bias + d->d_un.d_ptr);
            break;
        case DT_STRTAB:
            strtab = (const char *)(load_bias + d->d_un.d_ptr);
            break;
        case DT_HASH:
            hash = (const uint32_t *)(load_bias + d->d_un.d_ptr);
            break;
        }
    }

    if (!symtab || !strtab)
    {
        LOGE("findSymbolInLib: %s 中未找到 SYMTAB 或 STRTAB", libname);
        return nullptr;
    }

    // 5. 确定符号表大小
    // 优先用 DT_HASH 的 nchain（= 符号数）；否则用 strtab-symtab 估算
    int sym_count = 0;
    if (hash)
    {
        // DT_HASH 结构：nbucket, nchain, bucket[], chain[]
        // nchain = 符号表中的条目数
        sym_count = (int)hash[1];
    }
    if (sym_count <= 0)
    {
        // 回退：strtab 通常紧跟 symtab
        size_t symtab_size = (const char *)strtab - (const char *)symtab;
        sym_count = (int)(symtab_size / sizeof(ElfW(Sym)));
    }
    if (sym_count <= 0 || sym_count > 500000)
    {
        LOGE("findSymbolInLib: %s 符号数异常 %d", libname, sym_count);
        return nullptr;
    }

    // 6. 遍历符号表查找目标符号
    for (int i = 0; i < sym_count; i++)
    {
        const ElfW(Sym) *sym = &symtab[i];
        if (sym->st_name == 0 || sym->st_value == 0)
            continue;
        const char *name = strtab + sym->st_name;
        if (strcmp(name, symname) == 0)
        {
            void *addr = (void *)(load_bias + sym->st_value);
            LOGI("findSymbolInLib: 在 %s 中找到 %s = %p", libname, symname, addr);
            return addr;
        }
    }

    LOGE("findSymbolInLib: 在 %s 的 %d 个符号中未找到 %s", libname, sym_count, symname);
    return nullptr;
}

static JavaVM *getJavaVM()
{
    auto fn = (GetCreatedJavaVMs_t) nullptr;

    // 方式 1（最可靠）：手动解析 libart.so 的 ELF 符号表
    // 直接从 /proc/self/maps 找基地址 + 解析 ELF，绕过所有 dlsym namespace 限制
    fn = (GetCreatedJavaVMs_t)findSymbolInLib("libart.so", "JNI_GetCreatedJavaVMs");
    if (!fn)
    {
        // Android 10+ 可能在不同路径，也试 libdvm.so（旧版）
        fn = (GetCreatedJavaVMs_t)findSymbolInLib("libdvm.so", "JNI_GetCreatedJavaVMs");
    }

    // 方式 2：RTLD_DEFAULT 搜索所有已加载库（部分 Android 版本可用）
    if (!fn)
    {
        fn = (GetCreatedJavaVMs_t) dlsym(RTLD_DEFAULT, "JNI_GetCreatedJavaVMs");
    }

    // 方式 3：dlopen 多路径兜底（旧 Android 或非 namespace 设备）
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
                fn = (GetCreatedJavaVMs_t) dlsym(handle, "JNI_GetCreatedJavaVMs");
                if (fn) break;
            }
        }
    }

    if (!fn)
    {
        LOGE("getJavaVM: 所有方式均失败（ELF解析+RTLD_DEFAULT+dlopen）");
        return nullptr;
    }

    JavaVM *vm = nullptr;
    jsize n = 0;
    if (fn(&vm, 1, &n) != JNI_OK || n < 1)
    {
        LOGE("getJavaVM: JNI_GetCreatedJavaVMs 返回失败");
        return nullptr;
    }
    LOGI("getJavaVM: 成功获取 JavaVM=%p", vm);
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

// =====================================================================
// 路径 2：screencap 命令截图
// 自动识别输出格式：PNG（cv::imdecode）或 raw RGBA（直接解析）
// 自动尝试 root 模式（su -c）当普通模式无输出时
// =====================================================================

// 尝试执行一个截图命令，读取全部输出，自动识别格式并转为 cv::Mat
// 成功返回 Mat*（含区域裁剪），失败返回 nullptr
static cv::Mat *tryScreencapCommand(const char *cmd, int x, int y, int x1, int y1)
{
    FILE *fp = popen(cmd, "r");
    if (!fp)
        return nullptr;

    // 读取全部输出到 buffer
    std::vector<uchar> buf;
    {
        uchar tmp[8192];
        size_t n;
        while ((n = fread(tmp, 1, sizeof(tmp), fp)) > 0)
            buf.insert(buf.end(), tmp, tmp + n);
    }
    pclose(fp);

    if (buf.empty())
        return nullptr;

    // 检测 PNG 格式（魔数：89 50 4E 47 0D 0A 1A 0A）
    if (buf.size() >= 8 && buf[0] == 0x89 && buf[1] == 0x50 &&
        buf[2] == 0x4E && buf[3] == 0x47)
    {
        cv::Mat raw = cv::imdecode(buf, cv::IMREAD_COLOR);
        if (raw.empty())
            return nullptr;
        cv::Mat *mat = new cv::Mat(raw);

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
                return cropped;
            }
        }
        return mat;
    }

    // 尝试 raw RGBA 格式（头部 4 个 int：width, height, stride, format）
    if (buf.size() >= 16)
    {
        // 用 memcpy 避免对齐问题
        int header[4];
        memcpy(header, buf.data(), 16);
        int width  = header[0];
        int height = header[1];
        int stride = header[2] > 0 ? header[2] : width;
        int format = header[3]; // 1=RGBA_8888(4bpp), 2=RGB_565(2bpp)

        if (width > 0 && height > 0 && width < 10000 && height < 10000 &&
            (format == 1 || format == 2))
        {
            int bpp = (format == 2) ? 2 : 4;
            size_t rowBytes   = (size_t)width  * bpp;
            size_t strideBytes = (size_t)stride * bpp;
            size_t pixelSize  = (size_t)height * rowBytes;

            // 像素数据紧跟头部（16 字节）
            const uchar *pixels = buf.data() + 16;
            size_t available    = buf.size() - 16;
            if (available < pixelSize)
                return nullptr; // 数据不完整

            cv::Mat *mat = new cv::Mat();
            if (format == 2) // RGB_565
            {
                cv::Mat rgb565(height, width, CV_8UC2, (void *)pixels);
                cv::cvtColor(rgb565, *mat, cv::COLOR_BGR5652BGR);
            }
            else // RGBA_8888
            {
                cv::Mat rgba(height, width, CV_8UC4, (void *)pixels);
                cv::cvtColor(rgba, *mat, cv::COLOR_RGBA2BGR);
            }

            if (mat->empty())
            {
                delete mat;
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
                    return cropped;
                }
            }
            return mat;
        }
    }

    return nullptr; // 格式未知
}

static void *screenshotViaScreencap(int x, int y, int x1, int y1)
{
    // 按优先级尝试不同命令组合
    // 1. screencap（raw，最快）  2. screencap -p（PNG）
    // 3. su -c screencap（root raw）  4. su -c screencap -p（root PNG）
    const char *cmds[] = {
        "screencap",
        "screencap -p",
        "su -c screencap",
        "su -c 'screencap -p'",
    };

    for (auto cmd : cmds)
    {
        cv::Mat *mat = tryScreencapCommand(cmd, x, y, x1, y1);
        if (mat)
        {
            snprintf(g_lastError, sizeof(g_lastError), "screencap ok (%s)", cmd);
            return fromMat(mat);
        }
    }

    snprintf(g_lastError, sizeof(g_lastError),
             "screencap: 所有命令均失败(无root或权限不足)");
    return nullptr;
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
        snprintf(g_lastError, sizeof(g_lastError), "getJavaVM失败(ELF解析+RTLD_DEFAULT+dlopen均失败)");
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
