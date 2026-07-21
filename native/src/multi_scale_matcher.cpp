// 多尺度匹配器：对大地图预计算 SIFT 特征，按预设尺度缩放小地图后逐一匹配
#include "common.h"

#include <vector>

class MultiScaleMatcher
{
public:
    MultiScaleMatcher(const cv::Mat &m, const double *scales, int scale_count)
        : largeMap_(m)
    {
        if (scales && scale_count > 0)
            scales_.assign(scales, scales + scale_count);
        else
            scales_.push_back(1.0);
        computeFeatures();
    }

    bool findPosition(const cv::Mat &smallMap, double threshold,
                      double *cx, double *cy, double *conf, double *best_scale) const
    {
        if (best_scale) *best_scale = 1.0;
        if (desc_.empty() || smallMap.empty() || scales_.empty())
            return false;

        double bestConf = -1.0;
        double bx = -1, by = -1, bs = 1.0;
        bool found = false;
        for (double s : scales_)
        {
            if (s <= 0)
                continue;
            cv::Mat resized;
            cv::resize(smallMap, resized, cv::Size(), s, s, cv::INTER_LINEAR);
            if (resized.empty())
                continue;
            double x = -1, y = -1, c = 0;
            int good = 0;
            if (locateTemplateSIFT(desc_, kp_, resized, threshold, &x, &y, &c, &good) && c > bestConf)
            {
                bestConf = c;
                bx = x;
                by = y;
                bs = s;
                found = true;
            }
        }
        if (found)
        {
            if (cx) *cx = bx;
            if (cy) *cy = by;
            if (conf) *conf = bestConf;
            if (best_scale) *best_scale = bs;
        }
        return found;
    }

private:
    void computeFeatures()
    {
        kp_.clear();
        desc_.release();
        if (largeMap_.empty())
            return;
        cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
        sift->detectAndCompute(largeMap_, cv::noArray(), kp_, desc_);
    }

    cv::Mat largeMap_;
    std::vector<cv::KeyPoint> kp_;
    cv::Mat desc_;
    std::vector<double> scales_;
};

extern "C"
{

void *createMultiScaleMatcher(void *large_map_ptr, double *scales, int scale_count)
{
    if (!isValidMat(large_map_ptr))
        return nullptr;
    return new MultiScaleMatcher(*toMat(large_map_ptr), scales, scale_count);
}

void findPositionMultiScale(void *multi_matcher_ptr, void *small_map_ptr, double threshold,
                            double *center_x, double *center_y, double *confidence, double *best_scale)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    if (best_scale) *best_scale = 1.0;
    auto *m = static_cast<MultiScaleMatcher *>(multi_matcher_ptr);
    if (!m || !isValidMat(small_map_ptr))
        return;
    m->findPosition(*toMat(small_map_ptr), threshold, center_x, center_y, confidence, best_scale);
}

void releaseMultiScaleMatcher(void *multi_matcher_ptr)
{
    if (!multi_matcher_ptr)
        return;
    delete static_cast<MultiScaleMatcher *>(multi_matcher_ptr);
}

} // extern "C"
