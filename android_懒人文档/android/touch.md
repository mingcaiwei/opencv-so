# 触控方法 (touch)

## 1. 模拟输入文字 (inputText)
**函数:** `inputText(text)`
**描述:** 模拟输入文字

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| text | string | 是 | 要输入的文本内容 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
inputText("hello nice!!!")
```

## 2. 锁定使用懒人输入法 (imeLib.lock)
**函数:** `imeLib.lock()`
**描述:** 锁定使用懒人输入法

参数:
无

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
setStopCallBack(function(error)
    imeLib.unlock()
end)

imeLib.lock()
imeLib.setText("hello")
```

## 3. 解锁懒人输入法 (imeLib.unlock)
**函数:** `imeLib.unlock()`
**描述:** 解锁懒人输入法

参数:
无

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
setStopCallBack(function(error)
    imeLib.unlock()
end)

imeLib.lock()
imeLib.setText("hello")
```

## 4. 输入法模拟输入文字 (imeLib.setText)
**函数:** `imeLib.setText(text)`
**描述:** 输入法模拟输入文字

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| text | string | 是 | 要输入的文本内容 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
imeLib.setText("hello nice!!!")
```

## 5. 输入法删除一个字符 (imeLib.deleteChar)
**函数:** `imeLib.deleteChar()`
**描述:** 输入法删除一个字符

参数:
无

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
imeLib.setText("hello nice!!!")
imeLib.deleteChar()
```

## 6. 输入法模拟完成输入 (imeLib.finishInput)
**函数:** `imeLib.finishInput()`
**描述:** 输入法模拟完成输入

参数:
无

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
imeLib.setText("hello nice!!!")
imeLib.finishInput()
```

## 7. 输入法输入字符 (imeLib.keyEvent)
**函数:** `imeLib.keyEvent(action, keycode)`
**描述:** 输入法输入字符

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| action | number | 是 | 0表示按下，1表示弹起 |
| keycode | number | 是 | 按键码，请参考android KeyEvent.KEY_CODE* |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
imeLib.keyEvent(0,7) --模拟按下字符"0"
imeLib.keyEvent(1,7) --模拟弹起字符"0"
```

## 8. 点击 (tap)
**函数:** `tap(x, y)`
**描述:** 点击坐标为x,y的点

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 当前屏幕横坐标 |
| y | number | 是 | 当前屏幕纵坐标 |

返回值:
无

示例:
```lua
tap(100, 100)
```

## 9. 长点击 (longTap)
**函数:** `longTap(x, y)`
**描述:** 长点击坐标为x,y的点

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 当前屏幕横坐标 |
| y | number | 是 | 当前屏幕纵坐标 |

返回值:
无

示例:
```lua
longTap(100, 100)
```

## 10. 按下手指 (touchDown)
**函数:** `touchDown(id, x, y)`
**描述:** 按住不放

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 模拟手指的索引号0-4之间 |
| x | number | 是 | 当前屏幕横坐标 |
| y | number | 是 | 当前屏幕纵坐标 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用

返回值:
无

示例:
```lua
touchDown(2, 100, 100)
touchDown(1, 100, 100)
sleep(300)
touchUp(1)
sleep(100)
touchUp(2)
```

## 11. 弹起手指 (touchUp)
**函数:** `touchUp(id)`
**描述:** 弹起手指

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 模拟手指的索引号0-4之间 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
touchDown(2, 100, 100)
touchDown(1, 100, 100)
sleep(300)
touchUp(1)
sleep(100)
touchUp(2)
```

## 12. 模拟滑动 (touchMove)
**函数:** `touchMove(id, x, y)`
**描述:** 模拟滑动

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 模拟手指的索引号0-4之间 |
| x | number | 是 | 当前屏幕横坐标 |
| y | number | 是 | 当前屏幕纵坐标 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
print("开始从下往上滑动")
touchDown(1, 297, 327)
for i = 1, 300 do
    touchMove(1, 297, 327 - i)
end
touchUp(1)
print("滑动结束")
```

## 13. 模拟滑动增强版 (touchMoveEx)
**函数:** `touchMoveEx(id, x, y, time)`
**描述:** 模拟滑动增强版

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 模拟手指的索引号0-4之间 |
| x | number | 是 | 当前屏幕横坐标 |
| y | number | 是 | 当前屏幕纵坐标 |
| time | number | 是 | 滑动到目标坐标点所需的时间，单位是毫秒 |

返回值:
无

示例:
```lua
touchDown(1, 100, 100)
sleep(50)
touchMoveEx(1, 300, 300, 800)
touchUp(1)
```

## 14. 划动 (swipe)
**函数:** `swipe(x1, y1, x2, y2, time)`
**描述:** 模拟从一点滑动到另外一点

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x1 | number | 是 | 划动的起点x坐标 |
| y1 | number | 是 | 划动的起点y坐标 |
| x2 | number | 是 | 划动的终点x坐标 |
| y2 | number | 是 | 划动的终点y坐标 |
| time | number | 是 | 滑动到目标坐标点所需的时间，单位是毫秒 |

注意: 此函数在懒人高级版所有模式下都能使用

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
swipe(200, 200, 800, 200, 500)
```

## 15. 按键 (keyPress)
**函数:** `keyPress(keycode)`
**描述:** 按一下按键并弹起

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| keycode | string/number | 是 | 按键标识符或者数字按键码 |

注意: 此函数运行在root或者激活模式下所有按键全部有效，在无障碍模式下只支持home、back、recent、power四个按键

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
keyPress("home")
```

## 16. 按键按下 (keyDown)
**函数:** `keyDown(keycode)`
**描述:** 按下一个按键不弹起

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| keycode | string/number | 是 | 按键标识符或者数字按键码 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
keyDown("home")
sleep(100)
keyUp("home")
```

## 17. 按键弹起 (keyUp)
**函数:** `keyUp(keycode)`
**描述:** 弹起一个按键

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| keycode | string/number | 是 | 按键标识符或者数字按键码 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 操作结果 |

示例:
```lua
keyDown("home")
sleep(100)
keyUp("home")
```

## 18. 获取用户触摸屏幕坐标 (setOnTouchListener)
**函数:** `setOnTouchListener(onTouchEvent)`
**描述:** 获取用户触摸屏幕坐标

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| onTouchEvent | function | 是 | 回调函数，当用户触摸屏幕时会触发调用并传递坐标 |

注意: 此函数不支持在无障碍模式下使用，只能在激活或者root模式下使用(android虚拟机无效)

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功，false表示失败 |

示例:
```lua
function onTouchEvent(x, y)
    print(x, y)
end
print("开始监听屏幕触摸")
setOnTouchListener(onTouchEvent)
sleep(1000000)
```

## 19. 关闭窗口 (closeWindow)
**函数:** `closeWindow(handle, isaveconfig)`
**描述:** 关闭窗口

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| isaveconfig | boolean | 是 | 是否保存当前界面的配置 |

返回值:
无

示例:
```lua
function onLoadEvent(handle)
end
function onClickEvent(handle, id)
    if id == "idClose" then
        closeWindow(handle, true)
    end
end
showUI("myui.ui", 600, 600, onLoadEvent, onClickEvent)
```

## 20. 获取当前浏览器的地址 (getUIWebViewUrl)
**函数:** `getUIWebViewUrl(handle, pageidx, idname)`
**描述:** 获取当前浏览器的地址

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 当前浏览器的地址 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        local url = getUIWebViewUrl(handle, 0, "idWebView")
        print(url)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 21. 设置浏览器地址 (setUIWebViewUrl)
**函数:** `setUIWebViewUrl(handle, pageidx, idname, url)`
**描述:** 设置浏览器地址

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| url | string | 是 | 要设置的浏览器地址 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIWebViewUrl(handle, 0, "idWebView", "http://www.lrappsoft.com")
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 22. 获取单选框或者下拉框当前选中项 (getUISelected)
**函数:** `getUISelected(handle, pageidx, idname)`
**描述:** 获取单选框或者下拉框当前选中项

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 选中控件的序号 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        local r = getUISelected(handle, 0, "idSelect1")
        print(r)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
    end
end
local ret = showUI("lgcat.ui", -1, -1, onUIEvent)
print(ret)
```

## 23. 获取单选框或者下拉框当前选中项的文本内容 (getUISelectText)
**函数:** `getUISelectText(handle, pageidx, idname)`
**描述:** 获取单选框或者下拉框当前选中项的文本内容

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 选中控件的文本内容 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        local r = getUISelectText(handle, 0, "idRadiobox")
        print(r)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
    end
end
local ret = showUI("lgcat.ui", -1, -1, onUIEvent)
print(ret)
```

## 24. 获取控件显示的文本内容 (getUIText)
**函数:** `getUIText(handle, pageidx, idname)`
**描述:** 获取控件显示的文本内容

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 控件显示的文本内容 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIText(handle, arg1, arg2, "test123")
        setUIText(handle, arg1, "idEdit1", "你好懒人")
        setUIText(handle, arg1, "idtext", "你好懒人")
        setUIText(handle, arg1, "idCheckbox", "你好懒人")

        print(getUIText(handle, arg1, arg2))
        print(getUIText(handle, arg1, "idEdit1"))
        print(getUIText(handle, arg1, "idtext"))
        print(getUIText(handle, arg1, "idCheckbox"))
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 25. 设置控件文本 (setUIText)
**函数:** `setUIText(handle, pageidx, idname, text)`
**描述:** 设置控件文本

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| text | string | 是 | 要设置的文本字符串 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIText(handle, arg1, arg2, "test123")
        setUIText(handle, arg1, "idEdit1", "你好懒人")
        setUIText(handle, arg1, "idtext", "你好懒人")
        setUIText(handle, arg1, "idCheckbox", "你好懒人")
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 26. 设置单选框或者下拉框选项被选中 (setUISelect)
**函数:** `setUISelect(handle, pageidx, idname, index)`
**描述:** 设置单选框或者下拉框选项被选中

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| index | number | 是 | 要选中项的索引(从0开始) |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUISelect(handle, arg1, "idRadiobox", 3) -- 选中第4个
        setUISelect(handle, arg1, "idSelect1", 1) -- 选中第2个
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 27. 设置多选框被选中或者反选 (setUICheck)
**函数:** `setUICheck(handle, pageidx, idname, selected)`
**描述:** 设置多选框被选中或者反选

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| selected | boolean | 是 | 是否被选中 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUICheck(handle, arg1, "idCheckbox", true)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 28. 获取单选框状态 (getUICheck)
**函数:** `getUICheck(handle, pageidx, idname)`
**描述:** 获取单选框状态

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 单选框的状态 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        local ret = setUICheck(handle, arg1, "idCheckbox")
        print(ret)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 29. 获取控件是否可用 (getUIEnable)
**函数:** `getUIEnable(handle, pageidx, idname)`
**描述:** 获取控件是否可用

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 控件是否可用 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIEnable(handle, arg1, arg2, false)
        local enable = getUIEnable(handle, arg1, arg2)
        if enable then
            print("控件:" .. arg2 .. "可用")
        else
            print("控件:" .. arg2 .. "被禁用")
        end
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 30. 设置控件是否可用 (setUIEnable)
**函数:** `setUIEnable(handle, pageidx, idname, enable)`
**描述:** 设置控件是否可用

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| enable | boolean | 是 | true表示可用，false表示不可用 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIEnable(handle, arg1, arg2, false)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 31. 获取当前控件可见的值 (getUIVisible)
**函数:** `getUIVisible(handle, pageidx, idname)`
**描述:** 获取当前控件可见的值

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 控件的可见值 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        local visible = getUIVisible(handle, arg1, "idtext")
        print("当前控件可见值:" .. visible)
        setUIVisible(handle, arg1, "idtext", 8)
        visible = getUIVisible(handle, arg1, "idtext")
        print("修改后控件的可见值:" .. visible)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 32. 设置控件隐藏或可见 (setUIVisible)
**函数:** `setUIVisible(handle, pageidx, idname, visible)`
**描述:** 设置控件隐藏或可见

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| visible | number | 是 | 0表示可见，8表示隐藏不占用空间大小，4表示隐藏但是还是占据空间大小 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUIVisible(handle, arg1, "idtext", 8)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 33. 修改控件字体颜色 (setUITextColor)
**函数:** `setUITextColor(handle, pageidx, idname, textcolor)`
**描述:** 修改控件字体颜色

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| textcolor | string | 是 | 16进制字符串，例如:"0xff00ff00" 或者 "#ff00ff00" |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        setUITextColor(handle, arg1, arg2, "#ffff0000")
        setUITextColor(handle, arg1, "idtext", "#ffff0000")
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 34. 设置窗口或者控件的背景 (setUIBackground)
**函数:** `setUIBackground(handle, pageid, idname, bg)`
**描述:** 设置窗口或者控件的背景

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 当前窗口的句柄 |
| pageid | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| bg | string | 是 | 要设置的背景，可以是ARGB颜色，也可以是图片文件名称 |

返回值:
无

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onclick" then
        print("设置按钮颜色", arg1, arg2)
        setUIBackground(handle, arg1, arg2, "#ffff0000")
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
        if arg1 == false then
            exitScript()
        end
    end
end

showUI("uidemo.ui", -1, -1, onUIEvent)
```

## 35. 给指定窗口ui加载一个配置 (setUIConfig)
**函数:** `setUIConfig(configname, configstr)`
**描述:** 把指定的配置json字符串写入到configname中

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| configname | string | 是 | ui的配置名称 |
| configstr | string | 是 | 配置的具体json字符串 |

返回值:
无

示例:
```lua
local json = "{\"page2\":{\"idSelect1\":\"0\"},\"page1\":{\"idRadiobox\":\"2\"},\"page0\":{\"idCheckbox\":\"true\",\"idRadiobox\":\"2\",\"idLabel1\":\"显示内容\",\"idButton\":\"点击我\",\"idEdit1\":\"输入内容\"}}"
setUIConfig("main.config", json)
showUI("myui.ui", 600, 600)
```

## 36. 弹窗显示信息 (toast)
**函数:** `toast(text, [x, y, textsize])`
**描述:** 在屏幕指定位置弹出信息框，5秒后自动消失

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| text | string | 是 | 要显示的字符串 |
| x | number | 否 | 屏幕横向坐标，默认为0 |
| y | number | 否 | 屏幕纵向坐标，默认为0 |
| textsize | number | 否 | 字体大小，默认为12 |

返回值:
无

示例:
```lua
for i = 1, 100 do
    toast("消息显示\n测试计数" .. i .. "次数")
    sleep(100)
end
hideToast()
```

## 37. 关闭消息显示 (hideToast)
**函数:** `hideToast()`
**描述:** 关闭消息显示

参数:
无

返回值:
无

示例:
```lua
for i = 1, 100 do
    toast("消息显示\n测试计数" .. i .. "次数")
    sleep(100)
end
hideToast()
```

## 38. 显示一个自定义的界面 (showUI)
**函数:** `showUI(uifile, [w, h, onUIEvent])`
**描述:** 显示一个用户自定义弹窗界面，当窗口关闭时返回配置数据

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| uifile | string | 是 | ui文件名称 |
| w | number | 否 | 窗口宽度，-1表示填满 |
| h | number | 否 | 窗口高度，-1表示填满 |
| onUIEvent | function | 否 | 回调函数，处理ui事件 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 界面配置的json字符串 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onload" then
        print("窗口被加载了")
    elseif event == "onclick" then
        print("按钮点击事件:", arg1, arg2)
        keyPress("home")
    elseif event == "onchecked" then
        print("多选框选中或反选事件:", arg1, arg2)
    elseif event == "onselected" then
        print("单选框或者下拉框事件:", arg1, arg2)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
    elseif event == "onwebviewjsevent" then
        print("webview事件", arg1, arg2, arg3)
    end
end

local ret = showUI("test.ui", -1, -1, onUIEvent)

print(ret)
```

## 39. 显示一个自定义的界面扩展版 (showUIEx)
**函数:** `showUIEx(uifile, [x, y, w, h, onUIEvent])`
**描述:** 显示一个用户自定义弹窗界面，支持设置窗口的坐标位置，当窗口关闭时返回配置数据

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| uifile | string | 是 | ui文件名称或路径，也可以是ui文件的字符串形式 |
| x | number | 否 | 悬浮窗的x坐标 |
| y | number | 否 | 悬浮窗的y坐标 |
| w | number | 否 | 窗口宽度，-1表示填满 |
| h | number | 否 | 窗口高度，-1表示填满 |
| onUIEvent | function | 否 | 回调函数，处理ui事件 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 界面配置的json字符串 |

示例:
```lua
function onUIEvent(handle, event, arg1, arg2, arg3)
    if event == "onload" then
        print("窗口被加载了")
    elseif event == "onclick" then
        print("按钮点击事件:", arg1, arg2)
        keyPress("home")
    elseif event == "onchecked" then
        print("多选框选中或反选事件:", arg1, arg2)
    elseif event == "onselected" then
        print("单选框或者下拉框事件:", arg1, arg2)
    elseif event == "onclose" then
        print("关闭窗口", arg1)
        closeWindow(handle, arg1)
    elseif event == "onwebviewjsevent" then
        print("webview事件", arg1, arg2, arg3)
    end
end

local ret = showUIEx("test.ui", 100, 100, 600, 600, onUIEvent)

print(ret)
```

## 40. 创建一个HUD用于显示 (createHUD)
**函数:** `createHUD()`
**描述:** 创建一个HUD用于显示

参数:
无

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | HUD实例句柄 |

示例:
```lua
local id = createHUD()
showHUD(id, "HelloWorld!", 12, "0xffff0000", "0xffffffff", 0, 100, 0, 228, 32) --显示HUD内容
sleep(2000)
showHUD(id, "HelloWorld!", 12, "0xffff0000", "msgbox_click.png", 0, 100, 0, 228, 32) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)
```

## 41. 显示HUD或者刷新 (showHUD)
**函数:** `showHUD(id, text, size, color, bg, pos, x, y, width, height, [padding], [align_text])`
**描述:** 显示或更新HUD

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 用于标示HUD的句柄 |
| text | string | 是 | 提示信息，将在屏幕上以HUD形式显示 |
| size | number | 是 | 提示信息的字体大小 |
| color | string | 是 | 提示信息的字体颜色，格式为ARGB |
| bg | string | 是 | 提示信息的背景颜色，可以是ARGB，也可以是图片文件名称 |
| pos | number | 是 | 提示信息的原点位置，0-左上角，1-居中，2-水平居中，3-垂直居中 |
| x | number | 是 | 提示信息相对原点的x坐标偏移值 |
| y | number | 是 | 提示信息相对原点的y坐标偏移值 |
| width | number | 是 | 提示信息显示的宽度 |
| height | number | 是 | 提示信息显示的高度 |
| padding | table | 否 | 内边距，默认左右上下都为3 |
| align_text | number | 否 | 文本对齐方式，默认不写为1 |

返回值:
无

示例:
```lua
local id = createHUD()
showHUD(id, "HelloWorld!", 12, "0xffff0000", "0xffffffff", 0, 100, 100, 0, 0) --显示HUD内容
sleep(2000)
showHUD(id, "HelloWorld!", 12, "0xffff0000", "msgbox_click.png", 0, 100, 100, 0, 0) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)
```

## 42. 隐藏并销毁HUD (hideHUD)
**函数:** `hideHUD(id)`
**描述:** 隐藏并销毁HUD

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | number | 是 | 用于标示HUD的句柄 |

返回值:
无

注意: 调用此方法后不能再用当前id句柄继续showHUD，如果需要调用showHUD需要重新createHUD

示例:
```lua
local id = createHUD()
showHUD(id, "HelloWorld!", 12, "0xffff0000", "0xffffffff", 0, 100, 0, 228, 32) --显示HUD内容
sleep(2000)
showHUD(id, "HelloWorld!", 12, "0xffff0000", "msgbox_click.png", 0, 100, 0, 228, 32) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)
id = createHUD() --创建一个HUD
showHUD(id, "hello", 12, "0xffff0000", "test.bmp", 0, 100, 0, 200, 200)
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)
```

## 43. 创建可拖动视图 (createDragView)
**函数:** `createDragView(x, y, width, height, imagePath)`
**描述:** 创建可拖动视图

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 视图初始X坐标(屏幕坐标系的像素值) |
| y | number | 是 | 视图初始Y坐标(屏幕坐标系的像素值) |
| width | number | 是 | 视图宽度(像素单位) |
| height | number | 是 | 视图高度(像素单位) |
| imagePath | string | 是 | 背景颜色或图片文件名称 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number/nil | 成功返回可拖动视图的句柄，失败返回nil |

示例:
```lua
-- 在屏幕坐标(100,100)位置创建50x50大小的可拖动视图
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")
if not handle then
    print("创建可拖动视图失败")
end

sleep(100000)
```

## 44. 获取可拖动视图位置 (getDragViewPos)
**函数:** `getDragViewPos(handle)`
**描述:** 获取可拖动视图当前位置

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 可拖动视图句柄(由createDragView创建) |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean/number | 成功返回true, x, y；失败返回false |

示例:
```lua
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")

-- 等待5秒让用户可能拖动视图
for i = 1, 5, 1 do
    sleep(1000)
end

-- 获取当前视图位置
local r, x, y = getDragViewPos(handle)
if r then
    print("当前视图位置:", x, y)
end
```

## 45. 移除可拖动视图 (removeDragView)
**函数:** `removeDragView(handle)`
**描述:** 移除可拖动视图

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 可拖动视图句柄(由createDragView创建) |

返回值:
无

注意事项: 移除后句柄将失效，不可再次使用

示例:
```lua
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")

-- 使用视图...

-- 移除视图
removeDragView(handle)
```

## 46. 设置可拖动视图点击回调 (setDragViewOnClick)
**函数:** `setDragViewOnClick(handle, callback)`
**描述:** 设置可拖动视图点击回调

参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 可拖动视图的句柄(由createDragView创建) |
| callback | function | 是 | 点击回调函数，格式为function(handle,x,y) |

返回值:
无

示例:
```lua
-- 创建绿色可拖动视图
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")

-- 设置点击回调
setDragViewOnClick(handle, function(h, x, y)
    print(string.format("视图%d被点击于(%f,%f)", h, x, y))
    -- 点击后移除视图
    removeDragView(h) 
end)

-- 保持脚本运行
sleep(100000)
```

