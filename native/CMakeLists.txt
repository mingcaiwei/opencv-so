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

# OpenCV 4.5.3 Android SDK 为动态库模式（libopencv_java4.so 单体库）
# opencv_java4 包含全部模块，运行时由懒人精灵进程内已加载的 libopencv_java4.so 提供符号。
set(OpenCV_DIR ${OPENCV_SDK}/sdk/native/jni)
find_package(OpenCV REQUIRED)
# 诊断：打印 OpenCV_LIBS，确认是否混入静态库组件
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

target_include_directories(libsy PRIVATE include)
# 只链接动态单体库 opencv_java4，避免 OpenCV_LIBS 里的静态库组件把大量 OpenCV 代码
# 静态链入 libsy.so（此前 .text 段 arm64 4.26MB / x86_64 25.44MB，即静态库代码膨胀）。
# opencv_java4 已含全部模块符号，业务代码所需 OpenCV API 均由其提供。
if(TARGET opencv_java4)
    target_link_libraries(libsy PRIVATE opencv_java4 jnigraphics log)
else()
    message(WARNING "未找到 opencv_java4 target，回退到 OpenCV_LIBS（可能含静态库）")
    target_link_libraries(libsy PRIVATE ${OpenCV_LIBS} jnigraphics log)
endif()

# 产出 libsy.so
set_target_properties(libsy PROPERTIES OUTPUT_NAME "sy")
