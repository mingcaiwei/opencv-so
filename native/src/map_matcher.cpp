// 地图匹配器（寻路定位）：预计算大地图 SIFT 特征，在小地图/截图中定位坐标
#include "common.h"

class MapMatcher
{
public:
    explicit MapMatcher(const cv::Mat &m) : largeMap_(m)
    {
        computeFeatures();
    }

    bool findPosition(const cv::Mat &smallMap, double threshold,
                      double *cx, double *cy, double *conf) const
    {
        int good = 0;
        return locateTemplateSIFT(desc_, kp_, smallMap, threshold, cx, cy, conf, &good);
    }

    bool findPositionInRegion(const cv::Mat &smallMap, double threshold,
                              int rx, int ry, int rw, int rh,
                              double *cx, double *cy, double *conf) const
    {
        if (desc_.empty() || kp_.empty())
            return false;
        // 过滤到 region 矩形内的关键点（坐标保持大地图系），构造子描述子
        std::vector<cv::KeyPoint> subKp;
        cv::Mat subDesc;
        for (size_t i = 0; i < kp_.size(); ++i)
        {
            const cv::Point2f &p = kp_[i].pt;
            if (p.x >= rx && p.x < rx + rw && p.y >= ry && p.y < ry + rh)
            {
                subKp.push_back(kp_[i]);
                subDesc.push_back(desc_.row((int)i));
            }
        }
        if (subKp.empty())
            return false;
        int good = 0;
        return locateTemplateSIFT(subDesc, subKp, smallMap, threshold, cx, cy, conf, &good);
    }

    void setParameters(int maxFeatures, double ratio, int minMatches)
    {
        bool recompute = (maxFeatures > 0 && maxFeatures != maxFeatures_);
        maxFeatures_ = maxFeatures > 0 ? maxFeatures : maxFeatures_;
        ratio_ = ratio > 0 ? ratio : ratio_;
        minMatches_ = minMatches > 0 ? minMatches : minMatches_;
        if (recompute)
            computeFeatures();
    }

    void getMapInfo(int *width, int *height, int *feature_count) const
    {
        if (width) *width = largeMap_.cols;
        if (height) *height = largeMap_.rows;
        if (feature_count) *feature_count = (int)kp_.size();
    }

    void updateLargeMap(const cv::Mat &m)
    {
        largeMap_ = m;
        computeFeatures();
    }

private:
    void computeFeatures()
    {
        kp_.clear();
        desc_.release();
        if (largeMap_.empty())
            return;
        cv::Ptr<cv::SIFT> sift = cv::SIFT::create(maxFeatures_);
        sift->detectAndCompute(largeMap_, cv::noArray(), kp_, desc_);
    }

    cv::Mat largeMap_;
    std::vector<cv::KeyPoint> kp_;
    cv::Mat desc_;
    int maxFeatures_ = 2000;
    double ratio_ = 0.75;
    int minMatches_ = 8;
};

extern "C"
{

void *createMapMatcher(void *large_map_ptr)
{
    if (!isValidMat(large_map_ptr))
        return nullptr;
    return new MapMatcher(*toMat(large_map_ptr));
}

void *createMapMatcherFromFile(const char *large_map_path)
{
    if (!large_map_path)
        return nullptr;
    cv::Mat m = cv::imread(large_map_path, cv::IMREAD_COLOR);
    if (m.empty())
        return nullptr;
    return new MapMatcher(m);
}

void releaseMapMatcher(void *matcher_ptr)
{
    if (!matcher_ptr)
        return;
    delete static_cast<MapMatcher *>(matcher_ptr);
}

void findPositionInMap(void *matcher_ptr, void *small_map_ptr, double threshold,
                       double *center_x, double *center_y, double *confidence)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m || !isValidMat(small_map_ptr))
        return;
    m->findPosition(*toMat(small_map_ptr), threshold, center_x, center_y, confidence);
}

void findPositionByScreenshot(void *matcher_ptr, int x, int y, int x1, int y1, double threshold,
                              double *center_x, double *center_y, double *confidence)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m)
        return;
    void *shot = screenshotImpl(x, y, x1, y1);
    if (!isValidMat(shot))
        return;
    m->findPosition(*toMat(shot), threshold, center_x, center_y, confidence);
    delete toMat(shot);
}

void findBestPositionInMap(void *matcher_ptr, void **small_maps, int map_count, double threshold,
                           double *best_x, double *best_y, double *best_confidence, int *best_index)
{
    if (best_x) *best_x = -1;
    if (best_y) *best_y = -1;
    if (best_confidence) *best_confidence = 0;
    if (best_index) *best_index = -1;
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m || !small_maps || map_count <= 0)
        return;

    double bestConf = -1.0;
    int bestIdx = -1;
    double bx = -1, by = -1;
    for (int i = 0; i < map_count; ++i)
    {
        if (!isValidMat(small_maps[i]))
            continue;
        double cx = -1, cy = -1, conf = 0;
        if (m->findPosition(*toMat(small_maps[i]), threshold, &cx, &cy, &conf) && conf > bestConf)
        {
            bestConf = conf;
            bestIdx = i;
            bx = cx;
            by = cy;
        }
    }
    if (bestIdx >= 0)
    {
        if (best_x) *best_x = bx;
        if (best_y) *best_y = by;
        if (best_confidence) *best_confidence = bestConf;
        if (best_index) *best_index = bestIdx; // 0 基，Lua 端 +1
    }
}

void setMatcherParameters(void *matcher_ptr, int max_features, double ratio_threshold, int min_matches)
{
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m)
        return;
    m->setParameters(max_features, ratio_threshold, min_matches);
}

int getMapInfo(void *matcher_ptr, int *width, int *height, int *feature_count)
{
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m)
        return 0;
    m->getMapInfo(width, height, feature_count);
    return 1;
}

int updateLargeMap(void *matcher_ptr, void *new_large_map_ptr)
{
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m || !isValidMat(new_large_map_ptr))
        return 0;
    m->updateLargeMap(*toMat(new_large_map_ptr));
    return 1;
}

void findPositionInRegion(void *matcher_ptr, void *small_map_ptr,
                          int region_x, int region_y, int region_width, int region_height,
                          double threshold, double *center_x, double *center_y, double *confidence)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    auto *m = static_cast<MapMatcher *>(matcher_ptr);
    if (!m || !isValidMat(small_map_ptr))
        return;
    m->findPositionInRegion(*toMat(small_map_ptr), threshold,
                            region_x, region_y, region_width, region_height,
                            center_x, center_y, confidence);
}

} // extern "C"
