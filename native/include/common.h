#ifndef LRSY_COMMON_H
#define LRSY_COMMON_H

// libsy 公共头：Mat 指针转换、空指针校验、全局匹配信息、日志
// 所有导出函数均以 extern "C" 暴露给懒人精灵 LuaJIT FFI，命名与
// opencvutil.lua 的 ffi.cdef 完全一致。

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <android/log.h>

// Mat 在 FFI 边界以 void* 传递（实际为 cv::Mat*）
using MatPtr = cv::Mat *;

inline cv::Mat *toMat(void *p) { return static_cast<cv::Mat *>(p); }
inline const cv::Mat *toMat(const void *p) { return static_cast<const cv::Mat *>(p); }
inline void *fromMat(cv::Mat *m) { return static_cast<void *>(m); }

inline bool isValidMat(const void *p) { return p != nullptr; }

// 全局最近一次特征匹配信息，供 getLastMatchInfo 读取
struct LastMatchInfo
{
    double confidence = 0.0;
    int keypoints_count = 0;
    int good_matches_count = 0;
};
extern LastMatchInfo g_lastMatch;

// screenshot 的底层实现，由 screenshot_jni.cpp 提供（JNI 调 LuaEngine.snapShot）
void *screenshotImpl(int x, int y, int x1, int y1);

// 共享匹配工具：在场景(预计算特征)中定位原始模板 Mat，成功返回 true 并写中心坐标
// 由 features.cpp 实现，供 map_matcher / multi_scale_matcher / map_stitcher 复用
// SIFT + BFMatcher(NORM_L2) + ratio test + 距离阈值 + findHomography(RANSAC)
bool locateTemplateSIFT(const cv::Mat &sceneDesc, const std::vector<cv::KeyPoint> &sceneKp,
                        const cv::Mat &tmplMat, double threshold,
                        double *cx, double *cy, double *conf, int *good_count);
// ORB + BFMatcher(NORM_HAMMING) + ratio test + 距离阈值 + homography
bool locateTemplateORB(const cv::Mat &sceneDesc, const std::vector<cv::KeyPoint> &sceneKp,
                       const cv::Mat &tmplMat, double threshold,
                       double *cx, double *cy, double *conf, int *good_count);

#define LOG_TAG "libsy"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif // LRSY_COMMON_H
