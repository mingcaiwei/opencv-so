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
    local result = cv_lib.screenshot(x, y, x1, y1)
    if not isValid(result) then
        error("screenshot: 截图失败")
    end
    return result
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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

    return {
        x = best_x[0],
        y = best_y[0],
        match_value = match_value[0],
        scale = best_scale[0],
        found = best_x[0] >= 0 and best_y[0] >= 0
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
        confidence = confidence[0],
        keypoints_count = keypoints_count[0],
        good_matches_count = good_matches_count[0]
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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

    return {
        x = best_x[0],
        y = best_y[0],
        confidence = best_confidence[0],
        index = best_index[0] + 1, -- 转换为Lua的1基索引
        found = best_index[0] >= 0
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
            width = width[0],
            height = height[0],
            feature_count = feature_count[0]
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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

    return {
        x = center_x[0],
        y = center_y[0],
        confidence = confidence[0],
        scale = best_scale[0],
        found = center_x[0] >= 0 and center_y[0] >= 0
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
            image_count = image_count[0],
            success_count = success_count[0],
            current_x = current_x[0],
            current_y = current_y[0]
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

return OpenCV
