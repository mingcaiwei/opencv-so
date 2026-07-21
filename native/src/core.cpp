// 基础图像操作：screenshot / loadImage / saveMat / releaseMat / cloneMat / getMat*
#include "common.h"

LastMatchInfo g_lastMatch; // 全局匹配信息定义（common.h 中 extern 声明）

extern "C"
{

// 截图：转交 screenshot_jni.cpp 的 JNI 实现
void *screenshot(int x, int y, int x1, int y1)
{
    return screenshotImpl(x, y, x1, y1);
}

// 从文件加载图像（彩色）
void *loadImage(const char *filepath)
{
    if (!filepath)
        return nullptr;
    cv::Mat *m = new cv::Mat(cv::imread(filepath, cv::IMREAD_COLOR));
    if (m->empty())
    {
        delete m;
        return nullptr;
    }
    return fromMat(m);
}

// 保存 Mat 到文件
int saveMat(void *mat_ptr, const char *filepath)
{
    if (!isValidMat(mat_ptr) || !filepath)
        return 0;
    return cv::imwrite(filepath, *toMat(mat_ptr)) ? 1 : 0;
}

// 释放 Mat
void releaseMat(void *mat_ptr)
{
    if (!isValidMat(mat_ptr))
        return;
    delete toMat(mat_ptr);
}

// 克隆 Mat
void *cloneMat(void *mat_ptr)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    return fromMat(new cv::Mat(toMat(mat_ptr)->clone()));
}

int getMatWidth(void *mat_ptr) { return isValidMat(mat_ptr) ? toMat(mat_ptr)->cols : 0; }
int getMatHeight(void *mat_ptr) { return isValidMat(mat_ptr) ? toMat(mat_ptr)->rows : 0; }
int getMatChannels(void *mat_ptr) { return isValidMat(mat_ptr) ? toMat(mat_ptr)->channels() : 0; }

} // extern "C"
