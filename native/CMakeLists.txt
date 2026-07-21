cmake_minimum_required(VERSION 3.10)
project(lrsy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 体积优化：隐藏符号、按段裁剪
add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden
                    -ffunction-sections -fdata-sections)
add_link_options(-Wl,--gc-sections -Wl,--exclude-libs,ALL)

# OpenCV Android SDK 路径，由 -DOPENCV_SDK=/path/to/OpenCV-android-sdk 传入
if(NOT DEFINED OPENCV_SDK)
    message(FATAL_ERROR "OPENCV_SDK not set. Pass -DOPENCV_SDK=/abs/path/to/OpenCV-android-sdk")
endif()

# OpenCV 4.5.3 Android SDK 为动态库模式（libopencv_java4.so 单体库）
# find_package 后 OpenCV_LIBS 指向 opencv_java4，链接产出 NEEDED libopencv_java4.so，
# 运行时由懒人精灵进程内已加载的同名库提供符号。
set(OpenCV_DIR ${OPENCV_SDK}/sdk/native/jni)
find_package(OpenCV REQUIRED)

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
target_link_libraries(libsy PRIVATE ${OpenCV_LIBS} jnigraphics log)

# 产出 libsy.so
set_target_properties(libsy PROPERTIES OUTPUT_NAME "sy")
