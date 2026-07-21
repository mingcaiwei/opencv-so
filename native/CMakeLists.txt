cmake_minimum_required(VERSION 3.10)
project(lrsy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 体积优化：按段裁剪未引用代码 + 链接期 strip 符号表
# 不使用 -fvisibility=hidden：否则 extern "C" 导出函数不进动态符号表，
# 懒人精灵 LuaJIT FFI 的 dlsym 将找不到符号（如 screenshot）。
# -Wl,-s: strip 符号表(.symtab)/字符串表/调试信息；动态符号表(.dynsym)保留，
#         故 extern "C" 导出函数仍可被 dlsym 找到，FFI 调用不受影响。
add_compile_options(-ffunction-sections -fdata-sections)
add_link_options(-Wl,--gc-sections -Wl,--exclude-libs,ALL -Wl,-s)

# OpenCV Android SDK 路径，由 -DOPENCV_SDK=/path/to/OpenCV-android-sdk 传入
if(NOT DEFINED OPENCV_SDK)
    message(FATAL_ERROR "OPENCV_SDK not set. Pass -DOPENCV_SDK=/abs/path/to/OpenCV-android-sdk")
endif()

# OpenCV 4.5.3 Android SDK：libopencv_java4.so 为含全部模块的动态单体库，
# 运行时由懒人精灵进程内已加载的同名库提供符号。
set(OpenCV_DIR ${OPENCV_SDK}/sdk/native/jni)
find_package(OpenCV REQUIRED)
# 诊断：find_package 默认 OpenCV_LIBS 含 staticlibs/*.a + 3rdparty 静态库，
# 直接链接会把大量 OpenCV 代码静态链入 libsy.so（.text 膨胀），故仅用于诊断打印。
message(STATUS "==== OpenCV_LIBS=${OpenCV_LIBS} ====")

add_library(libsy SHARED
    src/core.cpp
    src/screenshot_jni.cpp
    src/imgproc.cpp
    src/morphology.cpp
    src/geometry.cpp
    src/features.cpp
    src/map_matcher.cpp
    src/multi_scale_matcher.cpp
    src/map_stitcher.cpp
)

# 头文件：SDK 预生成的 opencv2/ 头文件已自包含
target_include_directories(libsy PRIVATE
    include
    ${OPENCV_SDK}/sdk/native/jni/include
)

# 直接用动态库文件路径链接 libopencv_java4.so（而非 OpenCV_LIBS 的静态库组件）。
# 链接器只记录 NEEDED libopencv_java4.so，不把 OpenCV 代码链入 libsy.so，
# .text 段仅含本工程 9 个 cpp 的业务代码。
# 此前用 OpenCV_LIBS 时 .text 段 arm64 4.26MB / x86_64 25.44MB，系静态库膨胀。
set(OPENCV_JAVA4_LIB "${OPENCV_SDK}/sdk/native/libs/${ANDROID_ABI}/libopencv_java4.so")
if(NOT EXISTS "${OPENCV_JAVA4_LIB}")
    message(FATAL_ERROR "未找到 OpenCV 动态库: ${OPENCV_JAVA4_LIB}")
endif()
message(STATUS "==== 链接动态库: ${OPENCV_JAVA4_LIB} ====")
target_link_libraries(libsy PRIVATE "${OPENCV_JAVA4_LIB}" jnigraphics log)

# 产出 libsy.so
set_target_properties(libsy PROPERTIES OUTPUT_NAME "sy")
