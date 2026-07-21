// 形态学操作：dilate / erode / morphologyOpen/Close/Tophat/Blackhat/Gradient
#include "common.h"

static cv::Mat getKernel(int ksize)
{
    if (ksize < 1)
        ksize = 1;
    if (ksize % 2 == 0)
        ksize += 1;
    return cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize, ksize));
}

extern "C"
{

void *dilate(void *mat_ptr, int kernel_size, int iterations)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::dilate(*toMat(mat_ptr), *out, getKernel(kernel_size), cv::Point(-1, -1), iterations);
    return fromMat(out);
}

void *erode(void *mat_ptr, int kernel_size, int iterations)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::erode(*toMat(mat_ptr), *out, getKernel(kernel_size), cv::Point(-1, -1), iterations);
    return fromMat(out);
}

void *morphologyOpen(void *mat_ptr, int kernel_size, int iterations)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::morphologyEx(*toMat(mat_ptr), *out, cv::MORPH_OPEN, getKernel(kernel_size), cv::Point(-1, -1), iterations);
    return fromMat(out);
}

void *morphologyClose(void *mat_ptr, int kernel_size, int iterations)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::morphologyEx(*toMat(mat_ptr), *out, cv::MORPH_CLOSE, getKernel(kernel_size), cv::Point(-1, -1), iterations);
    return fromMat(out);
}

void *morphologyTophat(void *mat_ptr, int kernel_size)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::morphologyEx(*toMat(mat_ptr), *out, cv::MORPH_TOPHAT, getKernel(kernel_size));
    return fromMat(out);
}

void *morphologyBlackhat(void *mat_ptr, int kernel_size)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::morphologyEx(*toMat(mat_ptr), *out, cv::MORPH_BLACKHAT, getKernel(kernel_size));
    return fromMat(out);
}

void *morphologyGradient(void *mat_ptr, int kernel_size)
{
    if (!isValidMat(mat_ptr))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::morphologyEx(*toMat(mat_ptr), *out, cv::MORPH_GRADIENT, getKernel(kernel_size));
    return fromMat(out);
}

} // extern "C"
