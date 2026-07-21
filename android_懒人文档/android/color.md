# 图色方法 (image)

## 1. LuaEngine.snapShot java层截图方法 (LuaEngine.snapShot)
**函数:** `LuaEngine.snapShot(l,t,r,b)`  
**描述:** LuaEngine.snapShot java层截图方法

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| l | number | 是 | 左范围 |
| t | number | 是 | 上范围 |
| r | number | 是 | 右范围 |
| b | number | 是 | 下范围 |


| 返回值类型 | 说明 |
| :--- | :--- |
| any | 返回一个java的Bitmap对象，记得一定要释放避免内存泄漏 |

**示例:**
```lua
import('android.*')
import('java.lang.*')
import('java.util.*')
import('android.widget.*')
import('android.os.Build')
import('android.graphics.*');
import('com.nx.assist.lua.LuaEngine')

function releaseBmp(bmp)
	if bmp ~= nil and bmp.isRecycled() == false then
		bmp.recycle()
	end
end

local bitmap = LuaEngine.snapShot(100,100,200,200)
printEx(bitmap)

releaseBmp(bitmap)
```

## 2. YoloV5.detect yolov5目标检测 (YoloV5.detect)
**函数:** `LuaEngine.detect(bmp,usegpu)`  
**描述:** YoloV5.detect yolov5目标检测

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 获取一个结果集 |

**示例:**
```lua
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('android.hardware.Sensor')
import('android.hardware.SensorEvent')
import('android.hardware.SensorEventListener')
import('android.hardware.SensorManager')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.YoloV5')

local work = getWorkPath() .. "/yolo"
mkdir(work)
extractAssets("yolo.rc",work,"*.*")
local result = work .. "/result.txt"
local param = work .. "/yolov5s.param"
local bin = work .. "/yolov5s.bin"

local r = YoloV5.init(result,param,bin)
for i=1,100 do
	local bmp = LuaEngine.snapShot(0,0,0,0)
	local str = YoloV5.detect(bmp,false)
	print(str)
	if str ~= nil then
		local tb = jsonLib.decode(str)
		for i=1,#tb do
			print(tb[i])
		end
	end
	if bmp ~= nil and bmp.isRecycled() == false then
		bmp.recycle()
	end
	sleep(1000)
end
```

## 3. PaddleOcr.loadModel  加载自带的模型 (PaddleOcr.loadModel)
**函数:** `LuaEngine.loadModel(isUseOnnxModel)`  
**描述:** PaddleOcr.loadModel  加载自带的模型

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| isUseOnnxModel | boolean | 是 | 是否使用ONNX模型（true: ONNX模型, false: NCNN模型） |

| 返回值类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
-- 导入必要的类库
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.PaddleOcr')

--[[
 * OCR处理主函数
 * @param useOnnx 是否使用ONNX模型（true: ONNX模型, false: NCNN模型）
 * @param left 截图区域左坐标
 * @param top 截图区域上坐标
 * @param right 截图区域右坐标
 * @param bottom 截图区域下坐标
 * @return table|nil 识别结果表，失败返回nil
]]
local function processOcr(useOnnx, left, top, right, bottom)
    -- 记录开始时间
    local startTime = os.time()
    
    -- 1. 加载OCR模型
    print(string.format("Loading %s model...", useOnnx and "ONNX" or "NCNN"))
    if not PaddleOcr.loadModel(useOnnx) then
        print("ERROR: Failed to load OCR model")
        return nil
    end
    print("Model loaded successfully")
    
    -- 2. 获取屏幕截图
    print("Capturing screen snapshot...")
    local bitmap = LuaEngine.snapShot(left, top, right, bottom)
    if not bitmap then
        print("ERROR: Failed to capture screen area")
        return nil
    end
    
    -- 3. 执行OCR识别（确保在finally块释放资源）
    local result
    local success, err = pcall(function()
        -- 执行OCR检测
        local jsonStr = PaddleOcr.detect(bitmap)
        if not jsonStr or jsonStr == "" then
            error("OCR detection returned empty result")
        end
        
        -- 解析JSON结果
        local parseSuccess, parsed = pcall(jsonLib.decode, jsonStr)
        if not parseSuccess then
            error("Failed to parse JSON result: "..tostring(parsed))
        end
        
        result = parsed
    end)
    
    -- 4. 确保释放bitmap资源
    LuaEngine.releaseBmp(bitmap)
    
    if not success then
        print("OCR Processing Error: "..tostring(err))
        return nil
    end
    
    -- 5. 输出性能信息
    print(string.format("OCR processing completed in %.2f seconds", os.time() - startTime))
    
    return result
end

--[[
 * 格式化打印OCR结果
 * @param results table OCR识别结果
]]
local function printOcrResults(results)
    if not results or #results == 0 then
        print("INFO: No text detected")
        return
    end
    
    print("\nOCR Detection Results:")
    print("========================================")
    print(" Index | Text              | Confidence | Position ")
    print("----------------------------------------")
    
    for i, item in ipairs(results) do
        local text = item.label and item.label:sub(1, 16) or "N/A"
        local conf = item.confidence and string.format("%.2f", item.confidence) or "N/A"
        local pos = item.x and item.y and string.format("(%d,%d)", item.x, item.y) or "N/A"
        
        print(string.format(" %-5d | %-16s | %-9s | %-8s",
                          i, text, conf, pos))
    end
    print("========================================")
end

-- 主执行函数
local function main()
    -- 配置参数
    local config = {
        useOnnx = true,  -- 使用ONNX模型（PP-OCRv4官方模型）
        captureArea = {   -- 截图区域坐标
            left = 0,
            top = 0,
            right = 280,
            bottom = 271
        }
    }
    
    print("\n===== PaddleOCR Processor =====")
    print("Model Type: "..(config.useOnnx and "ONNX(PP-OCRv4)" or "NCNN"))
    print(string.format("Capture Area: [%d,%d,%d,%d]",
                      config.captureArea.left,
                      config.captureArea.top,
                      config.captureArea.right,
                      config.captureArea.bottom))
    
    -- 执行OCR处理
    local results = processOcr(
        config.useOnnx,
        config.captureArea.left,
        config.captureArea.top,
        config.captureArea.right,
        config.captureArea.bottom
    )
    
    -- 处理并打印结果
    if results then
        printOcrResults(results)
        
        -- 示例：处理特定识别结果
        -- if #results > 0 and results[1].label:find("目标文本") then
        --     print("Found target text!")
        -- end
    else
        print("OCR processing failed")
    end
    
    return results ~= nil
end

-- 执行主函数
return main()
```

## 4. PaddleOcr.loadOnnxModel  加载自己训练的onnx模型 (PaddleOcr.loadOnnxModel)
**函数:** `PaddleOcr.loadOnnxModel(modelDetPath,modelClsPath,modelRecPath,keyTxt)`  
**描述:** PaddleOcr.loadOnnxModel  加载自己训练的onnx模型

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| modelDetPath | string | 是 | 文件路径 |
| modelClsPath | string | 是 | 文件路径 |
| modelRecPath | string | 是 | 文件路径 |
| keyTxt | string | 是 | 文件路径 |

**返回值类型 | 说明 |
| :--- | :--- |
| string | json字符串 |

**示例:**
```lua
-- 导入必要的类库
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.PaddleOcr')

--[[
 * OCR处理主函数
 * @param useOnnx 是否使用ONNX模型（true: ONNX模型, false: NCNN模型）
 * @param left 截图区域左坐标
 * @param top 截图区域上坐标
 * @param right 截图区域右坐标
 * @param bottom 截图区域下坐标
 * @return table|nil 识别结果表，失败返回nil
]]
local function processOcr(useOnnx, left, top, right, bottom)
    -- 记录开始时间
    local startTime = os.time()
    
    -- 1. 加载OCR模型
    print(string.format("Loading %s model...", useOnnx and "ONNX" or "NCNN"))
    if not PaddleOcr.loadModel(useOnnx) then
        print("ERROR: Failed to load OCR model")
        return nil
    end
    print("Model loaded successfully")
    
    -- 2. 获取屏幕截图
    print("Capturing screen snapshot...")
    local bitmap = LuaEngine.snapShot(left, top, right, bottom)
    if not bitmap then
        print("ERROR: Failed to capture screen area")
        return nil
    end
    
    -- 3. 执行OCR识别（确保在finally块释放资源）
    local result
    local success, err = pcall(function()
        -- 执行OCR检测
        local jsonStr = PaddleOcr.detect(bitmap)
        if not jsonStr or jsonStr == "" then
            error("OCR detection returned empty result")
        end
        
        -- 解析JSON结果
        local parseSuccess, parsed = pcall(jsonLib.decode, jsonStr)
        if not parseSuccess then
            error("Failed to parse JSON result: "..tostring(parsed))
        end
        
        result = parsed
    end)
    
    -- 4. 确保释放bitmap资源
    LuaEngine.releaseBmp(bitmap)
    
    if not success then
        print("OCR Processing Error: "..tostring(err))
        return nil
    end
    
    -- 5. 输出性能信息
    print(string.format("OCR processing completed in %.2f seconds", os.time() - startTime))
    
    return result
end

--[[
 * 格式化打印OCR结果
 * @param results table OCR识别结果
]]
local function printOcrResults(results)
    if not results or #results == 0 then
        print("INFO: No text detected")
        return
    end
    
    print("\nOCR Detection Results:")
    print("========================================")
    print(" Index | Text              | Confidence | Position ")
    print("----------------------------------------")
    
    for i, item in ipairs(results) do
        local text = item.label and item.label:sub(1, 16) or "N/A"
        local conf = item.confidence and string.format("%.2f", item.confidence) or "N/A"
        local pos = item.x and item.y and string.format("(%d,%d)", item.x, item.y) or "N/A"
        
        print(string.format(" %-5d | %-16s | %-9s | %-8s",
                          i, text, conf, pos))
    end
    print("========================================")
end

-- 主执行函数
local function main()
    -- 配置参数
    local config = {
        useOnnx = true,  -- 使用ONNX模型（PP-OCRv4官方模型）
        captureArea = {   -- 截图区域坐标
            left = 0,
            top = 0,
            right = 280,
            bottom = 271
        }
    }
    
    print("\n===== PaddleOCR Processor =====")
    print("Model Type: "..(config.useOnnx and "ONNX(PP-OCRv4)" or "NCNN"))
    print(string.format("Capture Area: [%d,%d,%d,%d]",
                      config.captureArea.left,
                      config.captureArea.top,
                      config.captureArea.right,
                      config.captureArea.bottom))
    
    -- 执行OCR处理
    local results = processOcr(
        config.useOnnx,
        config.captureArea.left,
        config.captureArea.top,
        config.captureArea.right,
        config.captureArea.bottom
    )
    
    -- 处理并打印结果
    if results then
        printOcrResults(results)
        
        -- 示例：处理特定识别结果
        -- if #results > 0 and results[1].label:find("目标文本") then
        --     print("Found target text!")
        -- end
    else
        print("OCR processing failed")
    end
    
    return results ~= nil
end

-- 执行主函数
return main()
```

## 5. PaddleOcr.loadNnccModel  加载自己训练的ncnn模型 (PaddleOcr.loadNnccModel)
**函数:** `LuaEngine.loadNnccModel(detParams,recParams,detBin,recBin,keyTxt)`  
**描述:** PaddleOcr.loadNnccModel  加载自己训练的ncnn模型

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| detParams | string | 是 | 文件路径 |
| recParams | string | 是 | 文件路径 |
| detBin | string | 是 | 文件路径 |
| recBin | string | 是 | 文件路径 |
| keyTxt | string | 是 | 文件路径 |

**返回值类型 | 说明 |
| :--- | :--- |
| string | json字符串 |

**示例:**
```lua
-- 导入必要的Java类库
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.PaddleOcr')

--[[
 * 初始化OCR模型路径配置
 * @return table 包含模型路径的配置表
]]
local function initModelConfig()
    return {
        detParams = "/sdcard/paddle/det.param",
        recParams = "/sdcard/paddle/rec.param",
        detBin = "/sdcard/paddle/det.bin",
        recBin = "/sdcard/paddle/rec.bin",
        keyTxt = "/sdcard/paddle/keys.txt"
    }
end

--[[
 * 检查模型文件是否存在
 * @param config table 模型配置表
 * @return boolean 所有模型文件是否存在
]]
local function checkModelFiles(config)
    local requiredFiles = {
        config.detParams,
        config.recParams,
        config.detBin,
        config.recBin,
        config.keyTxt
    }

    for _, filePath in ipairs(requiredFiles) do
        local file = File(filePath)
        if not file.exists() then
            print(string.format("ERROR: Model file not found - %s", filePath))
            return false
        end
    end
    return true
end

--[[
 * 执行OCR识别流程
 * @param left 截图区域左坐标
 * @param top 截图区域上坐标
 * @param right 截图区域右坐标
 * @param bottom 截图区域下坐标
 * @return table|nil 识别结果，失败返回nil
]]
local function performOcrDetection(left, top, right, bottom)
    -- 1. 初始化模型配置
    local modelConfig = initModelConfig()

    -- 2. 检查模型文件是否存在
    if not checkModelFiles(modelConfig) then
        return nil
    end

    -- 3. 加载NNCC模型
    print("Loading NNCC model...")
    local modelLoaded = PaddleOcr.loadNnccModel(
        modelConfig.detParams,
        modelConfig.recParams,
        modelConfig.detBin,
        modelConfig.recBin,
        modelConfig.keyTxt
    )

    if not modelLoaded then
        print("ERROR: Failed to load NNCC model")
        return nil
    end

    -- 4. 获取屏幕截图
    print("Capturing screen snapshot...")
    local bitmap = LuaEngine.snapShot(left, top, right, bottom)
    if not bitmap then
        print("ERROR: Failed to capture screen snapshot")
        return nil
    end

    -- 5. 执行OCR识别
    print("Performing OCR detection...")
    local jsonResult = PaddleOcr.detect(bitmap)

    -- 6. 释放bitmap资源
    LuaEngine.releaseBmp(bitmap)

    if not jsonResult then
        print("WARNING: OCR detection returned no results")
        return nil
    end

    -- 7. 解析JSON结果
    local success, resultData = pcall(jsonLib.decode, jsonResult)
    if not success or type(resultData) ~= "table" then
        print("ERROR: Failed to parse OCR results JSON")
        return nil
    end

    return resultData
end

--[[
 * 格式化输出OCR结果
 * @param results table OCR识别结果
]]
local function printOcrResults(results)
    if not results or #results == 0 then
        print("INFO: No OCR results to display")
        return
    end

    print("\nOCR Detection Results:")
    print("========================================")
    print(" Index | Text              | Confidence ")
    print("----------------------------------------")
    
    for idx, item in ipairs(results) do
        if type(item) == "table" and item.label then
            -- 格式化输出：索引、文本（前16字符）、置信度（如果有）
            local confidence = item.confidence and string.format("%.2f", item.confidence) or "N/A"
            print(string.format(" %-5d | %-16s | %s",
                              idx,
                              item.label:sub(1, 16),
                              confidence))
        else
            print(string.format(" WARNING: Invalid data at index %d", idx))
        end
    end
    print("========================================")
end

-- 主函数
local function main()
    print("Starting OCR Processing Pipeline...")
    local startTime = os.time()

    -- 定义截图区域（示例坐标）
    local captureArea = {
        left = 0,
        top = 0,
        right = 280,
        bottom = 271
    }

    -- 执行OCR识别
    local ocrResults = performOcrDetection(
        captureArea.left,
        captureArea.top,
        captureArea.right,
        captureArea.bottom
    )

    -- 处理并输出结果
    if ocrResults then
        printOcrResults(ocrResults)
        
        -- 示例：处理特定识别结果
        -- if #ocrResults > 0 and ocrResults[1].label:find("目标文本") then
        --     print("Found target text!")
        -- end
    else
        print("OCR processing failed")
    end

    print(string.format("\nTotal processing time: %.2f seconds", os.time() - startTime))
    return ocrResults ~= nil
end

-- 执行主程序并返回状态
return main()
```

## 6. PaddleOcr.detectWithPadding 根据模型识别图片增强版 (PaddleOcr.detectWithPadding)
**函数:** `LuaEngine.detectWithPadding(bmp,padding,r,g,b)`  
**描述:** PaddleOcr.detectWithPadding 根据模型识别图片增强版

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| bmp | any | 是 | java的Bitmap对象 |
| padding | number | 是 | 填充值 |
| r | number | 是 | 红色通道值 |
| g | number | 是 | 绿色通道值 |
| b | number | 是 | 蓝色通道值 |

**返回值类型 | 说明 |
| :--- | :--- |
| string | json字符串 |

**示例:**
```lua
-- 导入必要的Java类库
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('android.hardware.Sensor')
import('android.hardware.SensorEvent')
import('android.hardware.SensorEventListener')
import('android.hardware.SensorManager')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.PaddleOcr')

--[[
 * OCR识别处理函数
 * @param left 截图区域左坐标
 * @param top 截图区域上坐标
 * @param right 截图区域右坐标
 * @param bottom 截图区域下坐标
 * @return table|nil 识别结果表，失败返回nil
]]
local function performOcrWithSnapshot(left, top, right, bottom)
    -- 1. 加载OCR模型
    if not PaddleOcr.loadModel(true) then
        print("ERROR: Failed to load PaddleOCR model")
        return nil
    end

    -- 2. 获取屏幕截图
    local bitmap = LuaEngine.snapShot(left, top, right, bottom)
    if not bitmap then
        print("ERROR: Failed to capture screen snapshot")
        return nil
    end

    -- 3. 执行OCR识别（带padding处理）
    local jsonResult = PaddleOcr.detectWithPadding(bitmap, 50, 0xff, 0xff, 0xff)
    
    -- 4. 释放bitmap资源
    LuaEngine.releaseBmp(bitmap)
    
    if not jsonResult then
        print("WARNING: OCR detection returned no results")
        return nil
    end

    -- 5. 解析JSON结果
    local success, resultData = pcall(jsonLib.decode, jsonResult)
    if not success or type(resultData) ~= "table" then
        print("ERROR: Failed to parse OCR results JSON")
        return nil
    end

    return resultData
end

--[[
 * 格式化输出OCR结果
 * @param results table OCR识别结果表
]]
local function printOcrResults(results)
    if not results or #results == 0 then
        print("INFO: No OCR results to display")
        return
    end

    print(string.format("\nOCR Results (Count: %d):", #results))
    print("----------------------------------------")
    print("Index | Text              | Coordinates")
    print("----------------------------------------")
    
    for idx, item in ipairs(results) do
        if type(item) == "table" and item.label and item.x and item.y then
            print(string.format("%-5d | %-16s | (%4d, %4d)", 
                              idx, 
                              item.label:sub(1, 16),  -- 限制文本长度
                              item.x, item.y))
        else
            print(string.format("WARNING: Invalid data structure at index %d", idx))
        end
    end
    print("----------------------------------------")
end

-- 主函数
local function main()
    print("Starting OCR processing...")
    local startTime = os.time()

    -- 定义截图区域（示例坐标）
    local captureArea = {
        left = 0,
        top = 0,
        right = 500,
        bottom = 500
    }

    -- 执行OCR识别
    local ocrResults = performOcrWithSnapshot(
        captureArea.left,
        captureArea.top,
        captureArea.right,
        captureArea.bottom
    )

    -- 处理结果
    if ocrResults then
        printOcrResults(ocrResults)
        
        -- 这里可以添加结果处理逻辑
        -- 例如：if ocrResults[1].label == "目标文本" then ...
    else
        print("OCR processing failed")
    end

    print(string.format("Processing completed in %.3f seconds", os.time() - startTime))
    return ocrResults ~= nil
end

-- 执行主程序
local success = main()

-- 返回执行状态（可用于被其他脚本调用时判断）
return success
```

## 7. PaddleOcr.detect 直接识别当前屏幕范围内的文本 (PaddleOcr.detect)
**函数:** `LuaEngine.detect(left,top,right,bottom)`  
**描述:** PaddleOcr.detect 直接识别当前屏幕范围内的文本

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| left | number | 是 | 截图区域左坐标 |
| top | number | 是 | 截图区域上坐标 |
| right | number | 是 | 截图区域右坐标 |
| bottom | number | 是 | 截图区域下坐标 |

**返回值类型 | 说明 |
| :--- | :--- |
| string | json字符串 |

**示例:**
```lua
-- 导入必要的Java类库
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')

-- 导入NX Assist Lua扩展库
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.PaddleOcr')

--[[
 * PaddleOCR识别处理函数
 * 该函数加载OCR模型并执行文本识别，输出识别结果
 * @return boolean 操作是否成功
]]
local function performOcrDetection()
    -- 1. 加载OCR模型
    local isModelLoaded = PaddleOcr.loadModel(true)
    if not isModelLoaded then
        print("Error: Failed to load PaddleOCR model")
        return false
    end

    -- 2. 执行OCR识别（全屏识别，坐标参数为0,0,0,0）
    local jsonResult = PaddleOcr.detect(0, 0, 0, 0)
    if jsonResult == nil then
        print("Warning: OCR detection returned no results")
        return true  -- 视为成功执行但无结果
    end

    -- 3. 解析JSON结果
    local success, resultData = pcall(jsonLib.decode, jsonResult)
    if not success or resultData == nil then
        print("Error: Failed to parse OCR results JSON")
        return false
    end

    -- 4. 输出格式化结果
    if type(resultData) == "table" then
        for index, item in ipairs(resultData) do
            if type(item) == "table" and item.label and item.x and item.y then
                print(string.format("OCR Result [%d]: Text='%s', Coordinates=(%d, %d)", 
                                    index, item.label, item.x, item.y))
            else
                print(string.format("Warning: Invalid data structure at index %d", index))
            end
        end
    else
        print("Warning: Unexpected OCR results format")
    end

    return true
end

-- 主执行流程
local function main()
    local startTime = os.time()
    print("Starting PaddleOCR processing...")
    
    local success = performOcrDetection()
    
    print(string.format("Processing completed in %.2f seconds", os.time() - startTime))
    return success
end

-- 执行主函数
return main()
```

## 8. setScreenScale 屏幕缩放 (setScreenScale)
**函数:** `setScreenScale(type,width,height,[scale])`  
**描述:** 此功能用于非目标分辨率设备上找色和点击时使用

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| type | number | 是 | 0:关闭缩放,1:开启缩放 |
| width | number | 是 | 脚本开发时使用的设备宽度 |
| height | number | 是 | 脚本开发时使用的设备高度 |
| scale | number | 否 | 默认为1,0代表只对传入函数的坐标进行缩放,
从函数返回坐标的不缩放,即为当前使用设备真实坐标。
1代表传入函数的坐标进行缩放，函数返回的坐标进行反向缩放 |

返回值:
无



**示例:**
```lua
--假设作者在720分辨率上开发的脚本，在1080分辨率上使用
setScreenScale(1,720,1280,0)--开启缩放
local x=-1 y=-1
x,y=findMultiColor(0,0,0,0,"778787|675699-101010","10|11|2F9772-000000|123456-101010|23|57|353535",0,0.9)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
setScreenScale(0,720,1280,0)--关闭缩放
```

## 9. keepCapture 截图到内存 (keepCapture)
**函数:** `keepCapture()`  
**描述:** keepCapture 截图到内存

**返回值:**
无

**示例:**
```lua
keepCapture()
sleep(10000)
releaseCapture()
```

## 10. releaseCapture 删除内存中的截图 (releaseCapture)
**函数:** `releaseCapture()`  
**描述:** releaseCapture 删除内存中的截图

**返回值:**
无

**示例:**
```lua
keepCapture()
sleep(10000)
releaseCapture()
```

## 11. snapShot 截图并保存 (snapShot)
**函数:** `snapShot(path,path,[left,top,right,bottom])`  
**描述:** snapShot 截图并保存

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| path | string | 是 | 文件路径 |
| left | number | 是 | 截图区域左坐标 |
| top | number | 是 | 截图区域上坐标 |
| right | number | 是 | 截图区域右坐标 |
| bottom | number | 是 | 截图区域下坐标 |

**返回值:**
无

**示例:**
```lua
snapShot("/mnt/sdcard/test.png",0,0,100,100)
```

## 12. getPixelColor 获取指定坐标的颜色值 (getPixelColor)
**函数:** `getPixelColor(x,y,[type])`  
**描述:** getPixelColor 获取指定坐标的颜色值

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x | number | 是 | 屏幕坐标x |
| y | number | 是 | 屏幕坐标y |
| type | number | 否 | type=1时返回一个整数默认不填写type是返回颜色的16进制字符串 | 

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 返回指定坐标处的颜色值 |

**示例:**
```lua
local pixel = getPixelColor(100,100)
print(pixel)
```

## 13. getScreenPixel 获取区域像素数组 (getScreenPixel)
**函数:** `getScreenPixel(x1,y1,x2,y2)`  
**描述:** getScreenPixel 获取区域像素数组

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | 区域左坐标 |
| y1 | number | 是 | 区域上坐标 |
| x2 | number | 是 | 区域右坐标 |
| y2 | number | 是 | 区域下坐标 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | w,h,arr，其中w,h是获取范围的长宽,arr是返回的数组,如果w,h小于0则表明失败 |

**示例:**
```lua
--当前测试在720x1280模式下

function printRGB(color)
	local r,g,b = colorToRGB(color)
	print("col:".."=>"..r..","..g..","..b)
end

local w,h,arr = getScreenPixel(0,0,0,0)

print("image size:"..w..","..h)
local x = 567
local y = 1231
local color = arr[y * w + (x + 1)]
local cc = getPixelColor(x,y)
printRGB(cc)
printRGB(color)
```

## 14. colorDiff 颜色比对 (colorDiff)
**函数:** `colorDiff(color1,color2)`  
**描述:** colorDiff 颜色比对

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 整数型:两个颜色的红、绿、蓝三个分量的差值之总和 |

**示例:**
```lua
local diff = colorDiff(0x998899,0x777777)
local diff1 = colorDiff("999999","888888")
print(diff)
print(diff1)
```

## 15. colorToRGB 颜色值转化R,G,B三个分量 (colorToRGB)
**函数:** `colorToRGB(color)`  
**描述:** colorToRGB 颜色值转化R,G,B三个分量

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| color | string | 是 | 16进制颜色值,格式为"BBGGRR" |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 十进制颜色红分量 |
| number | 十进制颜色绿分量 |
| number | 十进制颜色蓝分量 |

**示例:**
```lua
local r,g,b = colorToRGB(0x998899)
print(r,g,b)
```

## 16. cmpColor 指定坐标颜色比对 (cmpColor)
**函数:** `cmpColor(x,y,color,sim)`  
**描述:** cmpColor 指定坐标颜色比对

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x | number | 是 | x:整数型,需要对比颜色的X坐标 |
| y | number | 是 | y:整数型,需要对比颜色的Y坐标 |
| color | string | 是 | color:字符串,待比较的16进制颜色,格式为"BBGGRR" |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number |1为匹配到,0为没有匹配到 |

**示例:**
```lua
local r = cmpColor(100,100,"787878-101010|123456",0.9)
print(r)
```

## 17. getColorNum 获取区域颜色数量 (getColorNum)
**函数:** `getColorNum(x1,y1,x2,y2,color,sim)`  
**描述:** getColorNum 获取区域颜色数量

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,区域左上X坐标 |
| y1 | number | 是 | y1:整数型,区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,区域右下X坐标 |
| y2 | number | 是 | y2:整数型,区域右下Y坐标 |
| color | string | 是 | color:字符串,要找的16进制颜色,格式为"BBGGRR" |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 整数型,指定区域颜色匹配相同的像素点个数 |

**示例:**
```lua
local number = getColorNum(10,50,600,600,"888888",0.8)
print(number)
```

## 18. cmpColorEx 区域多点比色 (cmpColorEx)
**函数:** `cmpColorEx(mul_color,sim)`  
**描述:** cmpColorEx 区域多点比色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| mul_color | string | 是 | mul_color:字符串,需要对比的点xy坐标和16进制颜色,格式为(X坐标|Y坐标|16进制颜色),需要偏色用“-”号分隔 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 整型，1为完全匹配,0为没有完全匹配到 |

**示例:**
```lua
local r = cmpColorEx("500|600|787878|101010-102030,200|105|FFFFFF",0.9)
print(r)
```

## 19. cmpColorExT 区域多点比色 (cmpColorExT)
**函数:** `cmpColorExT(tb)`  
**描述:** cmpColorExT 区域多点比色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| tb | table | 是 | 数组的各项内容如下  

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 整型，1为完全匹配,0为没有完全匹配到 |

**示例:**
```lua
local r = cmpColorExT({"500|600|787878|101010-102030,200|105|FFFFFF",0.9})
print(r)
```

## 20. findMultiColor 区域多点找色 (findMultiColor)
**函数:** `findMultiColor(x1,y1,x2,y2,first_color,offset_color,dir,sim)`  
**描述:** findMultiColor 区域多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| first_color | string | 是 | first_color:要对比的16进制颜色|
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |
| offset_color | string | 是 | offset_color:字符串,偏移颜色 |
| dir | number | 是 | dir:整数型,查找方向.

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 如果成功返回对应点的坐标x,y,否则返回-1,-1 |

**示例:**
```lua
local x=-1 y=-1
x,y=findMultiColor(0,0,0,0,"778787|675699-101010","10|11|2F9772-000000|123456-101010,23|57|353535",0,0.9)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 21. findMultiColorT 区域多点找色 (findMultiColorT)
**函数:** `findMultiColorT(tb)`  
**描述:** findMultiColorT 区域多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| tb | table | 是 | 传递是的是一个数组,数组的每一项如下|


**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 如果成功返回对应点的坐标x,y,否则返回-1,-1 |

**示例:**
```lua
local x=-1 y=-1
x,y=findMultiColorT({0,0,0,0,"778787|675699-101010","10|11|2F9772-000000|123456-101010,23|57|353535",0,0.9})
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 22. findMultiColorAll 区域多点找色 (findMultiColorAll)
**函数:** `findMultiColorAll(x1,y1,x2,y2,first_color,offset_color,dir,sim)`  
**描述:** findMultiColorAll 区域多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| first_color | string | 是 | first_color:要对比的16进制颜色|
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |
| offset_color | string | 是 | offset_color:字符串,偏移颜色 |
| dir | number | 是 | dir:整数型,查找方向.

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| table | 如果成功返回所有满足要求的表格数组 |

**示例:**
```lua
local ret =findMultiColorAll(0,0,0,0,"778787|675699-101010","10|11|2F9772-000000|123456-101010,23|57|353535",0,0.9)
if ret ~= nil then
	print(ret)
end
```

## 23. findMultiColorAllT 区域多点找色 (findMultiColorAllT)
**函数:** `findMultiColorAllT(tb)`  
**描述:** findMultiColorAllT 区域多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| tb | table | 是 | 传递是的是一个数组,数组的每一项如下|

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| table | 如果成功返回所有满足要求的表格数组 |

**示例:**
```lua
local ret =findMultiColorAllT({0,0,0,0,"778787|675699-101010","10|11|2F9772-000000|123456-101010,23|57|353535",0,0.9})
if ret ~= nil then
	print(ret)
end
```

## 24. findColor 多点找色 (findColor)
**函数:** `findColor(x1, y1, x2, y2,color,dir,sim)`  
**描述:** findColor 多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| color | string | 是 | color:要对比的16进制颜色|
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |
| dir | number | 是 | dir:整数型,查找方向.

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | x,y 对应找到的坐标 |

**示例:**
```lua
local x=-1 y=-1
ret,x,y=findColor(0,0,0,0,"121212-000000|aabbcc-030303|ddeeff-202020",0,1.0)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 25. findColorT 多点找色 (findColorT)
**函数:** `findColorT(tb)`  
**描述:** findColorT 多点找色

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
tb | table | 是 | 传递是的是一个数组,数组的每一项如下|

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 如果成功返回对应点的坐标x,y,否则返回-1,-1 |

**示例:**
```lua
local x=-1 y=-1
ret,x,y=findColorT({0,0,0,0,"121212-000000|aabbcc-030303|ddeeff-202020",0,1.0})
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 26. findStr 区域文字查找 (findStr)
**函数:** `findStr(x1, y1, x2, y2,text,colorfmt,sim)`  
**描述:** findStr 区域文字查找

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| text | string | 是 | text:字符串,要找的文字,多个图片用“|”号分隔 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 如果成功返回对应点的坐标x,y,否则返回-1,-1 |

**示例:**
```lua
setDict(0,"dict.txt")
useDict(0)
local x=-1 y=-1
ret,x,y=findStr(0,0,0,0,"中|国","FFFFFF-101010",0.98)
if x~=-1 and y ~=-1 then
	print("x:"..x.." y:"..y)
end
```

## 27. createOcr 创建本地光学ocr对象 (createOcr)
**函数:** `createOcr(lang,[mode],[engine])`  
**描述:** 创建一个tresseract-ocr(4.1.0)本地光学ocr对象

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| lang | string | 是 | 字库语言文件名称，不填则默认eng(只支持一般的中英+数字+标点符号)|
|mode | number | 否 | mode:整数型,0 仅检测方向和文本 1 自动检测方向和文本(OSD) 2 自动检测，但不进行OSD或OCR处理 3 自动PSM模式(但不含OSD) 4 所识别图片的字体大小不一 5 所识别图片当作整块竖向文字区域 6 所识别图片当作整块横向文字区域 (默认值) 7 所识别图片当作一行文字 8 所识别图片当作单个词语 9 所识别图片当作单个圆型围绕的词语 10 所识别图片当作单个英文/数字字符 11 尽可能识别更多的字符(无顺序要求) 12 分散稀疏的OSD检测|
| engine | number | 否 | engine:整数型,0 传统tesseract引擎(默认值) 1 lstm神经网络引擎|



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 一个tresseract-ocr对象句柄 |

**示例:**
```lua
local handle = createOcr("chi-sim",3,3)
local text = ocrText(handle,0,0,0,0,"ffffff-0f0f0f")
if text ~= nil then
	print("ocr text:"..text)
end
releaseOcr(handle)
```

## 28. setWhiteList 设置本地光学ocr白名单 (setWhiteList)
**函数:** `setWhiteList(handle,whitelist)`  
**描述:** setWhiteList 设置本地光学ocr白名单

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| handle | string | 是 | handle:通过createOcr创建的句柄
| whitelist | string | 是 | 不在这字符集里面的字符全部被过滤掉
说明:如果你选择的光学ocr识别引擎使用的是lstm神经网络模式那么白名单将失效 |

**返回值:**
无

**示例:**
```lua
local handle = createOcr(nil,0)
if handle ~= nil then
setWhiteList(handle,"abcdefg")
local text = ocrText(handle,0,0,0,0,"ffffff-0f0f0f")
if text ~= nil then
	print("ocr text:"..text)
end
releaseOcr(handle)
end
```

## 29. ocrText 本地光学ocr识别 (ocrText)
**函数:** `ocrText(handle,x1,y1,x2,y2,colorfmt)`  
**描述:** ocrText 本地光学ocr识别

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| handle | string | 是 | handle:通过createOcr创建的句柄
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回查找的字符串 |

**示例:**
```lua
local handle = createOcr("chi-sim")
local text = ocrText(handle,0,0,0,0,"ffffff-0f0f0f")
if text ~= nil then
	print("ocr text:"..text)
end
releaseOcr(handle)
```

## 30. ocrTextEx 本地光学ocr识别扩展方法 (ocrTextEx)
**函数:** `ocrTextEx(handle,x1,y1,x2,y2,[ThresholdTypes],[thresh],[maxthresh])`  
**描述:** ocrTextEx 本地光学ocr识别扩展方法


**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| handle | string | 是 | handle:通过createOcr创建的句柄
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| ThresholdTypes | number | 否 | ThresholdTypes:整数型,0 全局阈值 1 自适应阈值 2 基于本地区域的阈值 (默认值) |
| thresh | number | 否 | thresh:整数型,全局或自适应阈值,取值范围0-255 (默认值:128) |
| maxthresh | number | 否 | maxthresh:整数型,自适应阈值的最大值,取值范围0-255 (默认值:255) |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回查找的字符串 |

**示例:**
```lua
local handle = createOcr()
local text = ocrTextEx(handle,0,0,200,200,8,150,255)
if text ~= nil then
	print("ocr text:"..text)
end
releaseOcr(handle)
```

## 31. ocrTextExJ 本地光学ocr返回结果和坐标 (ocrTextExJ)
**函数:** `ocrTextExJ(handle,x1,y1,x2,y2,[splitType],[ThresholdTypes],[thresh],[maxthresh])`  
**描述:** ocrTextExJ 本地光学ocr返回结果和坐标

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| handle | string | 是 | handle:通过createOcr创建的句柄
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| splitType | number | 否 | splitType:整数型,0 不分割 1 按行分割 2 按列分割 3 按块分割 (默认值) |
| ThresholdTypes | number | 否 | ThresholdTypes:整数型,0 全局阈值 1 自适应阈值 2 基于本地区域的阈值 (默认值) |
| thresh | number | 否 | thresh:整数型,全局或自适应阈值,取值范围0-255 (默认值:128) |
| maxthresh | number | 否 | maxthresh:整数型,自适应阈值的最大值,取值范围0-255 (默认值:255) |



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 返回查找的结果的表 |

**示例:**
```lua
local handle = createOcr()
local text = ocrTextExJ(handle,0,0,200,200,3,8,150,255)
if text ~= nil then
	for i = 1,#ret then
		print("ocr text:"..ret[i])
	end
end
releaseOcr(handle)
```

## 32. releaseOcr 释放本地光学ocr对象 (releaseOcr)
**函数:** `releaseOcr(handle)`  
**描述:** releaseOcr 释放本地光学ocr对象

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| handle | string | 是 | handle:通过createOcr创建的句柄

**返回值:**
无

**示例:**
```lua
local handle = createOcr("chi-sim")
local text = ocrText(handle,0,0,0,0,"ffffff-0f0f0f")
if text ~= nil then
	print("ocr text:"..text)
end
releaseOcr(handle)
```

## 33. ocr 点阵ocr识别 (ocr)
**函数:** `ocr(x1, y1, x2, y2,colorfmt,sim)`  
**描述:** ocr 点阵ocr识别

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
useDict(0)
local str = ocr(0,0,0,0,"FFFFFF-101010",0.98)
if str ~= nil then
	print(str)
end
```

## 34. ocrj 返回区域范围内所有识别文字的坐标 (ocrj)
**函数:** `ocrj(x1, y1, x2, y2,colorfmt,sim)`  
**描述:** ocrj 返回区域范围内所有识别文字的坐标

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | json格式的字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
useDict(0)
local str = ocrj(0,0,0,0,"FFFFFF-101010",0.98)
if str ~= nil then
	print(str)
end
```

## 35. findStrEx 区域文字查找高级版 (findStrEx)
**函数:** `findStrEx(x1, y1, x2, y2,text,colorfmt,sim)`  
**描述:** findStrEx 区域文字查找高级版

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| text | string | 是 | text:字符串,要找的文字,多个图片用“|”号分隔 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 | 

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | ret:返回一个json数组字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
useDict(0)
ret=findStrEx(0,0,0,0,"中|国","FFFFFF-101010",0.98)
if ret ~= nil then
	print(ret)
end
```

## 36. findStrExNew 区域文字查找高级版 (findStrExNew)
**函数:** `findStrExNew(index,x1, y1, x2, y2,text,colorfmt,sim)`  
**描述:** findStrExNew 区域文字查找高级版

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 是 | index:字库的索引 |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| text | string | 是 | text:字符串,要找的文字,多个图片用“|”号分隔 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 | 



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | ret:返回一个json数组字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
ret,x,y=findStrExNew(0,0,0,0,0,"中|国","FFFFFF-101010",0.98)
if ret ~= nil then
	print(ret)
end
```

## 37. ocrjNew 返回区域范围内所有识别文字的坐标 (ocrjNew)
**函数:** `ocrjNew(index,x1, y1, x2, y2,colorfmt,sim)`  
**描述:** ocrjNew 返回区域范围内所有识别文字的坐标

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 是 | index:字库的索引 |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 | 



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | json格式的字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
local str = ocrjNew(0,0,0,0,0,"FFFFFF-101010",0.98)
if str ~= nil then
	print(str)
end
```

## 38. ocrNew 点阵ocr识别 (ocrNew)
**函数:** `ocrNew(index,x1, y1, x2, y2,colorfmt,sim)`  
**描述:** ocrNew 点阵ocr识别

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 是 | index:字库的索引 |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| colorfmt | string | 是 | colorfmt:字符串,文字的颜色格式 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 | 



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串 |

**示例:**
```lua
setDict(0,"dict.txt")
local str = ocrNew(0,0,0,0,0,"FFFFFF-101010",0.98)
if str ~= nil then
	print(str)
end
```

## 39. ocrEx 本地神经网络ocr (ocrEx)
**函数:** `ocrEx(x1, y1, x2, y2,[padding],[maxSlidLen],[boxscoreth],[boxthresh],[clipratio],[doAngle],[mostAngle])`  
**描述:** ocrEx 本地神经网络ocr

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 是 | index:字库的索引 |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| padding | number | 否 | padding: 整数型,周围添加隔离空白区域大小,默认不写是50 |
| maxSlidLen | number | 否 | maxSlidLen:整数型,长宽按比例缩放最大值，默认不写为0 |
| boxscoreth | number | 否 | boxscoreth：浮点类型，框置信度默认不写是0.6 |
| boxthresh | number | 否 | boxthresh：浮点类型，默认0.3 |
| clipratio | number | 否 | clipratio：框大小倍率，默认2.0 |
| doAngle | boolean | 否 | doAngle：布尔类型，是否角度分析默认为true |
| mostAngle | boolean | 否 | mostAngle: 布尔类型,是否进行方向分析默认为true |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 数组类型 |

**示例:**
```lua
local r = ocrEx(210,371,360,495,50,0,0.60,0.30,2.00,true,true)
if r ~= nil then
	for i=1,#r do
		print(r[i])
	end
end
sleep(1000)
```

## 40. ocrBinaryEx 二值化本地神经网络ocr (ocrBinaryEx)
**函数:** `ocrBinaryEx(x1, y1, x2, y2,color_desc,[padding],[maxSlidLen],[boxscoreth],[boxthresh],[clipratio],[doAngle],[mostAngle])`  
**描述:** ocrBinaryEx 二值化本地神经网络ocr

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 是 | index:字库的索引 |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| color_desc | string | 是 | color_desc:字符串,文字的颜色格式 |
| padding | number | 否 | padding: 整数型,周围添加隔离空白区域大小,默认不写是50 |
| maxSlidLen | number | 否 | maxSlidLen:整数型,长宽按比例缩放最大值，默认不写为0 |
| boxscoreth | number | 否 | boxscoreth：浮点类型，框置信度默认不写是0.6 |
| boxthresh | number | 否 | boxthresh：浮点类型，默认0.3 |
| clipratio | number | 否 | clipratio：框大小倍率，默认2.0 |
| doAngle | boolean | 否 | doAngle：布尔类型，是否角度分析默认为true |
| mostAngle | boolean | 否 | mostAngle: 布尔类型,是否进行方向分析默认为true |

**说明:** 这些参数可以通过群里的神经网络ocr.exe工具进行调试到自己满意值后直接生成代码 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 数组类型 |

**示例:**
```lua
local r = ocrBinaryEx(210,371,360,495,"FFFFFF-303030",50,0,0.60,0.30,2.00,true,true)
if r ~= nil then
	for i=1,#r do
		print(r[i])
	end
end
sleep(1000)
```

## 41. setDict 设置字库文件 (setDict)
**函数:** `setDict(index,name)`  
**描述:** setDict 设置字库文件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 否 | 节点索引 |
| name | string | 是 | name:字库文件名 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 0失败1成功 |

**示例:**
```lua
setDict(0,"dict.txt")
```

## 42. useDict 使用字库 (useDict)
**函数:** `useDict(index)`  
**描述:** useDict 使用字库

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 否 | 节点索引 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 0失败1成功 |

**示例:**
```lua
useDict(0)
```

## 43. findCircle 霍夫变换找圆 (findCircle)
**函数:** `findCircle(x1, y1, x2, y2,dp,minDist,param1,param2,minRadius,maxRadius)`  

**描述:** findCircle 霍夫变换找圆
**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| dp | number | 是 | dp:双精度浮点数,累加器分辨率与图像分辨率的反比,默认1.6 |
| minDist | number | 是 | minDist:整数型,检测到的圆的中心,其之间的最小距离,默认10 | 

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | ret:数组类型[{x:centerX,y=centerY,r=radius},{x=centerX1,y=centerY1,r=radius1}] |

**示例:**
```lua
local ret = findCircle(0,0,0,0,1.6,10,230,40,12,20)
print(ret)
```

## 44. findPicEx 高级区域找图 (findPicEx)
**函数:** `findPicEx(x1, y1, x2, y2,pic_name,sim)`  
**描述:** findPicEx 高级区域找图

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| pic_name | string | 是 | pic_name:字符串,要找的图片名字,多个图片用“|”号分隔 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 则对应找到的索引 x,y 对应找到的坐标 |

**示例:**
```lua
local x=-1 y=-1
ret,x,y=findPicEx(0,0,0,0,"1.png|2.png|3.png",1.0)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 45. findImage opencv模板匹配找图 (findImage)
**函数:** `findImage(x1, y1, x2, y2,pic_name,sim)`  
**描述:** findImage opencv模板匹配找图

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| pic_name | string | 是 | pic_name:字符串,要找的图片名字,多个图片用“|”号分隔 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |


**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | x,y 对应找到的坐标 |

**示例:**
```lua
local x=-1 y=-1
ret,x,y=findImage(0,0,0,0,"1.png|2.png|3.png",1.0)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 46. findPicAllPoint 匹配目标图片所有位置 (findPicAllPoint)
**函数:** `findPicAllPoint(x1, y1, x2, y2,pic_name,sim)`  
**描述:** findPicAllPoint 匹配目标图片所有位置

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| pic_name | string | 是 | pic_name:字符串,要找的图片名字,多个图片用“|”号分隔 |
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 返回一个坐标数组 |

**示例:**
```lua
local x=-1 y=-1
local arr = findPicAllPoint(0,0,0,0,"my.png",0.98)
if arr ~= nil then
	for n = 1,#arr do
		print("pos:",arr[n].x,arr[n].y)
	end
end
```

## 47. findPic 区域找图 (findPic)
**函数:** `findPic(x1, y1, x2, y2,pic_name,delta_color,dir,sim)`  
**描述:** findPic 区域找图

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| pic_name | string | 是 | pic_name:字符串,要找的图片名字,多个图片用“|”号分隔 | 
| delta_color | string | 是 | delta_color:16进制字符串,偏色 |
| dir | number | 是 | dir:整数型,查找方向: 0:表示从左上向右下查找; 1:表示从中心往四周查找; 2:表示从右下向左上查找;3:表示从左下向右上查找; 4:表示从右上向左下查找|
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | x,y 对应找到的坐标 |

**示例:**
```lua
local x=-1 y=-1
ret,x,y=findPic(0,0,0,0,"1.png|2.png|3.png","101010",0,1.0)
if x~=-1 and y ~=-1 then
	tap(x,y)
end
```

## 48. findPicFast 快速区域找图 (findPicFast)
**函数:** `findPicFast(x1, y1, x2, y2,pic_name,delta_color,dir,sim)`  
**描述:** findPicFast 快速区域找图

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| pic_name | string | 是 | pic_name:字符串,要找的图片名字,多个图片用“|”号分隔 | 
| delta_color | string | 是 | delta_color:16进制字符串,偏色 |
| dir | number | 是 | dir:整数型,查找方向: 0:表示从左上向右下查找; 1:表示从中心往四周查找; 2:表示从右下向左上查找;3:表示从左下向右上查找; 4:表示从右上向左下查找|
| sim | number | 是 | sim:双精度浮点数,相似度,取值范围0-1 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 所有找到的坐标数组列表 |

**示例:**
```lua
local index = -1
local retList = nil
index,retList=findPicFast(0,0,0,0,"1.png|2.png|3.png","101010",0,1.0)
print(index,retList)
```

## 49. isDisplayDead 检测屏幕区域所有色点是否变化 (isDisplayDead)
**函数:** `isDisplayDead(x1, y1, x2, y2,time)`  
**描述:** isDisplayDead 检测屏幕区域所有色点是否变化

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| x1 | number | 是 | x1:整数型,查找区域左上X坐标 |
| y1 | number | 是 | y1:整数型,查找区域左上Y坐标 |
| x2 | number | 是 | x2:整数型,查找区域右下X坐标 |
| y2 | number | 是 | y2:整数型,查找区域右下Y坐标 |
| time | number | 是 | time:整数型,检测时间,单位秒 |



**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | true表示没有变化，false有变化 |

**示例:**
```lua
local r = isDisplayDead(100,100,300,300,10)
print(r)
```

