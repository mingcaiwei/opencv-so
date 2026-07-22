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

    -- 5. 高层函数演示：用刚才的 shot.png 自动验证找图链路
    -- shot.png 是全屏截图（场景），从里面裁一小块作为"模板"，再在原图里找它
    -- 这样无需手动准备 template.png，运行即可看到找图效果
    local scene = cv.loadImage(savePath)  -- 复用前面保存的 shot.png
    if scene then
        -- 从场景中裁一块 200x200 保存为模板（选有内容的区域）
        local tx, ty, tw, th = 100, 300, 200, 200
        if cv.cropAndSave(scene, tx, ty, tw, th, tmplPath) then
            print(string.format("✓ 已从截图生成模板: 起点(%d,%d) 尺寸%dx%d", tx, ty, tw, th))
            -- 用 findImageIn 在场景中找这块模板（不截图，复用已有 scene）
            local r = cv.findImageIn(scene, tmplPath, 100.0, cv.MATCH_SIFT)
            if r and r.found then
                print(string.format("✓ findImageIn 找到: 中心(%d,%d) 置信度=%.0f", r.x, r.y, r.confidence))
                print(string.format("  预期中心约 (%d,%d)（模板起点+尺寸一半）", tx + tw/2, ty + th/2))
            else
                print("✗ findImageIn 未找到（该区域特征点不足，可调整裁剪位置或降低阈值到 50）")
            end
        end
        cv.releaseMat(scene)
    end

    -- 更多高层用法（按需取消注释，部分会真实操作屏幕）：
    --cv.findImageAndClick(tmplPath, nil, 100.0)              -- 找图并点击
    -- cv.clickIfFound(tmplPath, nil, 100.0)                   -- 简化找图点击
    -- cv.waitForImage(tmplPath, 5000, 500)                    -- 等待出现（5秒超时）
    -- cv.waitForImageAndClick(tmplPath, 5000, 500)            -- 等待并点击
    -- cv.waitForImageGone(tmplPath, 5000, 500)                -- 等待消失
    -- cv.findAnyImage({"a.png","b.png"}, nil, 100.0)          -- 多图找第一个
    -- cv.waitForAnyImage({"a.png","b.png"}, 5000, 500)        -- 等待任一出现
    -- cv.clickAllFound(tmplPath, 5, 800)                      -- 连续点击最多5次
    -- cv.dragImage(tmplPath, 300, 300, 500)                   -- 找到后拖拽到(300,300)
    -- cv.captureTemplate(100, 100, 80, 80, getWorkPath().."/btn.png")  -- 截取屏幕区域作为模板
    -- cv.clearTemplateCache()                                 -- 清除模板缓存

    print("✓ 示例执行完毕")
end

-- 全局保护：任何错误都打印而不崩溃
--[===[local ok, err = pcall(main)
if not ok then
    print("✗ 执行出错: " .. tostring(err))
end]===]


-- 截图并查找模板
-- @param tplPath: 模板图片路径
-- @param region: 搜索区域，nil=全屏，或 {x,y,x1,y1} / {x=,y=,x1=,y1=}
-- @param threshold: 匹配阈值
-- @param method: 匹配方法，默认 OpenCV.MATCH_SIFT
-- @param useCache: 是否缓存模板，默认 true
-- @return: {x, y, confidence, found, method, region}，x,y 为屏幕绝对坐标（匹配中心点）

-- ========== findImage 调用示例 ==========
-- findImage 会自动截图 + 匹配，返回屏幕绝对坐标（匹配中心点）
-- 返回值: { x, y, confidence, found, method, region }
--   confidence: SIFT/ORB 为 0-100 匹配率；TEMPLATE 为 0-1 相似度

local cv = require("opencvutil")

local work = getWorkPath()
local tplPath = work .. "/1.png"   -- 模板图片（放入 opencv.rc 资源包即可，findImage 会自动解压）


-- 示例 1：全屏 SIFT 找图
-- threshold=100 是 SIFT 描述子距离阈值（越小越严格，100 较宽松）
local r1 = cv.findImage(tplPath, nil, 100.0, cv.MATCH_SIFT)
if r1 and r1.found then
    print(string.format("✓ SIFT 全屏找到: 中心(%d, %d) 匹配率=%.1f%%", r1.x, r1.y, r1.confidence))
else
    print("✗ SIFT 全屏未找到（确认 template.png 已放入 work 目录）")
end

-- 示例 2：指定区域模板匹配
-- region = {左, 上, 右, 下}；threshold=0.8 即 80% 相似度
local tick = tickCount()
print(tick)
local r2 = cv.findImage(tplPath, {52,1635,261,1870}, 0.8, cv.MATCH_TEMPLATE)
if r2 and r2.found then
    print(string.format("✓ 模板匹配区域内找到: 中心(%d, %d) 相似度=%.1f%%", r2.x, r2.y, r2.confidence * 100))
else
    print("✗ 指定区域内未找到模板")
end
local tick2 = tickCount()

print(tick2-tick)

-- 示例 3：找图并点击（一行搞定，默认 SIFT + 普通点击）
-- cv.findImageAndClick(tplPath, nil, 100.0)

-- 示例 4：指定区域找图并长按
-- cv.findImageAndClick(tplPath, {553, 1057, 794, 1237}, 100.0, cv.MATCH_SIFT, cv.CLICK_LONG)





