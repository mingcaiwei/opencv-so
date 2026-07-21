// 几何变换：rotate / flip / crop / warpAffine / warpPerspective
#include "common.h"

extern "C"
{

void *rotate(void *src, double angle, double scale)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *m = toMat(src);
    cv::Point2f center(m->cols / 2.0f, m->rows / 2.0f);
    cv::Mat r = cv::getRotationMatrix2D(center, angle, scale);
    cv::Mat *out = new cv::Mat();
    cv::warpAffine(*m, *out, r, m->size());
    return fromMat(out);
}

void *flip(void *src, int flipCode)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *out = new cv::Mat();
    cv::flip(*toMat(src), *out, flipCode);
    return fromMat(out);
}

void *crop(void *src, int x, int y, int width, int height)
{
    if (!isValidMat(src))
        return nullptr;
    cv::Mat *m = toMat(src);
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= m->cols || y >= m->rows)
        return nullptr;
    if (x + width > m->cols)
        width = m->cols - x;
    if (y + height > m->rows)
        height = m->rows - y;
    if (width <= 0 || height <= 0)
        return nullptr;
    return fromMat(new cv::Mat((*m)(cv::Rect(x, y, width, height)).clone()));
}

void *warpAffine(void *src, double *matrix, int width, int height)
{
    if (!isValidMat(src) || !matrix || width <= 0 || height <= 0)
        return nullptr;
    cv::Mat M(2, 3, CV_64F, matrix); // 外部指针包装，warpAffine 只读
    cv::Mat *out = new cv::Mat();
    cv::warpAffine(*toMat(src), *out, M, cv::Size(width, height));
    return fromMat(out);
}

void *warpPerspective(void *src, double *matrix, int width, int height)
{
    if (!isValidMat(src) || !matrix || width <= 0 || height <= 0)
        return nullptr;
    cv::Mat M(3, 3, CV_64F, matrix);
    cv::Mat *out = new cv::Mat();
    cv::warpPerspective(*toMat(src), *out, M, cv::Size(width, height));
    return fromMat(out);
}

} // extern "C"
