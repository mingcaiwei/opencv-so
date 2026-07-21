// 图像处理：cvtColor / convertToGray / resize / threshold / gaussianBlur / cannyEdge / bilateralFilter
#include "common.h"

extern "C"
{

void *cvtColor(void *src, int code)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::cvtColor(*toMat(src), *out, code);
    return fromMat(out);
}

void *convertToGray(void *mat_ptr)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::cvtColor(*toMat(mat_ptr), *out, cv::COLOR_BGR2GRAY);
    return fromMat(out);
}

void *resize(void *src, int width, int height, int interpolation)
{
    if (!isValidMat(src) || width <= 0 || height <= 0)
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::resize(*toMat(src), *out, cv::Size(width, height), 0, 0, interpolation);
    return fromMat(out);
}

void *threshold(void *src, double thresh, double maxval, int type)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::threshold(*toMat(src), *out, thresh, maxval, type);
    return fromMat(out);
}

void *gaussianBlur(void *src, int ksize, double sigmaX, double sigmaY)
{
    if (!isValidMat(src))
        return nullptr;
    if (ksize < 1)
        ksize = 1;
    if (ksize % 2 == 0)
        ksize += 1;
    cv::Mat *out = new cv::Mat();
    cv::GaussianBlur(*toMat(src), *out, cv::Size(ksize, ksize), sigmaX, sigmaY);
    return fromMat(out);
}

void *cannyEdge(void *mat_ptr, double threshold1, double threshold2, int aperture_size)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::Canny(*toMat(mat_ptr), *out, threshold1, threshold2, aperture_size);
    return fromMat(out);
}

void *bilateralFilter(void *src, int d, double sigmaColor, double sigmaSpace)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::bilateralFilter(*toMat(src), *out, d, sigmaColor, sigmaSpace);
    return fromMat(out);
}

} // extern "C"
