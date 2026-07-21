# 交互方法 (ui)

类型: function
包含方法数: 28

## 1. closeWindow - closeWindow(关闭窗口) 

**说明**: 关闭窗口

**功能说明**:
关闭指定句柄的窗口，可以选择是否保存当前配置

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| saveconfig | boolean | 否 | 是否保存当前配置（默认 false） |

返回值:
无

**示例代码**:
```javascript

function onLoadEvent(handle)
end
function onClickEvent(handle,id)
if id == "idClose" then
	closeWindow(handle,true)
end
end
showUI("myui.ui",600,600,onLoadEvent,onClickEvent)

```

---

## 2. getUIWebViewUrl - getUIWebViewUrl(获取当前浏览器的地址) 

**说明**: 获取当前浏览器的地址

**功能说明**:
获取当前浏览器的地址


参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 当前浏览器的地址 |

**示例代码**:
```javascript
/**
 * 说明: 点击事件处理函数
 * 参数: 
 *  handle: 窗口句柄
 *  event: 事件类型
 *  arg1: 事件参数1
 *  arg2: 事件参数2
 *  arg3: 事件参数3
 * 返回值: 无
 */
function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		local url = getUIWebViewUrl(handle,0,"idWebView")
		print(url)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 3. setUIWebViewUrl - setUIWebViewUrl(设置浏览器地址) 

**说明**: 设置浏览器地址

**功能说明**:
设置当前浏览器的地址

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| url | string | 是 | 要设置的浏览器地址 |

返回值:
无

**示例代码**:
```javascript
/**
 * 说明: 点击事件处理函数
 * 参数: 
 *  handle: 窗口句柄
 *  event: 事件类型
 *  arg1: 事件参数1
 *  arg2: 事件参数2
 *  arg3: 事件参数3
 * 返回值: 无
 */
function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIWebViewUrl(handle,0,"idWebView","http://www.lrappsoft.com")
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 4. getUISelected - getUISelected(获取单选框或者下拉框当前选中项) 

**说明**: 获取单选框或者下拉框当前选中项

**功能说明**:
获取单选框或者下拉框当前选中项

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 选中控件的序号 |

**示例代码**:
```javascript
/**
 * 说明: 点击事件处理函数
 * 参数: 
 *  handle: 窗口句柄
 *  event: 事件类型
 *  arg1: 事件参数1
 *  arg2: 事件参数2
 *  arg3: 事件参数3
 * 返回值: 无
 */
function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		local r = getUISelected(handle,0,"idSelect1")
		print(r)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
	end
end
local ret = showUI("lgcat.ui",-1,-1,onUIEvent)
print(ret)

```

---

## 5. getUISelectText - getUISelectText(获取单选框或者下拉框当前选中项的文本内容) 

**说明**: 获取单选框或者下拉框当前选中项的文本内容

**语法**:
```
getUISelectText(handle,pageidx,idname)
```

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 选中控件的文本内容 |

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		local r = getUISelectText(handle,0,"idRadiobox")
		print(r)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
	end
end
local ret = showUI("lgcat.ui",-1,-1,onUIEvent)
print(ret)

```

---

## 6. getUIText - getUIText(获取控件显示的文本内容) 

**说明**: 获取文本框，输入框，按钮,多选框控件显示的文本内容

**功能说明**:
获取文本框，输入框，按钮,多选框控件显示的文本内容

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 控件显示的文本内容 |

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIText(handle,arg1,arg2,"test123")
		setUIText(handle,arg1,"idEdit1","你好懒人")
		setUIText(handle,arg1,"idtext","你好懒人")
		setUIText(handle,arg1,"idCheckbox","你好懒人")

		print(getUIText(handle,arg1,arg2))
		print(getUIText(handle,arg1,"idEdit1"))
		print(getUIText(handle,arg1,"idtext"))
		print(getUIText(handle,arg1,"idCheckbox"))
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 7. setUIText - setUIText(设置控件文本) 

**说明**: 设置文本框，输入框，按钮,多选框等显示的文本或名称

**功能说明**:
设置文本框，输入框，按钮,多选框等显示的文本或名称

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| text | string | 是 | 要设置的文本内容 |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIText(handle,arg1,arg2,"test123")
		setUIText(handle,arg1,"idEdit1","你好懒人")
		setUIText(handle,arg1,"idtext","你好懒人")
		setUIText(handle,arg1,"idCheckbox","你好懒人")
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 8. setUISelect - setUISelect(设置单选框或者下拉框选项被选中) 

**说明**: 设置单选框或者下拉框选项被选中

**功能说明**:
设置单选框或者下拉框选项被选中

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| index | number | 是 | 要选中的选项索引(从0开始) |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUISelect(handle,arg1,"idRadiobox",3)--选中第4个
		setUISelect(handle,arg1,"idSelect1",1)--选中第2个
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 9. setUICheck - setUICheck(设置多选框被选中或者反选) 

**说明**: 设置多选框被选中或者反选

**功能说明**:
设置多选框被选中或者反选

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| selected | boolean | 是 | 是否选中(true为选中，false为反选) |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUICheck(handle,arg1,"idCheckbox",true)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 10. getUICheck - getUICheck(获取多选框状态) 

**说明**: 获取多选框状态

**功能说明**:
获取多选框状态

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |


**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示选中，false表示反选 |

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		local ret = setUICheck(handle,arg1,"idCheckbox")
		print(ret)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 11. getUIEnable - getUIEnable(获取控件是否可用) 

**说明**: 获取控件是否可用

**功能说明**:
获取控件是否可用

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示可用，false表示禁用 |

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIEnable(handle,arg1,arg2,false)
		local enable = getUIEnable(handle,arg1,arg2)
		if enable then
			print("控件:"..arg2.."可用")
		else
			print("控件:"..arg2.."被禁用")
		end
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 12. setUIEnable - setUIEnable(设置控件是否可用) 

**说明**: 设置控件是否可用

**功能说明**:
设置控件是否可用

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| enable | boolean | 是 | 是否可用(true为可用，false为禁用) |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIEnable(handle,arg1,arg2,false)
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 13. getUIVisible - getUIVisible(获取当前控件可见的值) 

**说明**: 获取当前控件可见的值

**功能说明**:
获取当前控件可见的值

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 可见值(0表示隐藏，1表示可见) |

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		local visible = getUIVisible(handle,arg1,"idtext")
		print("当前控件可见值:"..visible)
		setUIVisible(handle,arg1,"idtext",8)
		visible = getUIVisible(handle,arg1,"idtext")
		print("修改后控件的可见值:"..visible)
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 14. setUIVisible - setUIVisible(设置控件隐藏或可见) 

**说明**: 设置控件隐藏或可见

**功能说明**:
设置控件隐藏或可见

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| visible | number | 是 | 可见值(0表示隐藏，1表示可见) |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUIVisible(handle,arg1,"idtext",8)
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 15. setUITextColor - setUITextColor(修改控件字体颜色) 

**说明**: 修改控件字体颜色

**功能说明**:
修改控件字体颜色,包括文本框，输入框

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| textcolor | string | 是 | 字体颜色的十六进制字符串，例如"#ffff0000"表示红色 |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		setUITextColor(handle,arg1,arg2,"#ffff0000")
		setUITextColor(handle,arg1,"idtext","#ffff0000")
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 16. setUIBackground - setUIBackground(设置窗口或者控件的背景) 

**说明**: 设置窗口或者控件的背景

**功能说明**:
设置窗口或者控件的背景

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 窗口句柄 |
| pageidx | number | 是 | 要设置的控件所在page页的索引(从0开始) |
| idname | string | 是 | 控件的id |
| bg | string | 是 | 背景颜色的十六进制字符串，例如"#ffff0000"表示红色 |

返回值: 无

**示例代码**:
```javascript

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onclick" then
		print("设置按钮颜色",arg1,arg2)
		setUIBackground(handle,arg1,arg2,"#ffff0000")
		elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		if arg1 == false then
			exitScript()
		end
	end
end

showUI("uidemo.ui",-1,-1,onUIEvent)

```

---

## 17. setUIConfig - setUIConfig(给指定窗口ui加载一个配置) 

**说明**: 把指定的配置json字符串写入到configname中

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| configname | string | 是 | 配置文件名称 |
| configstr | string | 是 | 配置的具体json字符串 |

返回值: 无

**示例代码**:
```javascript

local json = "{\"page2\":{\"idSelect1\":\"0\"},\"page1\":{\"idRadiobox\":\"2\"},\"page0\":{\"idCheckbox\":\"true\",\"idRadiobox\":\"2\",\"idLabel1\":\"显示内容\",\"idButton\":\"点击我\",\"idEdit1\":\"输入内容\"}}"
setUIConfig("main.config",json)
showUI("myui.ui",600,600);

```

---

## 18. toast - toast(弹窗显示信息) 

**说明**: 在屏幕指定位置弹出信息框，当坐标x,y同时为0的时候，默认向下横向居中显示，5秒后自动消失

**功能说明**:
在屏幕指定位置弹出信息框，当坐标x,y同时为0的时候，默认向下横向居中显示，5秒后自动消失

参数: 
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| text | string | 是 | 要显示的文本内容 |
| x | number | 否 | 弹窗显示的x坐标(默认0) |
| y | number | 否 | 弹窗显示的y坐标(默认0) |
| textsize | number | 否 | 字体大小(默认24) |

返回值: 无

**示例代码**:
```javascript

for i=1,100 do
	toast("消息显示\n测试计数"..i.."次数")
	sleep(100)
end
hideToast()

```

---

## 19. hideToast - hideToast(关闭消息显示) 

**说明**: 关闭消息显示

参数: 无

返回值: 无

**示例代码**:
```javascript

for i=1,100 do
	toast("消息显示\n测试计数"..i.."次数")
	sleep(100)
end
hideToast()

```

---

## 20. showUI - showUI(显示一个自定义的界面) 

**说明**: 显示一个自定义的界面

**功能说明**:
显示一个用户自定义弹窗界面,当窗口关闭时返回配置数据

**参数说明**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| uifile | string | 是 | 要显示的ui文件名称 |
| w | number | 否 | 窗口宽度(默认-1,表示填满) |
| h | number | 否 | 窗口高度(默认-1,表示填满) |
| onUIEvent | function | 否 | 窗口事件回调函数 |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 界面配置的json字符串 |
注意:当onUIEvent参数不填写的时候，继续和退出按钮将接管用户点击事件，点击退出的时候会直接结束脚本，继续将保存用户配置并关闭窗口

**示例代码**:
```lua

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onload" then
		print("窗口被加载了")
	elseif event == "onclick" then
		print("按钮点击事件:",arg1,arg2)
		keyPress("home")
	elseif event == "onchecked" then
		print("多选框选中或反选事件:",arg1,arg2)
		elseif event == "onselected" then
		print("单选框或下拉框选中事件:",arg1,arg2)
	end
end

```

## 21. showUIEx - showUIEx 显示一个自定义的界面

**方法名称**: 显示一个自定义的界面,这个是showUI的扩展版本，该方法可以设置窗口的坐标位置

**语法**:
```
showUIEx(uifile,[x],[y],[w],[h],[onUIEvent])
功能说明:显示一个用户自定义弹窗界面,当窗口关闭时返回配置数据
```

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| uifile | string | 是 | 要显示的ui文件名称或路径，也可以是ui文件的字符串形式 |
| x | number | 否 | 窗口x坐标(默认0,表示居中) |
| y | number | 否 | 窗口y坐标(默认0,表示居中) |
| w | number | 否 | 窗口宽度(默认-1,表示填满) |
| h | number | 否 | 窗口高度(默认-1,表示填满) |
| onUIEvent | function | 否 | 窗口事件回调函数 |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 界面配置的json字符串 |
**功能说明**:
显示一个用户自定义弹窗界面,当窗口关闭时返回配置数据

**参数说明**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| uifile | string | 是 | 要显示的ui文件名称或路径，也可以是ui文件的字符串形式 |
| x | number | 否 | 窗口显示的x坐标(默认0) |
| y | number | 否 | 窗口显示的y坐标(默认0) |
| w | number | 否 | 窗口宽度(默认-1,表示填满) |
| h | number | 否 | 窗口高度(默认-1,表示填满) |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 界面配置的json字符串 |
注意:当onUIEvent参数不填写的时候，继续和退出按钮将接管用户点击事件，点击退出的时候会直接结束脚本，继续将保存用户配置并关闭窗口

**示例代码**:
```lua

function onUIEvent(handle,event,arg1,arg2,arg3)
	if event == "onload" then
		print("窗口被加载了")
	elseif event == "onclick" then
		print("按钮点击事件:",arg1,arg2)
		keyPress("home")
	elseif event == "onchecked" then
		print("多选框选中或反选事件:",arg1,arg2)
	elseif event == "onselected" then
		print("单选框或者下拉框事件:",arg1,arg2)
	elseif event == "onclose" then
		print("关闭窗口",arg1)
		closeWindow(handle,arg1)
		elseif event == "onwebviewjsevent" then
		print("webview事件",arg1,arg2,arg3)
	end
end

local ret = showUIEx("test.ui",100,100,600,600,onUIEvent)

print(ret)

```


## 22. createHUD - createHUD 创建一个HUD用于显示

**方法名称**: 创建一个HUD用于显示

**语法**:
```lua
createHUD()
功能说明:HUD是一个悬浮在屏幕上的画面可以实时更新
```

**功能说明**:
HUD是一个悬浮在屏幕上的画面可以实时更新
返回值:整数类型,是一个HUD实例句柄

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| integer | HUD实例句柄 |

**示例代码**:
```lua

local id = createHUD()
showHUD(id,"HelloWorld!",12,"0xffff0000","0xffffffff",0,100,0,228,32)--显示HUD内容
sleep(2000)
showHUD(id,"HelloWorld!",12,"0xffff0000","msgbox_click.png",0,100,0,228,32) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)

```

---

## 23. showHUD - showHUD 显示HUD或者刷新

**方法名称**: 显示HUD或者刷新

**语法**:
```lua
showHUD(id,text,size,color,bg,pos,x,y,width,height,[leftpadding,toppadding,rightpadding,bottompadding],[align_text])
功能说明:显示更新HUD
```

**功能说明**:
显示更新HUD

**参数说明**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | integer | 是 | 用于标示HUD |
| text | string | 是 | 提示信息,将在屏幕上以HUD形式显示 |
| size | integer | 是 | 表示提示信息的字体大小 |
| color | string | 是 | 表示提示信息的字体颜色，格式为ARGB |
| bg | string | 是 | 表示提示信息的背景颜色，可以是ARGB，也可以是图片文件名称 |
| pos | integer | 是 | 表示提示信息的原点位置，0 - 左上角，1 - 居中，2 - 水平居中， 3 - 垂直居中 |
| x | integer | 是 | 表示提示信息相对原点的坐标偏移值 |
| y | integer | 是 | 表示提示信息相对原点的坐标偏移值 |
| width | integer | 是 | 表示提示信息显示的宽高 |
| height | integer | 是 | 表示提示信息显示的高 |
| leftpadding | integer | 否 | 左边内边距默认不填写是3 |
| toppadding | integer | 否 | 上边内边距默认不填写是3 |
| rightpadding | integer | 否 | 右边内边距默认不填写是3 |
| bottompadding | integer | 否 | 下边内边距默认不填写是3 |
| align_text | integer | 否 | 文本对齐方式默认不写为1， 0左上 1居中 2上水平居中 3左垂直居中 4左下 5右上 6右边垂直居中 7右下 8下水平居中 |

**返回值**:
无

**示例代码**:
```lua

local id = createHUD()
showHUD(id,"HelloWorld!",12,"0xffff0000","0xffffffff",0,100,100,0,0)--显示HUD内容
sleep(2000)
showHUD(id,"HelloWorld!",12,"0xffff0000","msgbox_click.png",0,100,100,0,0) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)

```

---

## 24. hideHUD - hideHUD 隐藏并销毁HUD

**方法名称**: 隐藏并销毁HUD

**语法**:
```lua
hideHUD(id)
```

**参数**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| id | integer | 是 | 用于标示HUD |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功隐藏HUD |
注意:调用此方法后不能再用当前id句柄继续showHUD，如果需要调用showHUD需要重新createHUD

**示例代码**:
```lua

local id = createHUD()
showHUD(id,"HelloWorld!",12,"0xffff0000","0xffffffff",0,100,0,228,32)--显示HUD内容
sleep(2000)
showHUD(id,"HelloWorld!",12,"0xffff0000","msgbox_click.png",0,100,0,228,32) --变更显示的HUD内容
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)
id = createHUD() --创建一个HUD
showHUD(id,"hello",12,"0xffff0000","test.bmp",0,100,0,200,200)
sleep(5000)
hideHUD(id) --隐藏HUD
sleep(3000)

```



## 25. createDragView - createDragView 创建可拖动视图

**方法名称**: 创建可拖动视图

**语法**:
```lua
createDragView(x, y, width, height, imagePath)
```

**参数**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | integer | 是 | 视图初始X坐标(必须，屏幕坐标系的像素值) |
| y | integer | 是 | 视图初始Y坐标(必须，屏幕坐标系的像素值) |
| width | integer | 是 | 视图宽度(必须，像素单位) |
| height | integer | 是 | 视图高度(必须，像素单位) |
| imagePath | string | 是 | 文本型,表示提示信息的背景颜色，可以是ARGB，也可以是图片文件名称 |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| integer | 可拖动视图句柄(成功) |
| nil | 创建失败 |

**示例代码**:
```lua

-- 在屏幕坐标(100,100)位置创建50x50大小的可拖动视图
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")
if not handle then
    print("创建可拖动视图失败")
end

sleep(100000)

```

---

## 26. getDragViewPos - getDragViewPos 获取可拖动视图位置

**方法名称**: 获取可拖动视图当前位置

**语法**:
```lua
getDragViewPos(handle)
```

**参数**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | integer | 是 | 可拖动视图句柄(必须，由createDragView创建) |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功获取位置 |
| number | 视图当前X坐标 |
| number | 视图当前Y坐标 |  

**示例代码**:
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

---

## 27. removeDragView - removeDragView 移除可拖动视图

**方法名称**: 移除可拖动视图

**语法**:
```lua
removeDragView(handle)
```

**参数**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | integer | 是 | 可拖动视图句柄(必须，由createDragView创建) |

**返回值**:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功移除视图 |

**示例代码**:
```lua

local handle = createDragView(100, 100, 50, 50, "0xff00ff00")

-- 使用视图...

-- 移除视图
removeDragView(handle)

```

---

## 28. setDragViewOnClick - setDragViewOnClick 设置可拖动视图点击回调

**方法名称**: 设置可拖动视图点击回调

**语法**:
```lua
setDragViewOnClick(handle, callback)
```

**参数**:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | integer | 是 | 可拖动视图的句柄(由createDragView创建) |
| callback | function | 是 | 点击回调函数，格式为 function(handle,x,y) |
| handle | 被点击的视图句柄 |
| x,y | 点击位置的屏幕坐标 |

**返回值**:
无

**示例代码**:
```lua

-- 创建绿色可拖动视图
local handle = createDragView(100, 100, 50, 50, "0xff00ff00")

-- 设置点击回调
setDragViewOnClick(handle, function(h,x,y)
    print(string.format("视图%d被点击于(%f,%f)", h,x,y))
    -- 点击后移除视图
    removeDragView(h) 
end)

-- 保持脚本运行
sleep(100000)

```

---

