# 虚拟屏相关方法 (virtualscreen)

## 1. virtualDisplay.createVirtualDisplay 创建一个虚拟屏幕 (virtualDisplay.createVirtualDisplay)
**函数:** `virtualDisplay.createVirtualDisplay(w,h,dpi)`  
**描述:** virtualDisplay.createVirtualDisplay 创建一个虚拟屏幕

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| w | number | 是 | 整数类型，表示长 |
| h | number | 是 | 整数类型，表示宽 |
| dpi | number | 是 | 整数类型，表示dpi |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number | 一个整数类型的虚拟屏幕id |

**示例:**
```lua
--[[
虚拟屏幕控制脚本
功能：创建并管理Android虚拟显示屏，支持显示控制、应用运行、截图和触摸测试
环境要求：Android 10及以上系统，需root或激活模式
]]

-- 获取当前运行环境类型和SDK版本
local type = getRunEnvType()  -- 0=root/激活模式, 其他=无障碍或者手动模式
local sdkVerInt = tonumber(getSdkVersion()) -- 获取Android SDK版本

-- 环境检查
if type ~= 0 then
    print("虚拟屏功能必须root或者激活模式才能使用")
    exitScript()
end

-- 系统版本检查(Android 10=API 29)
if sdkVerInt >= 29 then
	print(string.format("当前系统版本: Android %s", getOsVersionName()))
else
	print(string.format("虚拟屏需要Android 10及以上系统，当前系统版本: Android %s", getOsVersionName()))
    exitScript()
end

-- 创建虚拟显示屏(720x1280, 320dpi)
displayId = virtualDisplay.createVirtualDisplay(720, 1280, 320)

-- 设置脚本停止时的回调函数(关闭虚拟屏)
setStopCallBack(function()
    virtualDisplay.closeVirtualDisplay(displayId)
end)

-- 虚拟屏创建结果处理
if displayId ~= -1 then
    print("虚拟屏创建成功，ID:", displayId)
    virtualDisplay.switchToVirtualDisplay(displayId)  -- 切换到虚拟显示屏
    
    -- 虚拟屏窗口显示配置
    config = {
        x = 100,                     -- 窗口X坐标
        y = 100,                     -- 窗口Y坐标
        width = 480,                 -- 窗口宽度
        height = 800,                -- 窗口高度
        hastitle = true,             -- 显示标题栏
        title = "虚拟屏幕测试",         -- 标题文字
        titlesize = 13,               -- 标题字体大小
        titlecolor = 0xffffffff,      -- 标题字体颜色(ARGB)
        titlebgcolor = 0xdd294a7a,    -- 标题栏背景色
        hasclose = true,              -- 显示关闭按钮
        closecolor = 0xffffffff,     -- 关闭按钮颜色
        hastoggle = true,             -- 显示切换按钮
        togglecolor = 0xffffffff,     -- 切换按钮颜色
        enableresize = true,          -- 允许调整大小
        resizecolor = 0xffffffff      -- 调整大小控件颜色
    }
    
    -- 显示虚拟屏窗口
    function onShowDisplay()
        local result = virtualDisplay.showVirtualDisplay(displayId, config)
        print("虚拟屏显示结果:", result)
    end
    
    -- 在虚拟屏中运行应用
    function onRunApp()
        -- 参数：包名, 显示ID, 是否前台运行
        local result = virtualDisplay.runAppWithVirtualDisplay(
            "moe.shizuku.privileged.api", displayId, true)
        
        if not result then
            print("错误：未找到指定包名的应用")
            exitScript()
        end
        sleep(1000)
        keyPress("home")  -- 返回桌面
    end
    
    -- 虚拟屏截图功能
    function onSnapShot()
        -- 截图区域(0,0,300,300)
        local bmp = virtualDisplay.snapToBitmap(displayId, 0, 0, 300, 300)
        print("截图结果:", bmp)
        ui.setImageViewEx("imgId1", bmp)  -- 在UI中显示截图
        snapShot("/sdcard/test.png")     -- 保存截图到文件
    end
    
    -- 虚拟屏触摸测试
    function onTouchEvent()
        -- 模拟触摸操作(按下->移动->抬起)
        virtualDisplay.touchDown(displayId, 1, 100, 1000)
        for i = 1, 500 do
            virtualDisplay.touchMove(displayId, 1, 100, 1000 - i)
            sleep(1)
        end
        virtualDisplay.touchUp(displayId, 1)
    end
    
    -- 创建UI界面
	local wintitle = "虚拟屏幕测试"
    ui.newLayout(wintitle)
    -- 添加控制按钮
    ui.addButton(wintitle, "btn1", "显示虚拟屏幕", -2, -2)
    ui.addLine(wintitle, "lineId1", 10, -2)
    ui.addButton(wintitle, "btn2", "运行app", -2, -2)
    ui.newRow(wintitle, "row1")
    ui.addButton(wintitle, "btn3", "虚拟屏截图", -2, -2)
    ui.addLine(wintitle, "lineId1", 10, -2)
    ui.addButton(wintitle, "btn4", "触摸测试", -2, -2)
    -- 绑定按钮事件
    ui.setOnClick("btn1", "onShowDisplay()")
    ui.setOnClick("btn2", "onRunApp()")
    ui.setOnClick("btn3", "onSnapShot()")
    ui.setOnClick("btn4", "onTouchEvent()")
    -- 添加截图显示区域
    ui.newRow(wintitle, "row2")
    ui.addImageView(wintitle, "imgId1", "")
    
    -- 计算并设置UI显示位置(适配屏幕旋转)
    local displayWidth, displayHeight = getDisplaySize()
    local rotation = getDisplayRotate()
    local isOddRotation = rotation % 2 ~= 0
    local screenWidth = isOddRotation and displayHeight or displayWidth
    local screenHeight = isOddRotation and displayWidth or displayHeight
    
    -- 显示UI界面(右下角位置)
    ui.show(wintitle, true, 100, screenHeight)
    sleep(10000000)  -- 保持脚本运行
else
    print("虚拟屏创建失败")
end
```

## 2. virtualDisplay.closeVirtualDisplay 销毁虚拟屏 (virtualDisplay.closeVirtualDisplay)
**函数:** `virtualDisplay.closeVirtualDisplay(displayId)`  
**描述:** virtualDisplay.closeVirtualDisplay 销毁虚拟屏

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | any | 是 | displayId参数 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 3. virtualDisplay.showVirtualDisplay 小窗口显示一个虚拟屏里面的内容 (virtualDisplay.showVirtualDisplay)
**函数:** `virtualDisplay.showVirtualDisplay(displayId,config)`  
**描述:** virtualDisplay.showVirtualDisplay 小窗口显示一个虚拟屏里面的内容

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| config | string | 否 | 配置表(必选)，包含以下可选字段:
- x: 窗口X坐标(整数，默认0)
- y: 窗口Y坐标(整数，默认0)
- width: 窗口宽度(整数，默认600)
- height: 窗口高度(整数，默认600)
- hastitle: 是否显示标题栏(布尔值，默认true)
- title: 窗口标题文本(字符串)
- titlecolor: 标题文字颜色(ARGB格式，默认0xFFFFFFFF白色)
- titlebgcolor: 标题栏背景色(ARGB格式，默认0xFF87CEFA天蓝色)
- hasclose: 是否显示关闭按钮(布尔值，默认true)
- closecolor: 关闭按钮颜色(ARGB格式，默认0xFFFFFFFF白色)
- hasresize: 是否显示设置窗口大小按钮(布尔值，默认true)
- resizecolor: 设置窗口大小按钮颜色(ARGB格式，默认0xFFFFFFFF白色)
- hastoggle: 是否显示窗口收缩按钮(布尔值，默认true)
- togglecolor: 设置窗口收缩按钮颜色(ARGB格式，默认0xFFFFFFFF白色)
- titlesize:设置标题栏字体大小 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 4. virtualDisplay.snapToBitmap 虚拟屏截图 (virtualDisplay.snapToBitmap)
**函数:** `virtualDisplay.snapToBitmap(displayId,x,y,w,h)`  
**描述:** virtualDisplay.snapToBitmap 虚拟屏截图

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| x | number | 是 | 窗口X坐标(整数)
- y: 窗口Y坐标(整数)
- w: 窗口宽度(整数)
- h: 窗口高度(整数) |
| 说明 | string | 是 | 如果x,y,w,h 都写0表示全屏截图 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| object | 返回一个Java的Bitmap对象 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 5. virtualDisplay.switchToVirtualDisplay 切换虚拟屏幕 (virtualDisplay.switchToVirtualDisplay)
**函数:** `virtualDisplay.switchToVirtualDisplay(displayId)`  
**描述:** virtualDisplay.switchToVirtualDisplay 切换虚拟屏幕

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| 说明 | string | 是 | 当虚拟屏幕创建好后，如果想在这个虚拟屏里面实现图色功能，就需要用这个方法指定此虚拟屏幕的id 如果想切换回系统主屏只需要将id指定为0即可 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 6. virtualDisplay.runAppWithVirtualDisplay 在虚拟屏里面运行指定应用 (virtualDisplay.runAppWithVirtualDisplay)
**函数:** `virtualDisplay.runAppWithVirtualDisplay(displayId,pkg,forcestopapp)`  
**描述:** virtualDisplay.runAppWithVirtualDisplay 在虚拟屏里面运行指定应用

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| pkg | string | 是 | 已安装的app包名 |
| forcestopapp | string | 是 | 每次启动是否强制先关闭之前已运行的实例 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 7. virtualDisplay.tap 虚拟屏里面点击 (virtualDisplay.tap)
**函数:** `virtualDisplay.tap(displayId,x,y)`  
**描述:** virtualDisplay.tap 虚拟屏里面点击

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| x,y | string | 是 | 要点击的坐标 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 8. virtualDisplay.touchDown 虚拟屏里面模拟手指按下 (virtualDisplay.touchDown)
**函数:** `virtualDisplay.touchDown(displayId,id,x,y)`  
**描述:** virtualDisplay.touchDown 虚拟屏里面模拟手指按下

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| id | string | 是 | 手指id （0-5） x,y 要点击的坐标 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 9. virtualDisplay.touchUp 虚拟屏里面模拟手指弹起 (virtualDisplay.touchUp)
**函数:** `virtualDisplay.touchUp(displayId,id)`  
**描述:** virtualDisplay.touchUp 虚拟屏里面模拟手指弹起

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| id | string | 是 | 手指id （0-5） |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 10. virtualDisplay.touchMove 虚拟屏里面模拟手指滑动 (virtualDisplay.touchMove)
**函数:** `virtualDisplay.touchMove(displayId,id,x,y)`  
**描述:** virtualDisplay.touchMove 虚拟屏里面模拟手指滑动

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| id | string | 是 | 手指id （0-5） x,y 要点击的坐标 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.createVirtualDisplay 的完整例子
```

## 11. virtualDisplay.touchMove 虚拟屏里面模拟手指增强滑动 (virtualDisplay.touchMoveEx)
**函数:** `virtualDisplay.touchMoveEx(displayId,id,x,y)`  
**描述:** virtualDisplay.touchMove 虚拟屏里面模拟手指增强滑动

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| id | string | 是 | 模拟手指的索引号0-5之间 |
| x | number | 是 | 整数型,当前屏幕横坐标 |
| y | number | 是 | 整数型,当前屏幕纵坐标 |
| time | number | 是 | 整数型,滑动到x,y坐标点所需要的时间单位是毫秒 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
-- 获取当前运行环境类型和SDK版本
local type = getRunEnvType()  -- 0=root/激活模式, 其他=无障碍或者手动模式
local sdkVerInt = tonumber(getSdkVersion())  -- 获取Android SDK版本

-- 环境检查
if type ~= 0 then
    print("虚拟屏功能必须root或者激活模式才能使用")
    exitScript()
end

-- 系统版本检查(Android 10=API 29)
if sdkVerInt >= 29 then
	print(string.format("当前系统版本: Android %s", getOsVersionName()))
else
	print(string.format("虚拟屏需要Android 10及以上系统，当前系统版本: Android %s", getOsVersionName()))
    exitScript()
end

displayId = virtualDisplay.createVirtualDisplay(720 , 1280 , 320)

setStopCallBack(function ()
	virtualDisplay.closeVirtualDisplay(displayId)
end)

if displayId ~= - 1 then
	print("创建虚拟屏幕成功:" , displayId)
	virtualDisplay.switchToVirtualDisplay(displayId)
	config = {
		x = 100 ,
		y = 100 ,
		width = 480 ,
		height = 800 ,
		hastitle = true ,
		title = "虚拟屏测试" ,
		titlesize = 13 ,
		titlecolor = 0xffffffff ,
		titlebgcolor = 0xdd294a7a ,
		hasclose = true ,
		closecolor = 0xffffffff ,
		hastoggle = true ,
		togglecolor = 0xffffffff ,
		enableresize = true ,
		resizecolor = 0xffffffff
	}
	
	function onShowDisplay()
		local result = virtualDisplay.showVirtualDisplay(displayId , config)
		local result1 = virtualDisplay.runAppWithVirtualDisplay("moe.shizuku.privileged.api" , displayId , true)
		print(result,result1)
		sleep(1000)
		keyPress("home")
	end
	
	function onTouchEvent()
		virtualDisplay.touchDown(displayId , 1 , 100 , 1000)
		virtualDisplay.touchMoveEx(displayId , 1 , 100 , 300,1000)
		virtualDisplay.touchUp(displayId , 1)
	end
	
	ui.newLayout("layout1")
	ui.addButton("layout1" , "btn1" , "显示虚拟屏幕" , - 2 , - 2)
	ui.addLine("layout1" , "lineId1" , 10 , - 2)
	ui.addButton("layout1" , "btn2" , "增强滑动例子" , - 2 , - 2);
	ui.setOnClick("btn1","onShowDisplay()")
	ui.setOnClick("btn2","onTouchEvent()")
	local displayWidth , displayHeight = getDisplaySize()
	local rotation = getDisplayRotate()
	local isOddRotation = rotation % 2 ~= 0
	local screenWidth = isOddRotation and displayHeight or displayWidth
	local screenHeight = isOddRotation and displayWidth or displayHeight
	ui.show("layout1" , true , 100 , screenHeight)
	sleep(10000000)
else
	print("创建虚拟屏幕失败,请检查系统版本，系统最低要求10及以上才能使用虚拟屏幕")
end
```

## 12. virtualDisplay.swipe 虚拟屏里面模拟滑动 (virtualDisplay.swipe)
**函数:** `virtualDisplay.swipe(displayId,x1,y1,x2,y2)`  
**描述:** virtualDisplay.swipe 虚拟屏里面模拟滑动

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| x1 | number | 是 | 整数型,划动的起点x坐标 |
| y1 | number | 是 | 整数型,划动的起点y坐标 |
| x2 | number | 是 | 整数型,划动的终点x坐标 |
| y2 | number | 是 | 整数型,划动的终点y坐标 |
| time | number | 是 | 整数型,滑动到x,y坐标点所需要的时间单位是毫秒 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
-- 获取当前运行环境类型和SDK版本
local type = getRunEnvType()  -- 0=root/激活模式, 其他=无障碍或者手动模式
local sdkVerInt = tonumber(getSdkVersion())  -- 获取Android SDK版本

-- 环境检查
if type ~= 0 then
    print("虚拟屏功能必须root或者激活模式才能使用")
    exitScript()
end

-- 系统版本检查(Android 10=API 29)
if sdkVerInt >= 29 then
	print(string.format("当前系统版本: Android %s", getOsVersionName()))
else
	print(string.format("虚拟屏需要Android 10及以上系统，当前系统版本: Android %s", getOsVersionName()))
    exitScript()
end

displayId = virtualDisplay.createVirtualDisplay(720 , 1280 , 320)

setStopCallBack(function ()
	virtualDisplay.closeVirtualDisplay(displayId)
end)

if displayId ~= - 1 then
	print("创建虚拟屏幕成功:" , displayId)
	virtualDisplay.switchToVirtualDisplay(displayId)
	config = {
		x = 100 ,
		y = 100 ,
		width = 480 ,
		height = 800 ,
		hastitle = true ,
		title = "虚拟屏测试" ,
		titlesize = 13 ,
		titlecolor = 0xffffffff ,
		titlebgcolor = 0xdd294a7a ,
		hasclose = true ,
		closecolor = 0xffffffff ,
		hastoggle = true ,
		togglecolor = 0xffffffff ,
		enableresize = true ,
		resizecolor = 0xffffffff
	}
	
	function onShowDisplay()
		local result = virtualDisplay.showVirtualDisplay(displayId , config)
		local result1 = virtualDisplay.runAppWithVirtualDisplay("moe.shizuku.privileged.api" , displayId , true)
		print(result,result1)
		sleep(1000)
		keyPress("home")
	end
	
	function onTouchEvent()
		virtualDisplay.swipe(displayId , 100 , 100,500,100,1000)
	end
	
	ui.newLayout("layout1")
	ui.addButton("layout1" , "btn1" , "显示虚拟屏幕" , - 2 , - 2)
	ui.addLine("layout1" , "lineId1" , 10 , - 2)
	ui.addButton("layout1" , "btn2" , "滑动例子" , - 2 , - 2);
	ui.setOnClick("btn1","onShowDisplay()")
	ui.setOnClick("btn2","onTouchEvent()")
	local displayWidth , displayHeight = getDisplaySize()
	local rotation = getDisplayRotate()
	local isOddRotation = rotation % 2 ~= 0
	local screenWidth = isOddRotation and displayHeight or displayWidth
	local screenHeight = isOddRotation and displayWidth or displayHeight
	ui.show("layout1" , true , 100 , screenHeight)
	sleep(10000000)
else
	print("创建虚拟屏幕失败,请检查系统版本，系统最低要求10及以上才能使用虚拟屏幕")
end
```

## 13. virtualDisplay.keyDown 虚拟屏里面模拟键盘按下 (virtualDisplay.keyDown)
**函数:** `virtualDisplay.keyDown(displayId,keycode)`  
**描述:** virtualDisplay.keyDown 虚拟屏里面模拟键盘按下

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| keycode | number | 是 | 整数类型，请参考keyDown函数说明 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
-- 获取当前运行环境类型和SDK版本
local type = getRunEnvType()  -- 0=root/激活模式, 其他=无障碍或者手动模式
local sdkVerInt = tonumber(getSdkVersion())  -- 获取Android SDK版本

-- 环境检查
if type ~= 0 then
    print("虚拟屏功能必须root或者激活模式才能使用")
    exitScript()
end

-- 系统版本检查(Android 10=API 29)
if sdkVerInt >= 29 then
	print(string.format("当前系统版本: Android %s", getOsVersionName()))
else
	print(string.format("虚拟屏需要Android 10及以上系统，当前系统版本: Android %s", getOsVersionName()))
    exitScript()
end

displayId = virtualDisplay.createVirtualDisplay(720 , 1280 , 320)

setStopCallBack(function ()
	virtualDisplay.closeVirtualDisplay(displayId)
end)

if displayId ~= - 1 then
	print("创建虚拟屏幕成功:" , displayId)
	virtualDisplay.switchToVirtualDisplay(displayId)
	config = {
		x = 100 ,
		y = 100 ,
		width = 480 ,
		height = 800 ,
		hastitle = true ,
		title = "虚拟屏测试" ,
		titlesize = 13 ,
		titlecolor = 0xffffffff ,
		titlebgcolor = 0xdd294a7a ,
		hasclose = true ,
		closecolor = 0xffffffff ,
		hastoggle = true ,
		togglecolor = 0xffffffff ,
		enableresize = true ,
		resizecolor = 0xffffffff
	}
	
	function onShowDisplay()
		local result = virtualDisplay.showVirtualDisplay(displayId , config)
		local result1 = virtualDisplay.runAppWithVirtualDisplay("moe.shizuku.privileged.api" , displayId , true)
		print(result,result1)
		sleep(1000)
		keyPress("home")
	end
	
	function onKeyEvent()
		virtualDisplay.keyDown(displayId , "home")
		sleep(100)
		virtualDisplay.keyUp(displayId , "home")
	end
	
	ui.newLayout("layout1")
	ui.addButton("layout1" , "btn1" , "显示虚拟屏幕" , - 2 , - 2)
	ui.addLine("layout1" , "lineId1" , 10 , - 2)
	ui.addButton("layout1" , "btn2" , "按键例子" , - 2 , - 2);
	ui.setOnClick("btn1","onShowDisplay()")
	ui.setOnClick("btn2","onKeyEvent()")
	local displayWidth , displayHeight = getDisplaySize()
	local rotation = getDisplayRotate()
	local isOddRotation = rotation % 2 ~= 0
	local screenWidth = isOddRotation and displayHeight or displayWidth
	local screenHeight = isOddRotation and displayWidth or displayHeight
	ui.show("layout1" , true , 100 , screenHeight)
	sleep(10000000)
else
	print("创建虚拟屏幕失败,请检查系统版本，系统最低要求10及以上才能使用虚拟屏幕")
end
```

## 14. virtualDisplay.keyUp 虚拟屏里面模拟键盘弹起 (virtualDisplay.keyUp)
**函数:** `virtualDisplay.keyUp(displayId,keycode)`  
**描述:** virtualDisplay.keyUp 虚拟屏里面模拟键盘弹起

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| keycode | number | 是 | 整数类型，请参考keyDown函数说明 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.keyDown
```

## 15. virtualDisplay.keyPress 虚拟屏里面模拟键盘按下并弹起 (virtualDisplay.keyPress)
**函数:** `virtualDisplay.keyPress(displayId,keycode)`  
**描述:** virtualDisplay.keyPress 虚拟屏里面模拟键盘按下并弹起

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| displayId | number | 是 | 创建返回的 |
| 由virtualDisplay.createVirtualDisplay | number | 是 | 创建返回的 |
| keycode | number | 是 | 整数类型，请参考keyDown函数说明 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
--请参考virtualDisplay.keyDown
```

