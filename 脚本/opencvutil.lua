---@diagnostic disable: undefined-global
-- OpenCV完整封装库
-- 包含所有FFI接口的Lua封装，提供简洁易用的API
-- 作者: 苏御
-- 版本: 1.0

local ffi = require("ffi")

-- 定义所有FFI接口
ffi.cdef [[
    // 基础图像操作
    void* screenshot(int x, int y, int x1, int y1);
    const char* getScreenshotError();
    const char* dumpLuaEngineMethods();
    void* loadImage(const char* filepath);
    int saveMat(void* mat_ptr, const char* filepath);
    void releaseMat(void* mat_ptr);
    void* cloneMat(void* mat_ptr);
    int getMatWidth(void* mat_ptr);
    int getMatHeight(void* mat_ptr);
    int getMatChannels(void* mat_ptr);

    // 图像处理
    void* cvtColor(void* src, int code);
    void* convertToGray(void* mat_ptr);
    void* resize(void* src, int width, int height, int interpolation);
    void* threshold(void* src, double thresh, double maxval, int type);
    void* gaussianBlur(void* src, int ksize, double sigmaX, double sigmaY);
    void* cannyEdge(void* mat_ptr, double threshold1, double threshold2, int aperture_size);
    void* bilateralFilter(void* src, int d, double sigmaColor, double sigmaSpace);

     // 形态学操作
     void* dilate(void* mat_ptr, int kernel_size, int iterations);
     void* erode(void* mat_ptr, int kernel_size, int iterations);
     void* morphologyOpen(void* mat_ptr, int kernel_size, int iterations);
     void* morphologyClose(void* mat_ptr, int kernel_size, int iterations);
     void* morphologyTophat(void* mat_ptr, int kernel_size);
     void* morphologyBlackhat(void* mat_ptr, int kernel_size);
     void* morphologyGradient(void* mat_ptr, int kernel_size);


    // 几何变换
    void* rotate(void* src, double angle, double scale);
    void* flip(void* src, int flipCode);
    void* crop(void* src, int x, int y, int width, int height);
    void* warpAffine(void* src, double* matrix, int width, int height);
    void* warpPerspective(void* src, double* matrix, int width, int height);

    // 特征检测与匹配
    void* detectSIFT(void* src, int* keypoint_count);
    void* detectORB(void* src, int* keypoint_count);
    void* matchFeatures(void* desc1, void* desc2, double threshold, int* match_count);
    void findImageBySIFT(void* scene, void* template_img, double threshold,
                        double* center_x, double* center_y, double* confidence);
    void findImageByORB(void* scene, void* template_img, double threshold,
                       double* center_x, double* center_y, double* confidence);
    void templateMatchMultiScale(void* scene, void* template_img, int method,
                                 double scale_start, double scale_end, double scale_step,
                                 double* best_x, double* best_y, double* match_value, double* best_scale);
    int getLastMatchInfo(double* confidence, int* keypoints_count, int* good_matches_count);

    // 寻路导航专用SIFT匹配
    void* createMapMatcher(void* large_map_ptr);
    void* createMapMatcherFromFile(const char* large_map_path);
    void releaseMapMatcher(void* matcher_ptr);
    void findPositionInMap(void* matcher_ptr, void* small_map_ptr, double threshold,
                          double* center_x, double* center_y, double* confidence);
    void findPositionByScreenshot(void* matcher_ptr, int x, int y, int x1, int y1, double threshold,
                                 double* center_x, double* center_y, double* confidence);
    void findBestPositionInMap(void* matcher_ptr, void** small_maps, int map_count, double threshold,
                              double* best_x, double* best_y, double* best_confidence, int* best_index);
    void setMatcherParameters(void* matcher_ptr, int max_features, double ratio_threshold, int min_matches);
    int getMapInfo(void* matcher_ptr, int* width, int* height, int* feature_count);
    int updateLargeMap(void* matcher_ptr, void* new_large_map_ptr);
    void findPositionInRegion(void* matcher_ptr, void* small_map_ptr,
                             int region_x, int region_y, int region_width, int region_height,
                             double threshold, double* center_x, double* center_y, double* confidence);

    // 多尺度匹配器
    void* createMultiScaleMatcher(void* large_map_ptr, double* scales, int scale_count);
    void findPositionMultiScale(void* multi_matcher_ptr, void* small_map_ptr, double threshold,
                               double* center_x, double* center_y, double* confidence, double* best_scale);
    void releaseMultiScaleMatcher(void* multi_matcher_ptr);

    // 地图拼接功能
    void* createMapStitcher(int map_size, double scale_factor, int block_size, int stitch_method);
    void releaseMapStitcher(void* stitcher_ptr);
    void resetMapStitcher(void* stitcher_ptr);
    int addImageToStitcher(void* stitcher_ptr, const char* image_path);
    int addMatToStitcher(void* stitcher_ptr, void* mat_ptr);
    int addScreenshotToStitcher(void* stitcher_ptr, int x, int y, int x1, int y1);
    int addImageArrayToStitcher(void* stitcher_ptr, const char** image_paths, int path_count);
    int addImageFolderToStitcher(void* stitcher_ptr, const char* folder_path, const char* file_extension);
    void* getCurrentStitchResult(void* stitcher_ptr);
    int saveStitchResult(void* stitcher_ptr, const char* output_path);
    int getStitchInfo(void* stitcher_ptr, int* image_count, int* success_count, int* current_x, int* current_y);
    void setStitchParameters(void* stitcher_ptr, double sift_threshold, double orb_threshold,
                            double template_threshold, float crop_ratio);
    int startRealtimeStitching(void* stitcher_ptr, int screenshot_interval_ms);
    void stopRealtimeStitching(void* stitcher_ptr);
    int getRealtimeStitchStatus(void* stitcher_ptr);
]]

local workDir = getWorkPath()
print("工作目录: " .. workDir)

-- 最接近原始的代码！
local function getSoPath(soname)
	local work = getWorkPath() .. "/../bin/界面/libs"
	local type = getCpuArch()
	print("CPU类型: " .. tostring(type))
	
	if type == 3 then
		-- x86_64 特殊处理：强制用 x86，或者试试 x86_64
		local path1 = work .. "/x86_64/" .. soname
		print("尝试 x86_64: " .. path1)
		local ok1, lib1 = pcall(ffi.load, path1)
		if ok1 and lib1 then
			return lib1
		end
		
		local path2 = work .. "/x86/" .. soname
		print("尝试 x86: " .. path2)
		local ok2, lib2 = pcall(ffi.load, path2)
		if ok2 and lib2 then
			return lib2
		end
	elseif type == 0 then
		work = work .. "/x86/" .. soname
	elseif type == 1 then
		work = work .. "/armeabi-v7a/" .. soname
	elseif type == 2 then
		work = work .. "/arm64-v8a/" .. soname
	end
	
	print("尝试路径: " .. work)
	return ffi.load(work)
end

local cv_lib = nil
local ok, lib = pcall(getSoPath, "libsy.so")

if ok and lib then
	cv_lib = lib
	print("✓ 成功加载!")
else
	print("✗ 原始方法失败，尝试解压资源!")
	
	extractAssets("opencv.rc", getWorkPath() .. "/", "*.*")
	
	local try1, lib1 = pcall(ffi.load, getWorkPath() .. "/res/libsy.so")
	if try1 and lib1 then
		cv_lib = lib1
		print("✓ 从res加载成功!")
	else
		error("所有加载方法都失败了！")
	end
end
-- 创建OpenCV封装对象
local OpenCV = {}

-- 常量定义
OpenCV.COLOR_BGR2GRAY = 6
OpenCV.COLOR_BGR2RGB = 4
OpenCV.COLOR_GRAY2BGR = 8
OpenCV.COLOR_RGB2BGR = 4

OpenCV.THRESH_BINARY = 0
OpenCV.THRESH_BINARY_INV = 1
OpenCV.THRESH_TRUNC = 2
OpenCV.THRESH_TOZERO = 3
OpenCV.THRESH_TOZERO_INV = 4

OpenCV.INTER_NEAREST = 0
OpenCV.INTER_LINEAR = 1
OpenCV.INTER_CUBIC = 2
OpenCV.INTER_LANCZOS4 = 4

OpenCV.MORPH_ERODE = 0
OpenCV.MORPH_DILATE = 1
OpenCV.MORPH_OPEN = 2
OpenCV.MORPH_CLOSE = 3
OpenCV.MORPH_GRADIENT = 4
OpenCV.MORPH_TOPHAT = 5
OpenCV.MORPH_BLACKHAT = 6

OpenCV.TM_SQDIFF = 0
OpenCV.TM_SQDIFF_NORMED = 1
OpenCV.TM_CCORR = 2
OpenCV.TM_CCORR_NORMED = 3
OpenCV.TM_CCOEFF = 4
OpenCV.TM_CCOEFF_NORMED = 5

OpenCV.STITCH_SIFT = 0
OpenCV.STITCH_ORB = 1
OpenCV.STITCH_TEMPLATE = 2

-- 模板匹配多尺度参数（可调：范围越小越快，0.8~1.2 步长0.1 = 5个尺度，够大多数场景）
-- 若模板与截图比例差异大，可放宽如 OpenCV.SCALE_START=0.5 OpenCV.SCALE_END=2.0
OpenCV.SCALE_START = 0.8
OpenCV.SCALE_END   = 1.2
OpenCV.SCALE_STEP  = 0.1

-- 调试开关：设 true 打印截图/匹配耗时，定位性能瓶颈用
OpenCV.DEBUG = false
-- 文件法截图格式：true=JPEG(编码快3-5倍,有损)，false=PNG(无损,慢)；JPEG 不支持时自动回退 PNG
local _snapUseJpeg = true
-- JNI 截图方法列表是否已 dump 过（避免每次截图都 dump）
local _dumpedMethods = false

-- 辅助函数
local function isValid(ptr)
    return ptr ~= nil and ptr ~= ffi.cast("void*", 0)
end

local function checkMat(mat, func_name)
    if not isValid(mat) then
        error(func_name .. ": 无效的Mat对象")
    end
end

-- ================================
-- 基础图像操作
-- ================================

-- 屏幕截图
-- @param x: 左上角x坐标
-- @param y: 左上角y坐标
-- @param x1: 右下角x坐标
-- @param y1: 右下角y坐标
-- @return: 截图图像(Mat)
function OpenCV.screenshot(x, y, x1, y1)
    x = x or 0; y = y or 0; x1 = x1 or 0; y1 = y1 or 0
    local t0 = OpenCV.DEBUG and tickCount() or 0

    -- 路径 1：C 层 JNI 截图（已修复 native 线程 ClassLoader，直接返回 Mat，无文件 I/O、原生区域裁剪）
    -- 耗时约 20-40ms，是提速关键。需要 cf82f51 之后编译的 .so
    local ok, mat = pcall(cv_lib.screenshot, x, y, x1, y1)
    if ok and isValid(mat) then
        if OpenCV.DEBUG then
            print(string.format("[screenshot] JNI 截图 %dms (%d,%d,%d,%d)",
                tickCount() - t0, x, y, x1, y1))
        end
        return mat
    end
    if OpenCV.DEBUG then
        local err = "unknown"
        pcall(function() err = cv_lib.getScreenshotError() or "unknown" end)
        print(string.format("[screenshot] JNI 失败: %s", err))
        -- 首次失败时 dump LuaEngine 方法列表，帮助定位正确的截图方法名
        if not _dumpedMethods then
            _dumpedMethods = true
            local ok2, methods = pcall(cv_lib.dumpLuaEngineMethods)
            if ok2 and methods and #methods > 0 then
                print("[screenshot] LuaEngine 截图相关方法:\n" .. methods)
            end
        end
    end

    -- 路径 2：文件法（snapShot 存文件 + loadImage 读回 + crop）
    -- JPEG 编码比 PNG 快 3-5 倍；不支持时自动回退 PNG
    local ext = _snapUseJpeg and ".jpg" or ".png"
    local tmpPath = getWorkPath() .. "/_snap_tmp" .. ext
    snapShot(tmpPath)
    local full = cv_lib.loadImage(tmpPath)
    if not isValid(full) and _snapUseJpeg then
        os.remove(tmpPath)
        _snapUseJpeg = false
        ext = ".png"
        tmpPath = getWorkPath() .. "/_snap_tmp.png"
        snapShot(tmpPath)
        full = cv_lib.loadImage(tmpPath)
    end
    os.remove(tmpPath)
    if not isValid(full) then
        error("screenshot: 截图失败（JNI 与文件法均失败，检查截图服务/root权限）")
    end
    if OpenCV.DEBUG then
        print(string.format("[screenshot] 文件法(%s) 全屏截图+读取 %dms",
            ext, tickCount() - t0))
    end

    -- 区域裁剪
    local w = x1 - x
    local h = y1 - y
    if w > 0 and h > 0 then
        local cropped = cv_lib.crop(full, x, y, w, h)
        cv_lib.releaseMat(full)
        if not isValid(cropped) then
            error("screenshot: 区域裁剪失败")
        end
        if OpenCV.DEBUG then
            print(string.format("[screenshot] 裁剪区域 %dx%d 总耗时 %dms", w, h, tickCount() - t0))
        end
        return cropped
    end
    return full
end

-- 加载图像文件
-- @param filepath: 图像文件路径
-- @return: 图像(Mat)
function OpenCV.loadImage(filepath)
    local result = cv_lib.loadImage(filepath)
    if not isValid(result) then
        error("loadImage: 加载图像失败 - " .. filepath)
    end
    return result
end

-- 保存图像到文件
-- @param mat: 输入图像(Mat)
-- @param filepath: 保存路径
-- @return: 是否成功(boolean)
function OpenCV.saveMat(mat, filepath)
    checkMat(mat, "saveMat")
    return cv_lib.saveMat(mat, filepath) == 1
end

-- 释放Mat对象内存
-- @param mat: 要释放的Mat对象
function OpenCV.releaseMat(mat)
    if isValid(mat) then
        cv_lib.releaseMat(mat)
    end
end

-- 克隆Mat对象
-- @param mat: 输入图像(Mat)
-- @return: 克隆的图像(Mat)
function OpenCV.cloneMat(mat)
    checkMat(mat, "cloneMat")
    local result = cv_lib.cloneMat(mat)
    if not isValid(result) then
        error("cloneMat: 克隆失败")
    end
    return result
end

-- 获取图像宽度
-- @param mat: 输入图像(Mat)
-- @return: 图像宽度(number)
function OpenCV.getWidth(mat)
    checkMat(mat, "getWidth")
    return cv_lib.getMatWidth(mat)
end

-- 获取图像高度
-- @param mat: 输入图像(Mat)
-- @return: 图像高度(number)
function OpenCV.getHeight(mat)
    checkMat(mat, "getHeight")
    return cv_lib.getMatHeight(mat)
end

-- 获取图像通道数
-- @param mat: 输入图像(Mat)
-- @return: 通道数(number)
function OpenCV.getChannels(mat)
    checkMat(mat, "getChannels")
    return cv_lib.getMatChannels(mat)
end

-- 获取图像尺寸信息
-- @param mat: 输入图像(Mat)
-- @return: {width, height, channels}
function OpenCV.getSize(mat)
    checkMat(mat, "getSize")
    return {
        width = cv_lib.getMatWidth(mat),
        height = cv_lib.getMatHeight(mat),
        channels = cv_lib.getMatChannels(mat)
    }
end

-- ================================
-- 图像处理
-- ================================

-- 颜色空间转换
-- @param src: 输入图像(Mat)
-- @param code: 转换代码，如OpenCV.COLOR_BGR2GRAY
-- @return: 转换后的图像(Mat)
function OpenCV.cvtColor(src, code)
    checkMat(src, "cvtColor")
    local result = cv_lib.cvtColor(src, code or OpenCV.COLOR_BGR2GRAY)
    if not isValid(result) then
        error("cvtColor: 颜色转换失败")
    end
    return result
end


-- 灰度处理
-- @param src: 输入图像(Mat)
-- @param code: 转换代码，如OpenCV.COLOR_BGR2GRAY
-- @return: 转换后的图像(Mat)
function OpenCV.convertToGray(src)
    checkMat(src, "cvtColor")
    local result = cv_lib.convertToGray(src)
    if not isValid(result) then
        error("convertToGray: 灰度转换失败")
    end
    return result
end


-- 图像缩放
-- @param src: 输入图像(Mat)
-- @param width: 目标宽度
-- @param height: 目标高度
-- @param interpolation: 插值方法，默认OpenCV.INTER_LINEAR
-- @return: 缩放后的图像(Mat)
function OpenCV.resize(src, width, height, interpolation)
    checkMat(src, "resize")
    local result = cv_lib.resize(src, width, height, interpolation or OpenCV.INTER_LINEAR)
    if not isValid(result) then
        error("resize: 图像缩放失败")
    end
    return result
end

-- 二值化处理
-- @param src: 输入灰度图像(Mat)
-- @param thresh: 阈值，默认127
-- @param maxval: 最大值，默认255
-- @param type: 二值化类型，默认OpenCV.THRESH_BINARY
-- @return: 二值化图像(Mat)
function OpenCV.threshold(src, thresh, maxval, type)
    checkMat(src, "threshold")
    local result = cv_lib.threshold(src, thresh or 127, maxval or 255, type or OpenCV.THRESH_BINARY)
    if not isValid(result) then
        error("threshold: 二值化处理失败")
    end
    return result
end

-- 高斯模糊
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param sigmaX: X方向标准差，默认0
-- @param sigmaY: Y方向标准差，默认0
-- @return: 模糊后的图像(Mat)
function OpenCV.gaussianBlur(src, ksize, sigmaX, sigmaY)
    checkMat(src, "gaussianBlur")
    local result = cv_lib.gaussianBlur(src, ksize or 5, sigmaX or 0, sigmaY or 0)
    if not isValid(result) then
        error("gaussianBlur: 高斯模糊失败")
    end
    return result
end

-- 开操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 处理后的图像(Mat)
function OpenCV.morphologyOpen(src, ksize, iterations)
    checkMat(src, "morphologyOpen")
    local result = cv_lib.morphologyOpen(src,  ksize or 5, iterations or 1)
    if not isValid(result) then
        error("morphologyOpen: 开操作失败")
    end
    return result
end

-- 闭操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 处理后的图像(Mat)
function OpenCV.morphologyClose(src, ksize, iterations)
    checkMat(src, "morphologyClose")
    local result = cv_lib.morphologyClose(src,  ksize or 5, iterations or 1)
    if not isValid(result) then
        error("morphologyClose: 闭操作失败")
    end
    return result
end

--顶帽操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 处理后的图像(Mat)
function OpenCV.morphologyTophat(src, ksize, iterations)
    checkMat(src, "morphologyTophat")
    local result = cv_lib.morphologyTophat(src,  ksize or 5, iterations or 1)
    if not isValid(result) then
        error("morphologyTophat: 顶帽操作失败")
    end
    return result
end

-- 黑帽操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 处理后的图像(Mat)
function OpenCV.morphologyBlackhat(src, ksize, iterations)
    checkMat(src, "morphologyBlackhat")
    local result = cv_lib.morphologyBlackhat(src,  ksize or 5, iterations or 1)
    if not isValid(result) then
        error("morphologyBlackhat: 黑帽操作操作失败")
    end
    return result
end

-- 梯度操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 处理后的图像(Mat)
function OpenCV.morphologyGradient(src, ksize, iterations)
    checkMat(src, "morphologyGradient") 
    local result = cv_lib.morphologyGradient(src,  ksize or 5, iterations or 1) 
    if not isValid(result) then
        error("morphologyGradient: 梯度操作操作失败")
    end
    return result
end

-- Canny边缘检测
-- @param src: 输入灰度图像(Mat)
-- @param threshold1: 低阈值，默认50
-- @param threshold2: 高阈值，默认150
-- @param apertureSize: Sobel核大小，默认3
-- @return: 边缘图像(Mat)
function OpenCV.cannyEdge(src, threshold1, threshold2, apertureSize)
    checkMat(src, "cannyEdge")
    local result = cv_lib.cannyEdge(src, threshold1 or 50, threshold2 or 150,
        apertureSize or 3)
    if not isValid(result) then
        error("cannyEdge: 边缘检测失败")
    end
    return result
end

-- 膨胀操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 膨胀后的图像(Mat)
function OpenCV.dilate(src, ksize, iterations)
    checkMat(src, "dilate")
    local result = cv_lib.dilate(src, ksize or 5, iterations or 1)
    if not isValid(result) then
        error("dilate: 膨胀操作失败")
    end
    return result
end

-- 腐蚀操作
-- @param src: 输入图像(Mat)
-- @param ksize: 核大小，默认5
-- @param iterations: 迭代次数，默认1
-- @return: 腐蚀后的图像(Mat)
function OpenCV.erode(src, ksize, iterations)
    checkMat(src, "erode")
    local result = cv_lib.erode(src, ksize or 5, iterations or 1)
    if not isValid(result) then
        error("erode: 腐蚀操作失败")
    end
    return result
end

-- 双边滤波
-- @param src: 输入图像(Mat)
-- @param d: 像素邻域直径，默认9
-- @param sigmaColor: 颜色空间标准差，默认75
-- @param sigmaSpace: 坐标空间标准差，默认75
-- @return: 滤波后的图像(Mat)
function OpenCV.bilateralFilter(src, d, sigmaColor, sigmaSpace)
    checkMat(src, "bilateralFilter")
    local result = cv_lib.bilateralFilter(src, d or 9, sigmaColor or 75, sigmaSpace or 75)
    if not isValid(result) then
        error("bilateralFilter: 双边滤波失败")
    end
    return result
end

-- ================================
-- 几何变换
-- ================================

-- 图像旋转
-- @param src: 输入图像(Mat)
-- @param angle: 旋转角度(度)
-- @param scale: 缩放比例，默认1.0
-- @return: 旋转后的图像(Mat)
function OpenCV.rotate(src, angle, scale)
    checkMat(src, "rotate")
    local result = cv_lib.rotate(src, angle, scale or 1.0)
    if not isValid(result) then
        error("rotate: 图像旋转失败")
    end
    return result
end

-- 图像翻转
-- @param src: 输入图像(Mat)
-- @param flipCode: 翻转代码 (0=垂直翻转, 1=水平翻转, -1=水平垂直翻转)
-- @return: 翻转后的图像(Mat)
function OpenCV.flip(src, flipCode)
    checkMat(src, "flip")
    local result = cv_lib.flip(src, flipCode or 1)
    if not isValid(result) then
        error("flip: 图像翻转失败")
    end
    return result
end

-- 图像裁剪
-- @param src: 输入图像(Mat)
-- @param x: 裁剪区域左上角x坐标
-- @param y: 裁剪区域左上角y坐标
-- @param width: 裁剪区域宽度
-- @param height: 裁剪区域高度
-- @return: 裁剪后的图像(Mat)
function OpenCV.crop(src, x, y, width, height)
    checkMat(src, "crop")
    local result = cv_lib.crop(src, x, y, width, height)
    if not isValid(result) then
        error("crop: 图像裁剪失败")
    end
    return result
end

-- 仿射变换
-- @param src: 输入图像(Mat)
-- @param matrix: 2x3变换矩阵(table)
-- @param width: 输出图像宽度
-- @param height: 输出图像高度
-- @return: 变换后的图像(Mat)
function OpenCV.warpAffine(src, matrix, width, height)
    checkMat(src, "warpAffine")
    local mat_array = ffi.new("double[6]")
    for i = 1, 6 do
        mat_array[i - 1] = matrix[i] or 0
    end
    local result = cv_lib.warpAffine(src, mat_array, width, height)
    if not isValid(result) then
        error("warpAffine: 仿射变换失败")
    end
    return result
end

-- 透视变换
-- @param src: 输入图像(Mat)
-- @param matrix: 3x3变换矩阵(table)
-- @param width: 输出图像宽度
-- @param height: 输出图像高度
-- @return: 变换后的图像(Mat)
function OpenCV.warpPerspective(src, matrix, width, height)
    checkMat(src, "warpPerspective")
    local mat_array = ffi.new("double[9]")
    for i = 1, 9 do
        mat_array[i - 1] = matrix[i] or 0
    end
    local result = cv_lib.warpPerspective(src, mat_array, width, height)
    if not isValid(result) then
        error("warpPerspective: 透视变换失败")
    end
    return result
end

-- ================================
-- 特征检测与匹配
-- ================================

-- 使用SIFT在场景中查找模板
-- @param scene: 场景图像(Mat)
-- @param template_img: 模板图像(Mat)
-- @param threshold: 匹配阈值，默认100.0
-- @return: {center_x, center_y, confidence}
function OpenCV.findImageBySIFT(scene, template_img, threshold)
    checkMat(scene, "findImageBySIFT")
    checkMat(template_img, "findImageBySIFT")
    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")

    cv_lib.findImageBySIFT(scene, template_img, threshold or 100.0, center_x, center_y, confidence)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    -- C 层 findImageBySIFT 的 confidence 输出参数在旧 .so 未回写（恒 0），用 getLastMatchInfo 取真实良好匹配数
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = OpenCV.getLastMatchInfo().confidence,
        found = x >= 0 and y >= 0
    }
end

-- 使用ORB在场景中查找模板
-- @param scene: 场景图像(Mat)
-- @param template_img: 模板图像(Mat)
-- @param threshold: 匹配阈值，默认50.0
-- @return: {center_x, center_y, confidence}
function OpenCV.findImageByORB(scene, template_img, threshold)
    checkMat(scene, "findImageByORB")
    checkMat(template_img, "findImageByORB")
    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")

    cv_lib.findImageByORB(scene, template_img, threshold or 50.0, center_x, center_y, confidence)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    -- C 层 findImageByORB 的 confidence 输出参数在旧 .so 未回写（恒 0），用 getLastMatchInfo 取真实良好匹配数
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = OpenCV.getLastMatchInfo().confidence,
        found = x >= 0 and y >= 0
    }
end

-- 多尺度模板匹配
-- @param scene: 场景图像(Mat)
-- @param template_img: 模板图像(Mat)
-- @param method: 匹配方法，默认OpenCV.TM_CCOEFF_NORMED
-- @param scale_start: 起始缩放比例，默认0.5
-- @param scale_end: 结束缩放比例，默认2.0
-- @param scale_step: 缩放步长，默认0.1
-- @return: {x, y, match_value, scale}
function OpenCV.templateMatchMultiScale(scene, template_img, method, scale_start, scale_end, scale_step)
    checkMat(scene, "templateMatchMultiScale")
    checkMat(template_img, "templateMatchMultiScale")
    local best_x = ffi.new("double[1]")
    local best_y = ffi.new("double[1]")
    local match_value = ffi.new("double[1]")
    local best_scale = ffi.new("double[1]")

    cv_lib.templateMatchMultiScale(scene, template_img, method or OpenCV.TM_CCOEFF_NORMED,
        scale_start or 0.5, scale_end or 2.0, scale_step or 0.1,
        best_x, best_y, match_value, best_scale)

    local bx, by = tonumber(best_x[0]), tonumber(best_y[0])
    return {
        x = math.floor(bx + 0.5),
        y = math.floor(by + 0.5),
        match_value = tonumber(match_value[0]),
        scale = tonumber(best_scale[0]),
        found = bx >= 0 and by >= 0
    }
end

-- 获取最后一次匹配的详细信息
-- @return: {confidence, keypoints_count, good_matches_count}
function OpenCV.getLastMatchInfo()
    local confidence = ffi.new("double[1]")
    local keypoints_count = ffi.new("int[1]")
    local good_matches_count = ffi.new("int[1]")

    cv_lib.getLastMatchInfo(confidence, keypoints_count, good_matches_count)

    return {
        confidence = tonumber(confidence[0]),
        keypoints_count = tonumber(keypoints_count[0]),
        good_matches_count = tonumber(good_matches_count[0])
    }
end

-- ================================
-- 寻路导航专用SIFT匹配
-- ================================

-- 地图匹配器类
OpenCV.MapMatcher = {}

-- 创建地图匹配器(从Mat对象)
-- @param large_map: 大地图图像(Mat)
-- @return: 地图匹配器对象
function OpenCV.MapMatcher.create(large_map)
    checkMat(large_map, "MapMatcher.create")
    local matcher = cv_lib.createMapMatcher(large_map)
    if not isValid(matcher) then
        error("MapMatcher.create: 创建地图匹配器失败")
    end
    return matcher
end

-- 创建地图匹配器(从文件)
-- @param filepath: 大地图文件路径
-- @return: 地图匹配器对象
function OpenCV.MapMatcher.createFromFile(filepath)
    local matcher = cv_lib.createMapMatcherFromFile(filepath)
    if not isValid(matcher) then
        error("MapMatcher.createFromFile: 从文件创建地图匹配器失败 - " .. filepath)
    end
    return matcher
end

-- 释放地图匹配器
-- @param matcher: 地图匹配器对象
function OpenCV.MapMatcher.release(matcher)
    if isValid(matcher) then
        cv_lib.releaseMapMatcher(matcher)
    end
end

-- 在大地图中查找小地图位置
-- @param matcher: 地图匹配器对象
-- @param small_map: 小地图图像(Mat)
-- @param threshold: 匹配阈值，默认100.0
-- @return: {x, y, confidence, found}
function OpenCV.MapMatcher.findPosition(matcher, small_map, threshold)
    if not isValid(matcher) then
        error("MapMatcher.findPosition: 无效的匹配器对象")
    end
    checkMat(small_map, "MapMatcher.findPosition")

    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")

    cv_lib.findPositionInMap(matcher, small_map, threshold or 100.0, center_x, center_y, confidence)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = tonumber(confidence[0]),
        found = x >= 0 and y >= 0
    }
end

-- 通过截图查找位置
-- @param matcher: 地图匹配器对象
-- @param x: 截图左上角x坐标
-- @param y: 截图左上角y坐标
-- @param x1: 截图右下角x坐标
-- @param y1: 截图右下角y坐标
-- @param threshold: 匹配阈值，默认100.0
-- @return: {x, y, confidence, found}
function OpenCV.MapMatcher.findPositionByScreenshot(matcher, x, y, x1, y1, threshold)
    if not isValid(matcher) then
        error("MapMatcher.findPositionByScreenshot: 无效的匹配器对象")
    end

    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")

    cv_lib.findPositionByScreenshot(matcher, x, y, x1, y1, threshold or 100.0, center_x, center_y, confidence)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = tonumber(confidence[0]),
        found = x >= 0 and y >= 0
    }
end

-- 批量位置检测
-- @param matcher: 地图匹配器对象
-- @param small_maps: 小地图数组(table of Mat)
-- @param threshold: 匹配阈值，默认100.0
-- @return: {x, y, confidence, index, found}
function OpenCV.MapMatcher.findBestPosition(matcher, small_maps, threshold)
    if not isValid(matcher) then
        error("MapMatcher.findBestPosition: 无效的匹配器对象")
    end

    local map_count = #small_maps
    local c_maps = ffi.new("void*[?]", map_count)
    for i, map in ipairs(small_maps) do
        checkMat(map, "MapMatcher.findBestPosition")
        c_maps[i - 1] = map
    end

    local best_x = ffi.new("double[1]")
    local best_y = ffi.new("double[1]")
    local best_confidence = ffi.new("double[1]")
    local best_index = ffi.new("int[1]")

    cv_lib.findBestPositionInMap(matcher, c_maps, map_count, threshold or 100.0,
        best_x, best_y, best_confidence, best_index)

    local bx, by = tonumber(best_x[0]), tonumber(best_y[0])
    return {
        x = math.floor(bx + 0.5),
        y = math.floor(by + 0.5),
        confidence = tonumber(best_confidence[0]),
        index = tonumber(best_index[0]) + 1, -- 转换为Lua的1基索引
        found = tonumber(best_index[0]) >= 0
    }
end

-- 设置匹配器参数
-- @param matcher: 地图匹配器对象
-- @param max_features: 最大特征点数量，默认2000
-- @param ratio_threshold: 比值阈值，默认0.75
-- @param min_matches: 最小匹配点数量，默认8
function OpenCV.MapMatcher.setParameters(matcher, max_features, ratio_threshold, min_matches)
    if not isValid(matcher) then
        error("MapMatcher.setParameters: 无效的匹配器对象")
    end
    cv_lib.setMatcherParameters(matcher, max_features or 2000, ratio_threshold or 0.75, min_matches or 8)
end

-- 获取地图信息
-- @param matcher: 地图匹配器对象
-- @return: {width, height, feature_count}
function OpenCV.MapMatcher.getInfo(matcher)
    if not isValid(matcher) then
        error("MapMatcher.getInfo: 无效的匹配器对象")
    end

    local width = ffi.new("int[1]")
    local height = ffi.new("int[1]")
    local feature_count = ffi.new("int[1]")

    if cv_lib.getMapInfo(matcher, width, height, feature_count) == 1 then
        return {
            width = tonumber(width[0]),
            height = tonumber(height[0]),
            feature_count = tonumber(feature_count[0])
        }
    else
        error("MapMatcher.getInfo: 获取地图信息失败")
    end
end

-- 更新大地图
-- @param matcher: 地图匹配器对象
-- @param new_large_map: 新的大地图图像(Mat)
-- @return: 是否成功(boolean)
function OpenCV.MapMatcher.updateMap(matcher, new_large_map)
    if not isValid(matcher) then
        error("MapMatcher.updateMap: 无效的匹配器对象")
    end
    checkMat(new_large_map, "MapMatcher.updateMap")
    return cv_lib.updateLargeMap(matcher, new_large_map) == 1
end

-- 在指定区域内查找位置
-- @param matcher: 地图匹配器对象
-- @param small_map: 小地图图像(Mat)
-- @param region_x: 搜索区域左上角x坐标
-- @param region_y: 搜索区域左上角y坐标
-- @param region_width: 搜索区域宽度
-- @param region_height: 搜索区域高度
-- @param threshold: 匹配阈值，默认100.0
-- @return: {x, y, confidence, found}
function OpenCV.MapMatcher.findPositionInRegion(matcher, small_map, region_x, region_y, region_width, region_height,
                                                threshold)
    if not isValid(matcher) then
        error("MapMatcher.findPositionInRegion: 无效的匹配器对象")
    end
    checkMat(small_map, "MapMatcher.findPositionInRegion")

    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")

    cv_lib.findPositionInRegion(matcher, small_map, region_x, region_y, region_width, region_height,
        threshold or 100.0, center_x, center_y, confidence)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = tonumber(confidence[0]),
        found = x >= 0 and y >= 0
    }
end

-- ================================
-- 多尺度匹配器
-- ================================

-- 多尺度匹配器类
OpenCV.MultiScaleMatcher = {}

-- 创建多尺度匹配器
-- @param large_map: 大地图图像(Mat)
-- @param scales: 缩放比例数组(table)，如{0.5, 0.75, 1.0, 1.25}
-- @return: 多尺度匹配器对象
function OpenCV.MultiScaleMatcher.create(large_map, scales)
    checkMat(large_map, "MultiScaleMatcher.create")
    local scale_count = #scales
    local c_scales = ffi.new("double[?]", scale_count)
    for i, scale in ipairs(scales) do
        c_scales[i - 1] = scale
    end

    local matcher = cv_lib.createMultiScaleMatcher(large_map, c_scales, scale_count)
    if not isValid(matcher) then
        error("MultiScaleMatcher.create: 创建多尺度匹配器失败")
    end
    return matcher
end

-- 释放多尺度匹配器
-- @param matcher: 多尺度匹配器对象
function OpenCV.MultiScaleMatcher.release(matcher)
    if isValid(matcher) then
        cv_lib.releaseMultiScaleMatcher(matcher)
    end
end

-- 多尺度位置查找
-- @param matcher: 多尺度匹配器对象
-- @param small_map: 小地图图像(Mat)
-- @param threshold: 匹配阈值，默认100.0
-- @return: {x, y, confidence, scale, found}
function OpenCV.MultiScaleMatcher.findPosition(matcher, small_map, threshold)
    if not isValid(matcher) then
        error("MultiScaleMatcher.findPosition: 无效的匹配器对象")
    end
    checkMat(small_map, "MultiScaleMatcher.findPosition")

    local center_x = ffi.new("double[1]")
    local center_y = ffi.new("double[1]")
    local confidence = ffi.new("double[1]")
    local best_scale = ffi.new("double[1]")

    cv_lib.findPositionMultiScale(matcher, small_map, threshold or 100.0,
        center_x, center_y, confidence, best_scale)

    local x, y = tonumber(center_x[0]), tonumber(center_y[0])
    return {
        x = math.floor(x + 0.5),
        y = math.floor(y + 0.5),
        confidence = tonumber(confidence[0]),
        scale = tonumber(best_scale[0]),
        found = x >= 0 and y >= 0
    }
end

-- ================================
-- 地图拼接功能
-- ================================

-- 地图拼接器类
OpenCV.MapStitcher = {}

-- 创建地图拼接器
-- @param map_size: 拼接画布大小，默认2048
-- @param scale_factor: 图像缩放比例，默认0.5
-- @param block_size: 中心屏蔽区域大小，默认100
-- @param stitch_method: 拼接方法，默认OpenCV.STITCH_TEMPLATE
-- @return: 地图拼接器对象
function OpenCV.MapStitcher.create(map_size, scale_factor, block_size, stitch_method)
    local stitcher = cv_lib.createMapStitcher(map_size or 2048, scale_factor or 0.5,
        block_size or 100, stitch_method or OpenCV.STITCH_TEMPLATE)
    if not isValid(stitcher) then
        error("MapStitcher.create: 创建地图拼接器失败")
    end
    return stitcher
end

-- 释放地图拼接器
-- @param stitcher: 地图拼接器对象
function OpenCV.MapStitcher.release(stitcher)
    if isValid(stitcher) then
        cv_lib.releaseMapStitcher(stitcher)
    end
end

-- 重置地图拼接器
-- @param stitcher: 地图拼接器对象
function OpenCV.MapStitcher.reset(stitcher)
    if not isValid(stitcher) then
        error("MapStitcher.reset: 无效的拼接器对象")
    end
    cv_lib.resetMapStitcher(stitcher)
end

-- 添加图像到拼接器
-- @param stitcher: 地图拼接器对象
-- @param image_path: 图像文件路径
-- @return: 是否成功(boolean)
function OpenCV.MapStitcher.addImage(stitcher, image_path)
    if not isValid(stitcher) then
        error("MapStitcher.addImage: 无效的拼接器对象")
    end
    return cv_lib.addImageToStitcher(stitcher, image_path) == 1
end

-- 添加Mat对象到拼接器
-- @param stitcher: 地图拼接器对象
-- @param mat: 图像Mat对象
-- @return: 是否成功(boolean)
function OpenCV.MapStitcher.addMat(stitcher, mat)
    if not isValid(stitcher) then
        error("MapStitcher.addMat: 无效的拼接器对象")
    end
    checkMat(mat, "MapStitcher.addMat")
    return cv_lib.addMatToStitcher(stitcher, mat) == 1
end

-- 添加截图到拼接器
-- @param stitcher: 地图拼接器对象
-- @param x: 截图左上角x坐标
-- @param y: 截图左上角y坐标
-- @param x1: 截图右下角x坐标
-- @param y1: 截图右下角y坐标
-- @return: 是否成功(boolean)
function OpenCV.MapStitcher.addScreenshot(stitcher, x, y, x1, y1)
    if not isValid(stitcher) then
        error("MapStitcher.addScreenshot: 无效的拼接器对象")
    end
    return cv_lib.addScreenshotToStitcher(stitcher, x, y, x1, y1) == 1
end

-- 批量添加图像
-- @param stitcher: 地图拼接器对象
-- @param image_paths: 图像路径数组(table)
-- @return: 成功添加的数量(number)
function OpenCV.MapStitcher.addImageArray(stitcher, image_paths)
    if not isValid(stitcher) then
        error("MapStitcher.addImageArray: 无效的拼接器对象")
    end

    local path_count = #image_paths
    local c_paths = ffi.new("const char*[?]", path_count)
    for i, path in ipairs(image_paths) do
        c_paths[i - 1] = path
    end

    return cv_lib.addImageArrayToStitcher(stitcher, c_paths, path_count)
end

-- 从文件夹添加图像
-- @param stitcher: 地图拼接器对象
-- @param folder_path: 文件夹路径
-- @param file_extension: 文件扩展名，如".jpg"，nil表示所有图像格式
-- @return: 成功添加的数量(number)
function OpenCV.MapStitcher.addImageFolder(stitcher, folder_path, file_extension)
    if not isValid(stitcher) then
        error("MapStitcher.addImageFolder: 无效的拼接器对象")
    end
    return cv_lib.addImageFolderToStitcher(stitcher, folder_path, file_extension)
end

-- 获取当前拼接结果
-- @param stitcher: 地图拼接器对象
-- @return: 拼接结果图像(Mat)
function OpenCV.MapStitcher.getCurrentResult(stitcher)
    if not isValid(stitcher) then
        error("MapStitcher.getCurrentResult: 无效的拼接器对象")
    end
    local result = cv_lib.getCurrentStitchResult(stitcher)
    if not isValid(result) then
        error("MapStitcher.getCurrentResult: 获取拼接结果失败")
    end
    return result
end

-- 保存拼接结果
-- @param stitcher: 地图拼接器对象
-- @param output_path: 输出文件路径
-- @return: 是否成功(boolean)
function OpenCV.MapStitcher.saveResult(stitcher, output_path)
    if not isValid(stitcher) then
        error("MapStitcher.saveResult: 无效的拼接器对象")
    end
    return cv_lib.saveStitchResult(stitcher, output_path) == 1
end

-- 获取拼接统计信息
-- @param stitcher: 地图拼接器对象
-- @return: {image_count, success_count, current_x, current_y}
function OpenCV.MapStitcher.getInfo(stitcher)
    if not isValid(stitcher) then
        error("MapStitcher.getInfo: 无效的拼接器对象")
    end

    local image_count = ffi.new("int[1]")
    local success_count = ffi.new("int[1]")
    local current_x = ffi.new("int[1]")
    local current_y = ffi.new("int[1]")

    if cv_lib.getStitchInfo(stitcher, image_count, success_count, current_x, current_y) == 1 then
        return {
            image_count = tonumber(image_count[0]),
            success_count = tonumber(success_count[0]),
            current_x = tonumber(current_x[0]),
            current_y = tonumber(current_y[0])
        }
    else
        error("MapStitcher.getInfo: 获取拼接信息失败")
    end
end

-- 设置拼接参数
-- @param stitcher: 地图拼接器对象
-- @param sift_threshold: SIFT匹配阈值，默认100.0
-- @param orb_threshold: ORB匹配阈值，默认50.0
-- @param template_threshold: 模板匹配阈值，默认0.8
-- @param crop_ratio: 裁剪比例，默认0.6
function OpenCV.MapStitcher.setParameters(stitcher, sift_threshold, orb_threshold, template_threshold, crop_ratio)
    if not isValid(stitcher) then
        error("MapStitcher.setParameters: 无效的拼接器对象")
    end
    cv_lib.setStitchParameters(stitcher, sift_threshold or 100.0, orb_threshold or 50.0,
        template_threshold or 0.8, crop_ratio or 0.6)
end

-- 开始实时拼接
-- @param stitcher: 地图拼接器对象
-- @param interval_ms: 截图间隔(毫秒)，默认2000
-- @return: 是否成功(boolean)
function OpenCV.MapStitcher.startRealtime(stitcher, interval_ms)
    if not isValid(stitcher) then
        error("MapStitcher.startRealtime: 无效的拼接器对象")
    end
    return cv_lib.startRealtimeStitching(stitcher, interval_ms or 2000) == 1
end

-- 停止实时拼接
-- @param stitcher: 地图拼接器对象
function OpenCV.MapStitcher.stopRealtime(stitcher)
    if not isValid(stitcher) then
        error("MapStitcher.stopRealtime: 无效的拼接器对象")
    end
    cv_lib.stopRealtimeStitching(stitcher)
end

-- 获取实时拼接状态
-- @param stitcher: 地图拼接器对象
-- @return: 是否正在运行(boolean)
function OpenCV.MapStitcher.getRealtimeStatus(stitcher)
    if not isValid(stitcher) then
        error("MapStitcher.getRealtimeStatus: 无效的拼接器对象")
    end
    return cv_lib.getRealtimeStitchStatus(stitcher) == 1
end

-- ================================
-- 高层业务函数（找图 + 点击 + 等待）
-- 基于 SIFT/ORB/模板匹配 + 懒人精灵触控 API
-- ================================

-- 匹配方法常量
OpenCV.MATCH_SIFT = "sift"          -- SIFT 特征匹配（抗缩放/旋转，默认）
OpenCV.MATCH_ORB = "orb"            -- ORB 特征匹配（速度更快，精度略低）
OpenCV.MATCH_TEMPLATE = "template"  -- 多尺度模板匹配（适合颜色稳定的图标）

-- 点击类型常量
OpenCV.CLICK_TAP = "tap"            -- 普通点击
OpenCV.CLICK_LONG = "long"          -- 长按

-- 模板缓存表：避免重复 loadImage 同一张图
local _tplCache = {}

-- 内部：规范化搜索区域
-- region 可为 nil（全屏）、{x,y,x1,y1} 或 {x=,y=,x1=,y1=}
-- 返回 x, y, x1, y1 四个屏幕绝对坐标
local function _normalizeRegion(region)
    if region == nil then
        local w, h = getDisplaySize()
        return 0, 0, w, h
    end
    local x = region.x or region[1] or 0
    local y = region.y or region[2] or 0
    local x1 = region.x1 or region[3]
    local y1 = region.y1 or region[4]
    if not x1 or not y1 then
        local w, h = getDisplaySize()
        x1 = x1 or w
        y1 = y1 or h
    end
    return x, y, x1, y1
end

-- 内部：加载模板（带缓存）
-- useCache 默认 true；返回 Mat 或 nil
-- 文件不存在时自动从 opencv.rc 资源包解压后重试（仅一次，避免重复 IO）
local _rcExtracted = false
local function _loadTemplate(tplPath, useCache)
    if useCache ~= false and _tplCache[tplPath] then
        return _tplCache[tplPath]
    end
    local tpl = cv_lib.loadImage(tplPath)
    -- 加载失败：尝试从 opencv.rc 资源包解压到模板所在目录后重试
    if not isValid(tpl) and not _rcExtracted then
        _rcExtracted = true
        local dir = tplPath:match("(.+)[/\\][^/\\]+$") or getWorkPath()
        pcall(extractAssets, "opencv.rc", dir .. "/", "*.*")
        tpl = cv_lib.loadImage(tplPath)
    end
    if not isValid(tpl) then
        return nil
    end
    if useCache ~= false then
        _tplCache[tplPath] = tpl
    end
    return tpl
end

-- 内部：在场景中执行一次匹配，返回标准结果表
-- regX, regY 为区域偏移，用于把相对坐标转成屏幕绝对坐标
local function _doMatch(scene, tpl, method, threshold, regX, regY)
    local result = { x = -1, y = -1, confidence = 0, found = false }
    if not isValid(scene) or not isValid(tpl) then
        return result
    end
    method = method or OpenCV.MATCH_SIFT
    local t0 = OpenCV.DEBUG and tickCount() or 0

    if method == OpenCV.MATCH_SIFT then
        local cx = ffi.new("double[1]")
        local cy = ffi.new("double[1]")
        local conf = ffi.new("double[1]")
        cv_lib.findImageBySIFT(scene, tpl, threshold or 100.0, cx, cy, conf)
        local x, y = tonumber(cx[0]), tonumber(cy[0])
        if x >= 0 and y >= 0 then
            result.x = x + regX
            result.y = y + regY
            -- C 层 confidence 输出参数旧 .so 未回写（恒 0），改用 getLastMatchInfo 取真实良好匹配数
            result.confidence = OpenCV.getLastMatchInfo().confidence
            result.found = true
        end
    elseif method == OpenCV.MATCH_ORB then
        local cx = ffi.new("double[1]")
        local cy = ffi.new("double[1]")
        local conf = ffi.new("double[1]")
        cv_lib.findImageByORB(scene, tpl, threshold or 50.0, cx, cy, conf)
        local x, y = tonumber(cx[0]), tonumber(cy[0])
        if x >= 0 and y >= 0 then
            result.x = x + regX
            result.y = y + regY
            result.confidence = OpenCV.getLastMatchInfo().confidence
            result.found = true
        end
    elseif method == OpenCV.MATCH_TEMPLATE then
        local bx = ffi.new("double[1]")
        local by = ffi.new("double[1]")
        local mv = ffi.new("double[1]")
        local bs = ffi.new("double[1]")
        -- 转灰度加速：彩色 3 通道 matchTemplate 慢 3 倍，UI 找图灰度足够
        local matchScene, matchTpl = scene, tpl
        local tmpScene, tmpTpl
        if cv_lib.getMatChannels(scene) > 1 then
            tmpScene = cv_lib.convertToGray(scene)
            if isValid(tmpScene) then matchScene = tmpScene end
        end
        if cv_lib.getMatChannels(tpl) > 1 then
            tmpTpl = cv_lib.convertToGray(tpl)
            if isValid(tmpTpl) then matchTpl = tmpTpl end
        end
        cv_lib.templateMatchMultiScale(matchScene, matchTpl, OpenCV.TM_CCOEFF_NORMED,
            OpenCV.SCALE_START, OpenCV.SCALE_END, OpenCV.SCALE_STEP, bx, by, mv, bs)
        if tmpScene then cv_lib.releaseMat(tmpScene) end
        if tmpTpl then cv_lib.releaseMat(tmpTpl) end
        -- C 层 templateMatchMultiScale 已返回中心坐标（loc + resized/2），阈值是相似度(0~1)
        local thr = threshold or 0.8
        local bxv, byv, mvv, bsv = tonumber(bx[0]), tonumber(by[0]), tonumber(mv[0]), tonumber(bs[0])
        if bxv >= 0 and byv >= 0 and mvv >= thr then
            result.x = bxv + regX
            result.y = byv + regY
            result.confidence = mvv
            result.scale = bsv
            result.found = true
        end
    else
        error("_doMatch: 未知匹配方法 " .. tostring(method))
    end
    -- 坐标四舍五入取整（像素坐标为整数，避免 string.format("%d") 报错）
    if result.found then
        result.x = math.floor(result.x + 0.5)
        result.y = math.floor(result.y + 0.5)
    end
    if OpenCV.DEBUG then
        print(string.format("[_doMatch] %s 匹配 %dms found=%s",
            method == OpenCV.MATCH_SIFT and "SIFT" or
            (method == OpenCV.MATCH_ORB and "ORB" or "TEMPLATE"),
            tickCount() - t0, tostring(result.found)))
    end
    return result
end

-- 内部：根据点击类型执行点击
local function _doClick(x, y, clickType)
    if clickType == OpenCV.CLICK_LONG then
        longTap(x, y)
    else
        tap(x, y)
    end
end

-- 内部：解析偏移参数，返回 dx, dy
local function _parseOffset(offset)
    if not offset then return 0, 0 end
    return offset.dx or offset[1] or 0, offset.dy or offset[2] or 0
end

-- 清除模板缓存
-- @param tplPath: 指定路径则只清除该项，nil 清除全部
function OpenCV.clearTemplateCache(tplPath)
    if tplPath then
        if _tplCache[tplPath] then
            cv_lib.releaseMat(_tplCache[tplPath])
            _tplCache[tplPath] = nil
        end
    else
        for path, mat in pairs(_tplCache) do
            cv_lib.releaseMat(mat)
            _tplCache[path] = nil
        end
    end
end

-- 在已有场景 Mat 中查找模板（不截图）
-- @param scene: 场景图像(Mat)
-- @param tplPath: 模板图片路径
-- @param threshold: 匹配阈值（SIFT/ORB 默认 100/50，模板匹配默认 0.8）
-- @param method: 匹配方法，默认 OpenCV.MATCH_SIFT
-- @param useCache: 是否缓存模板，默认 true
-- @return: {x, y, confidence, found, method}，坐标相对于 scene 左上角；模板加载失败返回 nil
function OpenCV.findImageIn(scene, tplPath, threshold, method, useCache)
    checkMat(scene, "findImageIn")
    local tpl = _loadTemplate(tplPath, useCache)
    if not tpl then
        return nil
    end
    local r = _doMatch(scene, tpl, method, threshold, 0, 0)
    r.method = method or OpenCV.MATCH_SIFT
    return r
end

-- 截图并查找模板
-- @param tplPath: 模板图片路径
-- @param region: 搜索区域，nil=全屏，或 {x,y,x1,y1} / {x=,y=,x1=,y1=}
-- @param threshold: 匹配阈值
-- @param method: 匹配方法，默认 OpenCV.MATCH_SIFT
-- @param useCache: 是否缓存模板，默认 true
-- @return: {x, y, confidence, found, method, region}，x,y 为屏幕绝对坐标（匹配中心点）
function OpenCV.findImage(tplPath, region, threshold, method, useCache)
    local regX, regY, x1, y1 = _normalizeRegion(region)
    local tpl = _loadTemplate(tplPath, useCache)
    if not tpl then
        return { x = -1, y = -1, confidence = 0, found = false,
                 method = method or OpenCV.MATCH_SIFT,
                 error = "模板加载失败: " .. tostring(tplPath) }
    end
    local ok, scene = pcall(OpenCV.screenshot, regX, regY, x1, y1)
    if not ok or not isValid(scene) then
        return { x = -1, y = -1, confidence = 0, found = false,
                 method = method or OpenCV.MATCH_SIFT,
                 error = "截图失败: " .. tostring(scene) }
    end
    local r = _doMatch(scene, tpl, method, threshold, regX, regY)
    r.method = method or OpenCV.MATCH_SIFT
    r.region = { x = regX, y = regY, x1 = x1, y1 = y1 }
    OpenCV.releaseMat(scene)
    return r
end

-- 判断图片是否存在
-- @return: found(bool), result(table)
function OpenCV.existsImage(tplPath, region, threshold, method, useCache)
    local r = OpenCV.findImage(tplPath, region, threshold, method, useCache)
    return r.found, r
end

-- 根据匹配结果点击
-- @param result: findImage 等返回的结果表
-- @param clickType: 点击类型，默认 OpenCV.CLICK_TAP
-- @param offset: 点击偏移 {dx,dy} 或 {x=,y=}，相对于匹配中心
-- @return: 是否执行了点击（result.found 为 true 才点击）
function OpenCV.clickResult(result, clickType, offset)
    if not result or not result.found then
        return false
    end
    local dx, dy = _parseOffset(offset)
    _doClick(result.x + dx, result.y + dy, clickType)
    return true
end

-- 截图找图并点击
-- @param tplPath: 模板路径
-- @param region: 搜索区域
-- @param threshold: 阈值
-- @param method: 匹配方法
-- @param clickType: 点击类型，默认 tap
-- @param offset: 点击偏移
-- @param useCache: 缓存模板
-- @return: 点击成功返回 true, result；失败返回 false, result
function OpenCV.findImageAndClick(tplPath, region, threshold, method, clickType, offset, useCache)
    local r = OpenCV.findImage(tplPath, region, threshold, method, useCache)
    if r.found then
        OpenCV.clickResult(r, clickType or OpenCV.CLICK_TAP, offset)
        return true, r
    end
    return false, r
end

-- 简化版找图点击（普通点击，无偏移）
-- @return: 是否点击成功
function OpenCV.clickIfFound(tplPath, region, threshold, method, useCache)
    local ok = OpenCV.findImageAndClick(tplPath, region, threshold, method,
                                        OpenCV.CLICK_TAP, nil, useCache)
    return ok
end

-- 连续找图并点击，直到找不到或达到上限
-- @param maxCount: 最大点击次数，默认 10
-- @param interval: 每次点击后等待（毫秒），默认 500
-- @return: 实际点击次数
function OpenCV.clickAllFound(tplPath, maxCount, interval, region, threshold, method, clickType, offset, useCache)
    maxCount = maxCount or 10
    interval = (interval and interval > 0) and interval or 500
    local count = 0
    for i = 1, maxCount do
        local ok = OpenCV.findImageAndClick(tplPath, region, threshold, method,
                                            clickType or OpenCV.CLICK_TAP, offset, useCache)
        if not ok then
            break
        end
        count = count + 1
        sleep(interval)
    end
    return count
end

-- 轮询等待图片出现
-- @param timeout: 超时（毫秒），默认 10000
-- @param interval: 轮询间隔（毫秒），默认 500
-- @return: 找到返回 result，超时返回 nil
function OpenCV.waitForImage(tplPath, timeout, interval, region, threshold, method, useCache)
    timeout = timeout or 10000
    interval = (interval and interval > 0) and interval or 500
    local elapsed = 0
    while elapsed <= timeout do
        local r = OpenCV.findImage(tplPath, region, threshold, method, useCache)
        if r.found then
            return r
        end
        sleep(interval)
        elapsed = elapsed + interval
    end
    return nil
end

-- 等待图片出现并点击
-- @return: 点击成功返回 true, result；超时返回 false, nil
function OpenCV.waitForImageAndClick(tplPath, timeout, interval, region, threshold, method, clickType, offset, useCache)
    local r = OpenCV.waitForImage(tplPath, timeout, interval, region, threshold, method, useCache)
    if r then
        OpenCV.clickResult(r, clickType or OpenCV.CLICK_TAP, offset)
        return true, r
    end
    return false, nil
end

-- 等待图片消失
-- @return: true=已消失，false=超时仍存在
function OpenCV.waitForImageGone(tplPath, timeout, interval, region, threshold, method, useCache)
    timeout = timeout or 10000
    interval = (interval and interval > 0) and interval or 500
    local elapsed = 0
    while elapsed <= timeout do
        local r = OpenCV.findImage(tplPath, region, threshold, method, useCache)
        if not r.found then
            return true
        end
        sleep(interval)
        elapsed = elapsed + interval
    end
    return false
end

-- 在多个模板中找到第一个匹配的（只截一次图）
-- @param tplPaths: 模板路径数组 {"a.png", "b.png"}
-- @return: {index, path, x, y, confidence, found, method} 或 nil
function OpenCV.findAnyImage(tplPaths, region, threshold, method, useCache)
    local regX, regY, x1, y1 = _normalizeRegion(region)
    local ok, scene = pcall(OpenCV.screenshot, regX, regY, x1, y1)
    if not ok or not isValid(scene) then
        return nil
    end
    local result = nil
    for i, path in ipairs(tplPaths) do
        local tpl = _loadTemplate(path, useCache)
        if tpl then
            local r = _doMatch(scene, tpl, method, threshold, regX, regY)
            if r.found then
                r.index = i
                r.path = path
                r.method = method or OpenCV.MATCH_SIFT
                result = r
                break
            end
        end
    end
    OpenCV.releaseMat(scene)
    return result
end

-- 等待多个模板中任一出现
-- @return: 找到返回 result（含 index, path），超时返回 nil
function OpenCV.waitForAnyImage(tplPaths, timeout, interval, region, threshold, method, useCache)
    timeout = timeout or 10000
    interval = (interval and interval > 0) and interval or 500
    local elapsed = 0
    while elapsed <= timeout do
        local r = OpenCV.findAnyImage(tplPaths, region, threshold, method, useCache)
        if r then
            return r
        end
        sleep(interval)
        elapsed = elapsed + interval
    end
    return nil
end

-- 找到图片后从该位置滑动到目标点（拖拽）
-- @param targetX, targetY: 滑动目标坐标
-- @param swipeTime: 滑动时长（毫秒），默认 500
-- @return: 是否执行了滑动, result
function OpenCV.dragImage(tplPath, targetX, targetY, swipeTime, region, threshold, method, useCache)
    local r = OpenCV.findImage(tplPath, region, threshold, method, useCache)
    if not r.found then
        return false, r
    end
    swipe(r.x, r.y, targetX, targetY, swipeTime or 500)
    return true, r
end

-- 保存当前截图到文件（调试用）
-- @param path: 保存路径
-- @param region: 截图区域，nil=全屏
-- @return: 是否成功
function OpenCV.saveScreenshot(path, region)
    local regX, regY, x1, y1 = _normalizeRegion(region)
    local ok, scene = pcall(OpenCV.screenshot, regX, regY, x1, y1)
    if not ok or not isValid(scene) then
        return false
    end
    local ret = cv_lib.saveMat(scene, path) == 1
    OpenCV.releaseMat(scene)
    return ret
end

-- 截取屏幕指定区域并保存为模板文件（用于制作找图模板）
-- @param x, y: 区域左上角坐标
-- @param w, h: 区域宽高
-- @param savePath: 保存路径
-- @return: 是否成功
function OpenCV.captureTemplate(x, y, w, h, savePath)
    local ok, scene = pcall(OpenCV.screenshot, x, y, x + w, y + h)
    if not ok or not isValid(scene) then
        return false
    end
    local ret = cv_lib.saveMat(scene, savePath) == 1
    OpenCV.releaseMat(scene)
    return ret
end

-- 从已有图像中裁剪一块保存为模板（用于从全屏截图制作模板）
-- @param srcMat: 源图像(Mat)
-- @param x, y: 裁剪左上角
-- @param w, h: 裁剪宽高
-- @param savePath: 保存路径
-- @return: 是否成功
function OpenCV.cropAndSave(srcMat, x, y, w, h, savePath)
    checkMat(srcMat, "cropAndSave")
    local tpl = cv_lib.crop(srcMat, x, y, w, h)
    if not isValid(tpl) then
        return false
    end
    local ret = cv_lib.saveMat(tpl, savePath) == 1
    cv_lib.releaseMat(tpl)
    return ret
end

return OpenCV
