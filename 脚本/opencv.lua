---@diagnostic disable: undefined-global
-- OpenCV so 库示例入口
-- 加载 opencvutil.lua（FFI 封装），演示截图、保存、SIFT 找图
-- 依赖：界面/libs/<abi>/libsy.so 由 GitHub Actions 编译产出

local function main()
    -- 加载 OpenCV 封装库（与本脚本同目录）
    local ok, cv = pcall(require, "opencvutil")
    if not ok or not cv then
        print("✗ 加载 opencvutil 失败: " .. tostring(cv))
        return
    end
    print("✓ OpenCV 封装库加载完成")

    -- 1. 截图并保存（验证 screenshot + saveMat）
    local shot = cv.screenshot(0, 0, 540, 960)
    local savePath = getWorkPath() .. "/shot.png"
    if cv.saveMat(shot, savePath) then
        print("✓ 截图已保存: " .. savePath)
    else
        print("✗ 截图保存失败")
    end

    -- 2. 图像信息
    print(string.format("截图尺寸: %d x %d, 通道: %d",
        cv.getWidth(shot), cv.getHeight(shot), cv.getChannels(shot)))

    -- 3. 灰度转换 + 保存（验证图像处理链路）
    local gray = cv.convertToGray(shot)
    cv.saveMat(gray, getWorkPath() .. "/shot_gray.png")
    cv.releaseMat(gray)

    -- 4. SIFT 找图示例（需要准备模板 template.png）
    local tmplPath = getWorkPath() .. "/template.png"
    local f = io.open(tmplPath, "rb")
    if f then
        f:close()
        local tmpl = cv.loadImage(tmplPath)
        local r = cv.findImageBySIFT(shot, tmpl, 100.0)
        if r.found then
            print(string.format("✓ SIFT 找到模板: 中心(%d, %d) 置信度=%.0f", r.x, r.y, r.confidence))
        else
            print("✗ SIFT 未找到模板（坐标: " .. tostring(r.x) .. "," .. tostring(r.y) .. "）")
        end
        local info = cv.getLastMatchInfo()
        print(string.format("  匹配详情: 关键点=%d, 良好匹配=%d", info.keypoints_count, info.good_matches_count))
        cv.releaseMat(tmpl)
    else
        print("（未找到 template.png，跳过 SIFT 找图演示）")
    end

    cv.releaseMat(shot)
    print("✓ 示例执行完毕")
end

-- 全局保护：任何错误都打印而不崩溃
local ok, err = pcall(main)
if not ok then
    print("✗ 执行出错: " .. tostring(err))
end
