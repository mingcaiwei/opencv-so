# libsy.so — 懒人精灵 OpenCV 扩展库

基于 OpenCV 4.5.3 的 Android 共享库，供懒人精灵通过 LuaJIT FFI 调用。
支持云手机（ARM）、雷电模拟器（x86/x86_64）、真机（ARM）四种 ABI。

## 工程结构

```
native/
├── CMakeLists.txt              # 编译配置：动态链接 OpenCV，产出 libsy.so
├── include/
│   └── common.h                # 公共头：Mat 指针转换、日志、共享匹配工具声明
└── src/
    ├── core.cpp                # screenshot/loadImage/saveMat/releaseMat/cloneMat/getMat*
    ├── screenshot_jni.cpp      # JNI 截图：dlopen libart.so → LuaEngine.snapShot → AndroidBitmap
    ├── imgproc.cpp             # cvtColor/resize/threshold/gaussianBlur/canny/bilateral
    ├── morphology.cpp          # dilate/erode/open/close/tophat/blackhat/gradient
    ├── geometry.cpp            # rotate/flip/crop/warpAffine/warpPerspective
    ├── features.cpp            # SIFT/ORB 检测、findImageBySIFT/ORB、templateMatchMultiScale
    ├── map_matcher.cpp         # 地图匹配器（寻路定位）
    ├── multi_scale_matcher.cpp # 多尺度匹配器
    └── map_stitcher.cpp        # 地图拼接器（含实时拼接）
```

## 编译前提

| 组件 | 版本 | 说明 |
|------|------|------|
| Android NDK | r25+ | 提供 toolchain 与 jnigraphics |
| CMake | 3.10+ | 构建系统 |
| OpenCV Android SDK | 4.5.3 | **必须 4.5.3**，与懒人精灵内置版本一致 |

OpenCV 4.5.3 Android SDK 下载：
```
https://github.com/opencv/opencv/releases/download/4.5.3/opencv-4.5.3-android-sdk.zip
```
解压后得到 `OpenCV-android-sdk/`，含 `sdk/native/jni/OpenCVConfig.cmake`。

## 本地编译（4 ABI）

```bash
export OPENCV_SDK=/path/to/OpenCV-android-sdk
export ANDROID_NDK_HOME=/path/to/android-ndk
TOOLCHAIN=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake

for ABI in armeabi-v7a arm64-v8a x86 x86_64; do
  cmake -B build-$ABI -S native \
    -DOPENCV_SDK=$OPENCV_SDK \
    -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
    -DANDROID_ABI=$ABI \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release
  cmake --build build-$ABI -j
  mkdir -p 界面/libs/$ABI
  cp build-$ABI/libsy.so 界面/libs/$ABI/libsy.so
done
```

## GitHub Actions 自动编译

workflow 位于仓库根 `.github/workflows/build.yml`：
- **触发**：push 到 main/master、打 `v*` 标签、PR、手动 workflow_dispatch
- **流程**：checkout → 缓存/下载 OpenCV 4.5.3 SDK → 循环编译 4 ABI → 校验产物 → 上传 artifact `libsy-4abi`
- **Release**：打 tag 时自动创建 Release 并附加 `libsy-4abi.zip`

使用流程：
1. push 代码到 GitHub
2. Actions 运行完成后，下载 `libsy-4abi` artifact
3. 解压得到 `界面/libs/{armeabi-v7a,arm64-v8a,x86,x86_64}/libsy.so`
4. 将 4 个 libsy.so 放入工程的 `界面/libs/<abi>/` 目录

## 运行时依赖

- `libsy.so` 动态依赖 `libopencv_java4.so`（NEEEDED），运行时由**懒人精灵进程内已加载**的 OpenCV 4.5.3 提供符号，无需随包附带。
- 因此 libsy.so 体积仅约 120-160KB（仅含业务代码）。
- 链接 `libjnigraphics.so`（AndroidBitmap_* 接口）与 `liblog.so`（日志），均为系统库。

## screenshot 实现原理

不依赖懒人精灵的 `libengine.so`，独立通过 JNI 实现：
1. `dlopen("libart.so")` + `dlsym("JNI_GetCreatedJavaVMs")` 获取进程 JavaVM
2. `AttachCurrentThread` 获取 JNIEnv
3. 调用 `com.nx.assist.lua.LuaEngine.snapShot(IIII)Landroid/graphics/Bitmap;`
4. `AndroidBitmap_lockPixels` 取像素，`cvtColor` 转 BGR 得 `cv::Mat`

## 集成到懒人精灵

1. `opencv.lcprojit` 已开启 4 ABI（`cpu_x86/arm/arm64/x86_64=1`）与 `engine_type=3`
2. 脚本 `脚本/opencvutil.lua` 定义全部 FFI 接口与 60 个 OpenCV.* 封装
3. 入口 `脚本/opencv.lua` 加载 opencvutil 并运行示例
4. `.so` 加载路径：`getWorkPath()/../bin/界面/libs/<abi>/libsy.so`（按 `getCpuArch()` 选目录：0=x86, 1=armeabi-v7a, 2=arm64-v8a, 3=x86_64，x86_64 失败回退 x86）

## 已知风险与排错

| 现象 | 原因 / 解决 |
|------|------|
| `ffi.load` 失败、找不到符号 | `libopencv_java4.so` 未在进程内加载；确认懒人精灵版本内置 OpenCV 4.5.3 |
| 截图返回 null | snapShot 截图服务未开启；需 root 模式（`opt_runinrootmode_checked=1`）并开启截图权限 |
| x86_64 加载失败 | 自动回退 x86 目录；如仍失败确认 `界面/libs/x86_64/libsy.so` 存在 |
| SIFT 找不到模板 | 模板过大/过小、阈值过严；调整 threshold（默认 100，越小越严），或改用 templateMatchMultiScale |
| 编译报错找不到 OpenCVConfig | `OPENCV_SDK` 路径错误，应指向解压后的 `OpenCV-android-sdk` 根目录 |

## 接口清单

共 60 个 C 接口，与 `脚本/opencvutil.lua` 的 `ffi.cdef` 1:1 对齐。详见该文件的 cdef 块与 `OpenCV.*` 封装。主要分组：
- 基础图像操作（7）
- 图像处理（7）
- 形态学操作（7）
- 几何变换（5）
- 特征检测与匹配（7）
- 地图匹配器 MapMatcher（9）
- 多尺度匹配器 MultiScaleMatcher（3）
- 地图拼接器 MapStitcher（17）
