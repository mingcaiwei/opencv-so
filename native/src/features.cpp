// 特征检测与匹配：detectSIFT/ORB、matchFeatures、findImageBySIFT/ORB、
// templateMatchMultiScale、getLastMatchInfo，以及共享工具 locateTemplateSIFT/ORB
#include "common.h"

#include <opencv2/calib3d.hpp>

namespace
{
// locateTemplate 共用实现：BFMatcher + ratio test + 距离阈值 + findHomography(RANSAC)
// detector 为 SIFT/ORB 实例，normType 为 NORM_L2(SIFT) 或 NORM_HAMMING(ORB)
bool locateTemplateImpl(const cv::Mat &sceneDesc, const std::vector<cv::KeyPoint> &sceneKp,
                        const cv::Mat &tmplMat, double threshold, int normType,
                        cv::Feature2D *detector,
                        double *cx, double *cy, double *conf, int *good_count)
{
    if (cx) *cx = -1;
    if (cy) *cy = -1;
    if (conf) *conf = 0;
    if (good_count) *good_count = 0;
    if (sceneDesc.empty() || tmplMat.empty() || !detector)
        return false;

    const int kMinMatches = 8; // 单应求解所需的最小匹配数
    const double kRatio = 0.75;

    std::vector<cv::KeyPoint> tmplKp;
    cv::Mat tmplDesc;
    detector->detectAndCompute(tmplMat, cv::noArray(), tmplKp, tmplDesc);
    if (tmplDesc.empty() || tmplKp.empty())
        return false;

    cv::BFMatcher matcher(normType);
    std::vector<std::vector<cv::DMatch>> knn;
    matcher.knnMatch(tmplDesc, sceneDesc, knn, 2);

    std::vector<cv::Point2f> tmplPts, scenePts;
    for (const auto &pair : knn)
    {
        if (pair.size() < 2)
            continue;
        const cv::DMatch &m = pair[0];
        if (m.distance >= threshold)               // 距离阈值：越小越相似
            continue;
        if (m.distance > kRatio * pair[1].distance) // ratio test
            continue;
        tmplPts.push_back(tmplKp[m.queryIdx].pt);
        scenePts.push_back(sceneKp[m.trainIdx].pt);
    }

    int good = (int)tmplPts.size();
    if (good_count) *good_count = good;
    // confidence 归一化为 0-100 匹配率：良好匹配数 / 模板特征点数 × 100（100=模板特征全部命中）
    if (conf) *conf = tmplKp.empty() ? 0.0 : (double)good / (double)tmplKp.size() * 100.0;
    if (good < kMinMatches)
        return false;

    cv::Mat H = cv::findHomography(tmplPts, scenePts, cv::RANSAC, 5.0);
    if (H.empty())
        return false;

    // 模板中心映射到场景坐标
    std::vector<cv::Point2f> tmplCenter = {
        cv::Point2f(tmplMat.cols / 2.0f, tmplMat.rows / 2.0f)};
    std::vector<cv::Point2f> sceneCenter;
    cv::perspectiveTransform(tmplCenter, sceneCenter, H);
    if (sceneCenter.empty())
        return false;

    if (cx) *cx = sceneCenter[0].x;
    if (cy) *cy = sceneCenter[0].y;
    return true;
}
} // namespace

// 共享工具导出（供 matcher 复用）
bool locateTemplateSIFT(const cv::Mat &sceneDesc, const std::vector<cv::KeyPoint> &sceneKp,
                        const cv::Mat &tmplMat, double threshold,
                        double *cx, double *cy, double *conf, int *good_count)
{
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create(800);
    return locateTemplateImpl(sceneDesc, sceneKp, tmplMat, threshold, cv::NORM_L2,
                              sift.get(), cx, cy, conf, good_count);
}

bool locateTemplateORB(const cv::Mat &sceneDesc, const std::vector<cv::KeyPoint> &sceneKp,
                       const cv::Mat &tmplMat, double threshold,
                       double *cx, double *cy, double *conf, int *good_count)
{
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    return locateTemplateImpl(sceneDesc, sceneKp, tmplMat, threshold, cv::NORM_HAMMING,
                              orb.get(), cx, cy, conf, good_count);
}

extern "C"
{

// SIFT 检测：返回描述子 Mat 指针，写 keypoint 数
void *detectSIFT(void *src, int *keypoint_count)
{
    if (keypoint_count) *keypoint_count = 0;
    if (!isValidMat(src))
        return nullptr;
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create(800);
    std::vector<cv::KeyPoint> kp;
    cv::Mat *desc = new cv::Mat();
    sift->detectAndCompute(*toMat(src), cv::noArray(), kp, *desc);
    if (keypoint_count) *keypoint_count = (int)kp.size();
    return fromMat(desc);
}

// ORB 检测：返回描述子 Mat 指针，写 keypoint 数
void *detectORB(void *src, int *keypoint_count)
{
    if (keypoint_count) *keypoint_count = 0;
    if (!isValidMat(src))
        return nullptr;
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    std::vector<cv::KeyPoint> kp;
    cv::Mat *desc = new cv::Mat();
    orb->detectAndCompute(*toMat(src), cv::noArray(), kp, *desc);
    if (keypoint_count) *keypoint_count = (int)kp.size();
    return fromMat(desc);
}

// 描述子匹配：返回占位 Mat（Lua 未封装返回值），写 good 匹配数
void *matchFeatures(void *desc1, void *desc2, double threshold, int *match_count)
{
    if (match_count) *match_count = 0;
    if (!isValidMat(desc1) || !isValidMat(desc2))
        return nullptr;
    cv::Mat *d1 = toMat(desc1);
    cv::Mat *d2 = toMat(desc2);
    if (d1->empty() || d2->empty())
        return fromMat(new cv::Mat());

    cv::BFMatcher matcher(d1->type() == CV_8U ? cv::NORM_HAMMING : cv::NORM_L2);
    std::vector<cv::DMatch> matches;
    matcher.match(*d1, *d2, matches);
    int good = 0;
    for (const auto &m : matches)
        if (m.distance < threshold)
            ++good;
    if (match_count) *match_count = good;
    return fromMat(new cv::Mat());
}

// SIFT 找图：在场景中定位模板中心
void findImageBySIFT(void *scene, void *template_img, double threshold,
                     double *center_x, double *center_y, double *confidence)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    if (!isValidMat(scene) || !isValidMat(template_img))
    {
        g_lastMatch = {0, 0, 0};
        return;
    }
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create(800);
    std::vector<cv::KeyPoint> sceneKp;
    cv::Mat sceneDesc;
    sift->detectAndCompute(*toMat(scene), cv::noArray(), sceneKp, sceneDesc);

    int good = 0;
    double conf = 0;
    locateTemplateSIFT(sceneDesc, sceneKp, *toMat(template_img), threshold,
                       center_x, center_y, &conf, &good);
    if (confidence) *confidence = conf; // 回写置信度（=良好匹配数），修复此前输出参数遗漏
    g_lastMatch.confidence = conf;
    g_lastMatch.keypoints_count = (int)sceneKp.size();
    g_lastMatch.good_matches_count = good;
}

// ORB 找图
void findImageByORB(void *scene, void *template_img, double threshold,
                    double *center_x, double *center_y, double *confidence)
{
    if (center_x) *center_x = -1;
    if (center_y) *center_y = -1;
    if (confidence) *confidence = 0;
    if (!isValidMat(scene) || !isValidMat(template_img))
    {
        g_lastMatch = {0, 0, 0};
        return;
    }
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    std::vector<cv::KeyPoint> sceneKp;
    cv::Mat sceneDesc;
    orb->detectAndCompute(*toMat(scene), cv::noArray(), sceneKp, sceneDesc);

    int good = 0;
    double conf = 0;
    locateTemplateORB(sceneDesc, sceneKp, *toMat(template_img), threshold,
                      center_x, center_y, &conf, &good);
    if (confidence) *confidence = conf; // 回写置信度（=良好匹配数），修复此前输出参数遗漏
    g_lastMatch.confidence = conf;
    g_lastMatch.keypoints_count = (int)sceneKp.size();
    g_lastMatch.good_matches_count = good;
}

// 多尺度模板匹配：循环缩放模板，取最优匹配位置（中心坐标）
void templateMatchMultiScale(void *scene, void *template_img, int method,
                             double scale_start, double scale_end, double scale_step,
                             double *best_x, double *best_y, double *match_value, double *best_scale)
{
    if (best_x) *best_x = -1;
    if (best_y) *best_y = -1;
    if (match_value) *match_value = 0;
    if (best_scale) *best_scale = 1.0;
    if (!isValidMat(scene) || !isValidMat(template_img))
        return;

    cv::Mat sceneMat = *toMat(scene);
    cv::Mat tmplMat = *toMat(template_img);
    if (sceneMat.empty() || tmplMat.empty())
        return;

    // SQDIFF 系列：值越小越好；其余越大越好
    bool smallerIsBetter = (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED);
    double bestVal = smallerIsBetter ? 1e18 : -1e18;
    bool found = false;

    if (scale_step <= 0)
        scale_step = 1.0; // 防止死循环，退化为单尺度
    for (double s = scale_start; s <= scale_end + 1e-9; s += scale_step)
    {
        if (s <= 0)
            continue;
        cv::Mat resized;
        cv::resize(tmplMat, resized, cv::Size(), s, s, cv::INTER_LINEAR);
        if (resized.cols > sceneMat.cols || resized.rows > sceneMat.rows)
            continue;

        cv::Mat result;
        cv::matchTemplate(sceneMat, resized, result, method);
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        double val = smallerIsBetter ? minVal : maxVal;
        cv::Point loc = smallerIsBetter ? minLoc : maxLoc;

        bool better = smallerIsBetter ? (val < bestVal) : (val > bestVal);
        if (better)
        {
            bestVal = val;
            if (best_x) *best_x = loc.x + resized.cols / 2.0;
            if (best_y) *best_y = loc.y + resized.rows / 2.0;
            if (best_scale) *best_scale = s;
            found = true;
        }
    }

    if (match_value) *match_value = found ? bestVal : 0;
    if (!found)
    {
        if (best_x) *best_x = -1;
        if (best_y) *best_y = -1;
    }
}

// 读取最近一次特征匹配的详细信息
int getLastMatchInfo(double *confidence, int *keypoints_count, int *good_matches_count)
{
    if (confidence) *confidence = g_lastMatch.confidence;
    if (keypoints_count) *keypoints_count = g_lastMatch.keypoints_count;
    if (good_matches_count) *good_matches_count = g_lastMatch.good_matches_count;
    return 1;
}

} // extern "C"
