// 地图拼接器：将连续截图/图像拼接到大画布，支持 SIFT/ORB/模板三种拼接方法
// 与实时拼接（后台线程周期截图）
#include "common.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>
#include <dirent.h>
#include <strings.h>
#include <cstring>

class MapStitcher
{
public:
    MapStitcher(int mapSize, double scaleFactor, int blockSize, int method)
        : mapSize_(mapSize > 0 ? mapSize : 2048),
          scaleFactor_(scaleFactor > 0 ? scaleFactor : 0.5),
          blockSize_(blockSize > 0 ? blockSize : 100),
          method_(method)
    {
        resetCanvas();
    }

    ~MapStitcher()
    {
        stopRealtime();
    }

    void reset()
    {
        stopRealtime();
        resetCanvas();
    }

    // 核心拼接：返回是否成功贴入
    bool addImage(const cv::Mat &img)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (img.empty())
        {
            ++imageCount_;
            return false;
        }
        cv::Mat scaled;
        cv::resize(img, scaled, cv::Size(), scaleFactor_, scaleFactor_, cv::INTER_LINEAR);
        if (scaled.empty())
        {
            ++imageCount_;
            return false;
        }

        if (imageCount_ == 0 || lastImg_.empty())
        {
            // 首张：贴到画布中心
            int x = mapSize_ / 2 - scaled.cols / 2;
            int y = mapSize_ / 2 - scaled.rows / 2;
            pasteToCanvas(scaled, x, y);
            lastImg_ = scaled.clone();
            currentX_ = x + scaled.cols / 2;
            currentY_ = y + scaled.rows / 2;
            successCount_ = 1;
            imageCount_ = 1;
            return true;
        }

        // 后续：在 lastImg_ 中定位新图中心，计算偏移并贴入
        cv::Mat matchImg = scaled;
        cv::Rect cropRect;
        if (cropRatio_ > 0 && cropRatio_ < 1.0)
        {
            int cw = (int)(scaled.cols * cropRatio_);
            int ch = (int)(scaled.rows * cropRatio_);
            int cx = (scaled.cols - cw) / 2;
            int cy = (scaled.rows - ch) / 2;
            if (cw > 16 && ch > 16)
            {
                cropRect = cv::Rect(cx, cy, cw, ch);
                matchImg = scaled(cropRect);
            }
        }

        double mx = -1, my = -1;
        bool ok = locate(matchImg, &mx, &my);
        ++imageCount_;
        if (!ok)
            return false;

        // matchImg 中心 == scaled 中心（中心裁剪保持中心），故 mx,my 即新图中心在 lastImg_ 中的坐标
        int newX = (int)(currentX_ - lastImg_.cols / 2.0 + mx);
        int newY = (int)(currentY_ - lastImg_.rows / 2.0 + my);
        int topLeftX = newX - scaled.cols / 2;
        int topLeftY = newY - scaled.rows / 2;
        pasteToCanvas(scaled, topLeftX, topLeftY);
        lastImg_ = scaled.clone();
        currentX_ = newX;
        currentY_ = newY;
        ++successCount_;
        return true;
    }

    void getInfo(int *image_count, int *success_count, int *current_x, int *current_y) const
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (image_count) *image_count = imageCount_;
        if (success_count) *success_count = successCount_;
        if (current_x) *current_x = currentX_;
        if (current_y) *current_y = currentY_;
    }

    cv::Mat getResult() const
    {
        std::lock_guard<std::mutex> lk(mutex_);
        return canvas_.clone();
    }

    void setParameters(double sift, double orb, double tmpl, float crop_ratio)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        siftThresh_ = sift > 0 ? sift : siftThresh_;
        orbThresh_ = orb > 0 ? orb : orbThresh_;
        tmplThresh_ = tmpl > 0 ? tmpl : tmplThresh_;
        cropRatio_ = (crop_ratio > 0 && crop_ratio <= 1.0f) ? crop_ratio : cropRatio_;
    }

    // 实时拼接：记录截图区域供线程使用
    void setScreenshotRect(int x, int y, int x1, int y1)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        rtRect_ = {x, y, x1, y1};
    }

    bool startRealtime(int interval_ms)
    {
        if (rtRunning_.load())
            return true;
        rtIntervalMs_ = interval_ms > 0 ? interval_ms : 2000;
        rtRunning_.store(true);
        rtThread_ = std::thread(&MapStitcher::realtimeLoop, this);
        return true;
    }

    void stopRealtime()
    {
        if (!rtRunning_.load())
            return;
        rtRunning_.store(false);
        if (rtThread_.joinable())
            rtThread_.join();
    }

    bool isRealtimeRunning() const { return rtRunning_.load(); }

private:
    void resetCanvas()
    {
        canvas_ = cv::Mat::zeros(mapSize_, mapSize_, CV_8UC3);
        lastImg_.release();
        currentX_ = mapSize_ / 2;
        currentY_ = mapSize_ / 2;
        imageCount_ = 0;
        successCount_ = 0;
    }

    // 将 src 贴到 canvas_ 的 (x,y)（左上角），越界自动裁剪
    void pasteToCanvas(const cv::Mat &src, int x, int y)
    {
        int x0 = std::max(x, 0);
        int y0 = std::max(y, 0);
        int x1 = std::min(x + src.cols, mapSize_);
        int y1 = std::min(y + src.rows, mapSize_);
        int w = x1 - x0;
        int h = y1 - y0;
        if (w <= 0 || h <= 0)
            return;
        cv::Rect srcRoi(x0 - x, y0 - y, w, h);
        cv::Rect dstRoi(x0, y0, w, h);
        src(srcRoi).copyTo(canvas_(dstRoi));
    }

    // 在 lastImg_ 中定位 matchImg 中心，写入 mx,my。成功返回 true
    bool locate(const cv::Mat &matchImg, double *mx, double *my)
    {
        if (lastImg_.empty() || matchImg.empty())
            return false;
        if (method_ == 0) // STITCH_SIFT
        {
            cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
            std::vector<cv::KeyPoint> kp;
            cv::Mat desc;
            sift->detectAndCompute(lastImg_, cv::noArray(), kp, desc);
            int good = 0;
            double conf = 0;
            if (locateTemplateSIFT(desc, kp, matchImg, siftThresh_, mx, my, &conf, &good))
                return true;
        }
        else if (method_ == 1) // STITCH_ORB
        {
            cv::Ptr<cv::ORB> orb = cv::ORB::create();
            std::vector<cv::KeyPoint> kp;
            cv::Mat desc;
            orb->detectAndCompute(lastImg_, cv::noArray(), kp, desc);
            int good = 0;
            double conf = 0;
            if (locateTemplateORB(desc, kp, matchImg, orbThresh_, mx, my, &conf, &good))
                return true;
        }
        else // STITCH_TEMPLATE
        {
            if (matchImg.cols > lastImg_.cols || matchImg.rows > lastImg_.rows)
                return false;
            cv::Mat result;
            cv::matchTemplate(lastImg_, matchImg, result, cv::TM_CCOEFF_NORMED);
            double maxVal;
            cv::Point maxLoc;
            cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);
            if (maxVal >= tmplThresh_)
            {
                if (mx) *mx = maxLoc.x + matchImg.cols / 2.0;
                if (my) *my = maxLoc.y + matchImg.rows / 2.0;
                return true;
            }
        }
        return false;
    }

    void realtimeLoop()
    {
        while (rtRunning_.load())
        {
            // 分段睡眠以便及时响应停止
            int slept = 0;
            while (slept < rtIntervalMs_ && rtRunning_.load())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                slept += 100;
            }
            if (!rtRunning_.load())
                break;
            Rect r;
            {
                std::lock_guard<std::mutex> lk(mutex_);
                r = rtRect_;
            }
            if (r.x1 > r.x && r.y1 > r.y)
            {
                void *shot = screenshotImpl(r.x, r.y, r.x1, r.y1);
                if (isValidMat(shot))
                {
                    addImage(*toMat(shot));
                    delete toMat(shot);
                }
            }
        }
    }

    struct Rect { int x, y, x1, y1; };

    cv::Mat canvas_;
    cv::Mat lastImg_;
    int mapSize_;
    double scaleFactor_;
    int blockSize_;
    int method_;
    double siftThresh_ = 100.0;
    double orbThresh_ = 50.0;
    double tmplThresh_ = 0.8;
    float cropRatio_ = 0.6f;
    int currentX_ = 0;
    int currentY_ = 0;
    int imageCount_ = 0;
    int successCount_ = 0;
    Rect rtRect_ = {0, 0, 0, 0};

    std::thread rtThread_;
    std::atomic<bool> rtRunning_{false};
    int rtIntervalMs_ = 2000;
    mutable std::mutex mutex_;
};

extern "C"
{

void *createMapStitcher(int map_size, double scale_factor, int block_size, int stitch_method)
{
    return new MapStitcher(map_size, scale_factor, block_size, stitch_method);
}

void releaseMapStitcher(void *stitcher_ptr)
{
    if (!stitcher_ptr)
        return;
    delete static_cast<MapStitcher *>(stitcher_ptr);
}

void resetMapStitcher(void *stitcher_ptr)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (s)
        s->reset();
}

int addImageToStitcher(void *stitcher_ptr, const char *image_path)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s || !image_path)
        return 0;
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty())
        return 0;
    return s->addImage(img) ? 1 : 0;
}

int addMatToStitcher(void *stitcher_ptr, void *mat_ptr)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s || !isValidMat(mat_ptr))
        return 0;
    return s->addImage(toMat(mat_ptr)->clone()) ? 1 : 0;
}

int addScreenshotToStitcher(void *stitcher_ptr, int x, int y, int x1, int y1)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s)
        return 0;
    void *shot = screenshotImpl(x, y, x1, y1);
    if (!isValidMat(shot))
        return 0;
    // 记录截图区域供实时拼接复用
    s->setScreenshotRect(x, y, x1, y1);
    bool ok = s->addImage(toMat(shot)->clone());
    delete toMat(shot);
    return ok ? 1 : 0;
}

int addImageArrayToStitcher(void *stitcher_ptr, const char **image_paths, int path_count)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s || !image_paths || path_count <= 0)
        return 0;
    int ok = 0;
    for (int i = 0; i < path_count; ++i)
    {
        if (!image_paths[i])
            continue;
        cv::Mat img = cv::imread(image_paths[i], cv::IMREAD_COLOR);
        if (!img.empty() && s->addImage(img))
            ++ok;
    }
    return ok;
}

int addImageFolderToStitcher(void *stitcher_ptr, const char *folder_path, const char *file_extension)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s || !folder_path)
        return 0;
    DIR *dir = opendir(folder_path);
    if (!dir)
        return 0;
    std::string folder = folder_path;
    if (folder.back() != '/')
        folder += '/';
    std::string ext = file_extension ? file_extension : "";
    int ok = 0;
    struct dirent *ent;
    while ((ent = readdir(dir)) != nullptr)
    {
        if (ent->d_type != DT_REG && ent->d_type != DT_UNKNOWN)
            continue;
        std::string name = ent->d_name;
        if (name == "." || name == "..")
            continue;
        if (!ext.empty())
        {
            // 扩展名匹配（大小写不敏感）
            if (name.size() < ext.size())
                continue;
            std::string tail = name.substr(name.size() - ext.size());
            if (strcasecmp(tail.c_str(), ext.c_str()) != 0)
                continue;
        }
        cv::Mat img = cv::imread(folder + name, cv::IMREAD_COLOR);
        if (!img.empty() && s->addImage(img))
            ++ok;
    }
    closedir(dir);
    return ok;
}

void *getCurrentStitchResult(void *stitcher_ptr)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s)
        return nullptr;
    return fromMat(new cv::Mat(s->getResult()));
}

int saveStitchResult(void *stitcher_ptr, const char *output_path)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s || !output_path)
        return 0;
    return cv::imwrite(output_path, s->getResult()) ? 1 : 0;
}

int getStitchInfo(void *stitcher_ptr, int *image_count, int *success_count, int *current_x, int *current_y)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s)
        return 0;
    s->getInfo(image_count, success_count, current_x, current_y);
    return 1;
}

void setStitchParameters(void *stitcher_ptr, double sift_threshold, double orb_threshold,
                         double template_threshold, float crop_ratio)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (s)
        s->setParameters(sift_threshold, orb_threshold, template_threshold, crop_ratio);
}

int startRealtimeStitching(void *stitcher_ptr, int screenshot_interval_ms)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s)
        return 0;
    return s->startRealtime(screenshot_interval_ms) ? 1 : 0;
}

void stopRealtimeStitching(void *stitcher_ptr)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (s)
        s->stopRealtime();
}

int getRealtimeStitchStatus(void *stitcher_ptr)
{
    auto *s = static_cast<MapStitcher *>(stitcher_ptr);
    if (!s)
        return 0;
    return s->isRealtimeRunning() ? 1 : 0;
}

} // extern "C"
