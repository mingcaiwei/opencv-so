# 动态UI方法 (dynamicui)

## 1. ui.newLayout 创建一个新的布局 (ui.newLayout)
**函数:** `ui.newLayout(name,...)`  
**描述:** ui.newLayout 创建一个新的布局

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| name | number | 是 | 字符串型,要新建的布局名称，即标题 |
| w | number | 否 | 宽(-1表示填满.-2是自适应)(默认值: 自适应大小),可省略 |
| h | number | 否 | 高(-1表示填满.-2是自适应)(默认值: 自适应大小),可省略 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.show("layout1")
sleep(10000)
```

## 2. ui.show 显示一个布局 (ui.show)
**函数:** `ui.show(name,...)`  
**描述:** ui.show 显示一个布局

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| name | number | 是 | 字符串类型, 要显示的布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.show("layout1")
sleep(10000)
```

## 3. ui.dismiss 关闭一个布局 (ui.dismiss)
**函数:** `ui.dismiss(name)`  
**描述:** ui.dismiss 关闭一个布局

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| name | number | 是 | 字符串类型, 要显示的布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.show("layout1")
for i=3,1,-1 do
toast("倒计时:"..i.."秒关闭窗口",0,0,30)
sleep(1000)
end
hideToast()
ui.dismiss("layout1")
sleep(10000)
```

## 4. ui.newRow  布局换行排列  (ui.newRow)
**函数:** `ui.newRow(layout,rowid,...)`  
**描述:** ui.newRow  布局换行排列 

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btn","hello1")
ui.addButton("layout1","btn1","hello2")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn2","hello3")
ui.show("layout1")
sleep(100000)
```

## 5. ui.addButton  创建一个按钮  (ui.addButton)
**函数:** `ui.addButton(layout,name,text,...)`  
**描述:** ui.addButton  创建一个按钮 

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btn","hello1")
ui.addButton("layout1","btn1","hello2")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn2","hello3")
ui.show("layout1")
sleep(100000)
```

## 6. ui.addTextView  创建文字框控件 (ui.addTextView)
**函数:** `ui.addTextView(layout,name,text,...)`  
**描述:** ui.addTextView  创建文字框控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTextView("layout1","tvId","这是文字布局框")
ui.show("layout1")
sleep(100000)
```

## 7. ui.addEditText  创建输入框控件 (ui.addEditText)
**函数:** `ui.addEditText(layout,name,text,...)`  
**描述:** ui.addEditText  创建输入框控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","这是文字布局框")
ui.show("layout1")
sleep(100000)
```

## 8. ui.addCheckBox  创建多选框控件 (ui.addCheckBox)
**函数:** `ui.addCheckBox(layout,name,text,...)`  
**描述:** ui.addCheckBox  创建多选框控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addCheckBox("layout1", "check_box1","多选框选项1", false)
ui.newRow("layout1", "new_row_1")
ui.addCheckBox("layout1", "check_box2", "多选框选项2", true)
ui.newRow("layout1", "new_row_2")
ui.addCheckBox("layout1", "check_box3", "多选框选项3", true)
ui.show("layout1")
sleep(100000)
```

## 9. ui.addRadioGroup  创建单选框控件 (ui.addRadioGroup)
**函数:** `ui.addRadioGroup(layout,name,list,...)`  
**描述:** ui.addRadioGroup  创建单选框控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addRadioGroup("layout1","单选框",{"选项1", "选项2", "选项3"},0)
ui.show("layout1")
sleep(100000)
```

## 10. ui.addSpinner  创建下拉框控件 (ui.addSpinner)
**函数:** `ui.addSpinner(layout,name,list,select,...)`  
**描述:** ui.addSpinner  创建下拉框控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addSpinner("layout1","spinId1",{"选项1", "选项2", "选项3"},0)
ui.show("layout1")
sleep(100000)
```

## 11. ui.addImageView    创建图像控件 (ui.addImageView)
**函数:** `ui.addImageView(layout,name,path,...)`  
**描述:** ui.addImageView    创建图像控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
local path = getSdPath().."/test.png"
snapShot(path)
if fileExist(path) then
	print("===")
	ui.addImageView("layout1","imgId1",path)
end
ui.show("layout1")
sleep(100000)
```

## 12. ui.addLine    创建线控件 (ui.addLine)
**函数:** `ui.addLine(layout,name)`  
**描述:** ui.addLine    创建线控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addLine("layout1","lineId1",-1,20)
ui.show("layout1")
sleep(100000)
```

## 13. ui.addWebView    创建一个浏览器控件 (ui.addWebView)
**函数:** `ui.addWebView(layout,name,url,...)`  
**描述:** ui.addWebView    创建一个浏览器控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addWebView("layout1","webId","www.baidu.com",500,500)
ui.show("layout1")
sleep(100000)
```

## 14. ui.callJs   调用webview打开的网页中的js函数 (ui.callJs)
**函数:** `ui.callJs(name,js)`  
**描述:** ui.callJs   调用webview打开的网页中的js函数

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local html = "PGh0bWw+DQo8aGVhZD4NCiAgICA8dGl0bGU+5rWL6K+VbHVh5ZKManPnm7jkupLosIPnlKg8L3RpdGxlPg0KICAgIDxtZXRhIGh0dHAtZXF1aXY9IkNvbnRlbnQtVHlwZSIgY29udGVudD0idGV4dC9odG1sO2NoYXJzZXQ9VVRGLTgiPg0KICAgIDxtZXRhIGlkPSJ2aWV3cG9ydCIgbmFtZT0idmlld3BvcnQiIGNvbnRlbnQ9IndpZHRoPWRldmljZS13aWR0aCxpbml0aWFsLXNjYWxlPTEuMCxtaW5pbXVtLXNjYWxlPTEuMCxtYXhpbXVtLXNjYWxlPTEuMCxtaW5pbWFsLXVpIj4NCiAgICA8c2NyaXB0IHR5cGU9InRleHQvamF2YXNjcmlwdCI+DQogICAgICAgIGZ1bmN0aW9uIGNhbGxqcyhhcmcpew0KICAgICAgICAgICAgIGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJjb250ZW50IikuaW5uZXJIVE1MICs9DQogICAgICAgICAgICAgICAgICI8YnJcPmx1Yeiwg+eUqOS6hmpzPT4iK2FyZzsNCiAgICAgICAgfQ0KDQoJCWZ1bmN0aW9uIGNhbGxMdWEoKSB7DQoJCQl3aW5kb3cuYnJpZGdlLmNhbGxMdWEoIm9uSnNDYWxsQmFjayhcInRlc3RcIikiKTsNCgkJfQ0KICAgIDwvc2NyaXB0Pg0KPC9oZWFkPg0KPGJvZHk+DQogICAgPGJyLz48YnIvPg0KICAgIDxsaT48YSBvbkNsaWNrPSJjYWxsTHVhKCkiPueCueWHu+iwg+eUqGx1YeS7o+eggTwvYT48L2xpPg0KCTxkaXYgaWQ9ImNvbnRlbnQiPjwvZGl2Pg0KPC9ib2R5Pg0KPC9odG1sPg0K"
local text = decodeBase64(html)
print(text)
writeFile("/sdcard/test.html",text)
function onJsCallBack(arg)
	local ret = ui.callJs("webId","javascript:calljs(\"hello\")")
	print("onJsCallBack:",arg,ret)
end
ui.newLayout("layout1")
ui.addWebView("layout1","webId","file:///sdcard/test.html",-1,500)
ui.show("layout1")
sleep(100000)
```

## 15. ui.addTabView    创建标签页控件 (ui.addTabView)
**函数:** `ui.addTabView(layout,name,...)`  
**描述:** ui.addTabView    创建标签页控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| layout | string | 是 | 布局名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTabView("layout1","tabviewId1")
ui.addTab ("tabviewId1", "lab1", "子标签1")
ui.addTab ("tabviewId1", "lab2", "子标签2")
ui.show("layout1")
sleep(100000)
```

## 16. ui.addTab    创建子标签页控件 (ui.addTab)
**函数:** `ui.addTabView(addTabView,name)`  
**描述:** ui.addTab    创建子标签页控件

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| tabName | string | 是 | 父标签控件名称 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTabView("layout1","tabviewId1")
ui.addTab ("tabviewId1", "lab1", "子标签1")
ui.addTab ("tabviewId1", "lab2", "子标签2")
ui.addButton("lab1","btnnId1","按钮1")
ui.newRow("lab1","row1")
ui.addButton("lab1","btnnId2","按钮2")
ui.show("layout1")
sleep(100000)
```

## 17. ui.setLine    重设线控件 (ui.setLine)
**函数:** `ui.setLine(name,...)`  
**描述:** ui.setLine    重设线控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTabView("layout1","tabviewId1")
ui.addTab ("tabviewId1", "lab1", "子标签1")
ui.addTab ("tabviewId1", "lab2", "子标签2")
ui.show("layout1")
ui.addLine("lab1", "lineId1")
sleep(1000)
ui.setLine("lineId1",100,100)
sleep(100000)
```

## 18. ui.setButton    重设按钮控件 (ui.setButton )
**函数:** `ui.setButton(name,text,...)`  
**描述:** ui.setButton    重设按钮控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnnId1","按钮1")
ui.show("layout1")
sleep(1000)
ui.setButton("btnnId1","我爱中国",300,300)
sleep(100000)
```

## 19. ui.setEditText    重设输入框控件 (ui.setEditText)
**函数:** `ui.setEditText(name,text,...)`  
**描述:** ui.setEditText    重设输入框控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","我是输入框")
ui.show("layout1")
sleep(1000)
ui.setEditText("editId1","i love you china")
sleep(100000)
```

## 20. ui.setEditHintText   设置输入框默认提示字符串 (ui.setEditHintText)
**函数:** `ui.setEditHintText(name,hinttext)`  
**描述:** ui.setEditHintText   设置输入框默认提示字符串

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","")
ui.setEditHintText("editId1","这是提示内容")
ui.show("layout1")
sleep(100000)
```

## 21. ui.setTextView    重设文本框控件 (ui.setTextView)
**函数:** `ui.setTextView(name,text,...)`  
**描述:** ui.setTextView    重设文本框控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTextView("layout1","textId1","我是文本框")
ui.show("layout1")
sleep(1000)
ui.setTextView("textId1","i love you china")
sleep(100000)
```

## 22. ui.setCheckBox    重设多选框控件 (ui.setCheckBox)
**函数:** `ui.setCheckBox(name,text,sel,...)`  
**描述:** ui.setCheckBox    重设多选框控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addCheckBox("layout1","ckId1","选项1")
ui.show("layout1")
sleep(1000)
ui.setCheckBox("ckId1","我爱中国",true)
sleep(100000)
```

## 23. ui.setRadioGroup    重设单选框控件 (ui.setRadioGroup)
**函数:** `ui.setRadioGroup(name,list,select,...)`  
**描述:** ui.setRadioGroup    重设单选框控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addRadioGroup("layout1","rgId1",{"选项1","选项2","选项3"})
ui.show("layout1")
sleep(1000)
ui.setRadioGroup("rgId1",{"选项1","选项2","选项3"},1)
sleep(100000)
```

## 24. ui.setSpinner    重设下拉框控件 (ui.setSpinner)
**函数:** `ui.setSpinner(name,list,select,...)`  
**描述:** ui.setSpinner    重设下拉框控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addSpinner("layout1","spinId1",{"选项1","选项2","选项3"})
ui.show("layout1")
sleep(1000)
ui.setSpinner("spinId1",{"选项1","选项2","选项3"},1)
sleep(100000)
```

## 25. ui.setWebView    重设浏览器控件 (ui.setWebView)
**函数:** `ui.setWebView(name,url,...)`  
**描述:** ui.setWebView    重设浏览器控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addWebView("layout1","webId1","www.baidu.com")
ui.show("layout1")
sleep(1000)
ui.setWebView("webId1","www.lrappsoft.com")
sleep(100000)
```

## 26. ui.setImageView    重设图像控件 (ui.setImageView)
**函数:** `ui.setImageView(name,path,...)`  
**描述:** ui.setImageView    重设图像控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
local path = getSdPath().."/test.png"
snapShot(path)
ui.addImageView("layout1","imgId1",path)
ui.show("layout1")
sleep(3000)
print("更新图片内容")
local path1 = getSdPath().."/test1.png"
snapShot(path1)
ui.setImageView("imgId1",path1)
sleep(100000)
```

## 27. ui.setImageViewEx   重设图像控件 (ui.setImageViewEx)
**函数:** `ui.setImageViewEx(name,bmp,...)`  
**描述:** ui.setImageViewEx   重设图像控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
import('android.*')
import('java.lang.*')
import('java.util.*')
import('android.widget.*')
import('android.os.Build')
import('android.graphics.*');
import('com.nx.assist.lua.LuaEngine')

ui.newLayout("layout1")
ui.addImageView("layout1","imgId1","")
ui.show("layout1")
local bitmap = LuaEngine.snapShot(10,10,500,500)
ui.setImageViewEx("imgId1",bitmap)
sleep(100000)
```

## 28. ui.setText    控件设置文字 (ui.setText)
**函数:** `ui.setText(name,text)`  
**描述:** ui.setText    控件设置文字

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTextView("layout1","tvId1","文字框")
ui.newRow("layout1","row1")
ui.addButton("layout1","btnnId1","按钮1")
ui.show("layout1")
sleep(2000)
ui.setText("tvId1","我爱中国")
ui.setText("btnnId1","我爱中国")
sleep(100000)
```

## 29. ui.setTitleText   设置布局标题 (ui.setTitleText)
**函数:** `ui.setText(layout,text)`  
**描述:** ui.setTitleText   设置布局标题

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTextView("layout1","tvId1","文字框")
ui.newRow("layout1","row1")
ui.addButton("layout1","btnnId1","按钮1")
ui.show("layout1")
sleep(2000)
ui.setTitleText("layout1","我爱中国")
ui.setText("tvId1","我爱中国")
ui.setText("btnnId1","我爱中国")
sleep(100000)
```

## 30. ui.setTextSize   设置文字大小 (ui.setTextSize)
**函数:** `ui.setTextSize(layout,text)`  
**描述:** ui.setTextSize   设置文字大小

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addTextView("layout1","tvId1","文字框")
ui.show("layout1")
sleep(2000)
ui.setTextSize("tvId1",50)
sleep(100000)
```

## 31. ui.setEnable   设置控件可用状态 (ui.setEnable)
**函数:** `ui.setEnable(name,enable)`  
**描述:** ui.setEnable   设置控件可用状态

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.setEnable("btnId1",false)
ui.show("layout1")
sleep(100000)
```

## 32. ui.setVisiblity   设置控件显示状态  (ui.setVisiblity)
**函数:** `ui.setVisiblity(name,state)`  
**描述:** ui.setVisiblity   设置控件显示状态 

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
sleep(1000)
ui.setVisiblity("btnId1",2)
sleep(100000)
```

## 33. ui.setRowVisibleByGid   批量设置行控件显示状态通过gid (ui.setRowVisibleByGid)
**函数:** `ui.setRowVisibleByGid(layoutid,name,state)`  
**描述:** ui.setRowVisibleByGid   批量设置行控件显示状态通过gid

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.newRow("layout1","row1",-1,-2,"gid1")
ui.addButton("layout1","btnnId1","按钮1")
ui.newRow("layout1","row2",-1,-2,"gid1")
ui.addButton("layout1","btnnId2","按钮1")
ui.newRow("layout1","row2",-1,-2,"gid2")
ui.addButton("layout1","btnnId3","隐藏gid为gid1的布局")
ui.newRow("layout1","row4")
ui.addButton("layout1","btnnId4","显示gid为gid1的布局")
ui.show("layout1")
function onClick(isShow)
	if isShow then
		ui.setRowVisibleByGid("layout1","gid1",0)
	else
		ui.setRowVisibleByGid("layout1","gid1",8)
	end
end
ui.setOnClick("btnnId3","onClick(false)")
ui.setOnClick("btnnId4","onClick(true)")
sleep(1000000)
```

## 34. ui.setBackground   设置控件背景颜色 (ui.setBackground)
**函数:** `ui.setBackground(name,color)`  
**描述:** ui.setBackground   设置控件背景颜色

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
sleep(1000)
ui.setBackground("btnId1","#ffff00ff")
sleep(100000)
```

## 35. ui.setTitleBackground   设置标题栏背景颜色 (ui.setTitleBackground)
**函数:** `ui.setBackground(layout1,color)`  
**描述:** ui.setTitleBackground   设置标题栏背景颜色

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
sleep(1000)
ui.setTitleBackground("layout1","#ffff00ff")
sleep(100000)
```

## 36. ui.setTextColor    设置文字颜色 (ui.setTextColor)
**函数:** `ui.setTextColor(name,color)`  
**描述:** ui.setTextColor    设置文字颜色

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
sleep(1000)
ui.setTextColor("btnId1","#ffff00ff")
sleep(100000)
```

## 37. ui.setInputType   设置输入类型 (ui.setInputType)
**函数:** `ui.setInputType(name,type)`  
**描述:** ui.setInputType   设置输入类型

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","1")
ui.setInputType("editId1",2)
ui.show("layout1")
sleep(100000)
```

## 38. ui.getText   获取文字 (ui.getText)
**函数:** `ui.getText(name)`  
**描述:** ui.getText   获取文字

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
print(ui.getText("btnId1"))
sleep(100000)
```

## 39. ui.getEnable    获取可用状态 (ui.getEnable)
**函数:** `ui.getEnabled(name)`  
**描述:** ui.getEnable    获取可用状态

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
print(ui.getEnable("btnId1"))
sleep(100000)
```

## 40. ui.getVisible    获取显示状态 (ui.getVisible)
**函数:** `ui.getVisible(name)`  
**描述:** ui.getVisible    获取显示状态

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.show("layout1")
print(ui.getVisible("btnId1"))
ui.setVisiblity("btnId1",2)
print(ui.getVisible("btnId1"))
sleep(100000)
```

## 41. ui.getTextColor    获取文字颜色 (ui.getTextColor)
**函数:** `ui.getTextColor(name)`  
**描述:** ui.getTextColor    获取文字颜色

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnId1","我是按钮")
ui.setTextColor("btnId1","#ffff00ff")
ui.show("layout1")
print(ui.getTextColor("btnId1"))
sleep(100000)
```

## 42. ui.setFullScreen    设置控件宽度全屏 (ui.setFullScreen)
**函数:** `ui.setFullScreen(name)`  
**描述:** ui.setFullScreen    设置控件宽度全屏

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnnId1","按钮1",100,100)
ui.setTextColor("btnnId1","#ffff00ff")
ui.setBackground("btnnId1","#ffff0000")
ui.show("layout1")
sleep(1000)
print(ui.setFullScreen("btnnId1"))
sleep(100000)
```

## 43. ui.setPadding    设置控件内边距 (ui.setPadding)
**函数:** `ui.setPadding(name,l,t,r,b)`  
**描述:** ui.setPadding    设置控件内边距

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型 |

**示例:**
```lua
ui.newLayout("layout1")
ui.addButton("layout1","btnnId1","按钮1")
ui.show("layout1")
sleep(1000)
ui.setPadding("btnnId1",10,50,10,10)
sleep(100000)
```

## 44. ui.setGravity    设置控件对齐方式 (ui.setGravity)
**函数:** `ui.setGravity(name,alignMode)`  
**描述:** ui.setGravity    设置控件对齐方式

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1",-1)
ui.newRow("layout1","row0",-2,-2)
ui.addTextView("layout1","tvId1","控件对齐测试")
ui.newRow("layout1","row1",-2,-2)
ui.addButton("layout1","btn1","上对齐", 80, 50)
ui.addButton("layout1","btn2","下对齐", 80, 100)
ui.addButton("layout1","btn3","垂直居中对齐", 80, 140)

ui.newRow("layout1","row2")

ui.addButton("layout1","btn4","右边对齐")
ui.addButton("layout1","btn5","居中对齐")
ui.addButton("layout1","btn6","左边对齐")

ui.setBackground("row1","#ffff0000")

ui.show("layout1")

ui.setOnClick("btn1","上对齐()")
ui.setOnClick("btn2","下对齐()")
ui.setOnClick("btn3","垂直居中对齐()")


ui.setOnClick("btn4","右边对齐()")
ui.setOnClick("btn5","居中对齐()")
ui.setOnClick("btn6","左边对齐()")

function 上对齐()
ui.setGravity("btn1",80)
end

function 下对齐()
ui.setGravity("btn2",3)
end

function 垂直居中对齐()
ui.setGravity("btn2",16)
end
------------------------------------------
function 右边对齐()

ui.setGravity("row1",5)
end
function 左边对齐()
ui.setGravity("row1",3)
end
function 居中对齐()
ui.setGravity("row1",17)
end
sleep(100000)
```

## 45. ui.setOnClick    设置控件单击事件 (ui.setOnClick)
**函数:** `ui.setOnClick(name,event)`  
**描述:** ui.setOnClick    设置控件单击事件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	toast("按钮被点击了",0,0,30)
end

ui.newLayout("layout1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(100000)
```

## 46. ui.setOnBackEvent   设置窗口监听返回按键消息 (ui.setOnBackEvent)
**函数:** `ui.setOnBackEvent(name,event)`  
**描述:** ui.setOnBackEvent   设置窗口监听返回按键消息

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onBackEvent()
	toast("点击了返回",0,0,30)
end

ui.newLayout("layout1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.setOnBackEvent("layout1","onBackEvent()")
ui.show("layout1")
sleep(100000)
```

## 47. ui.setOnClose    设置窗口关闭事件 (ui.setOnClose)
**函数:** `ui.setOnClose(event)`  
**描述:** ui.setOnClose    设置窗口关闭事件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClose()
	toast("窗口关闭了",0,0,30)
end

ui.newLayout("layout1")
ui.setOnClose("layout1","onClose()")
ui.show("layout1")
sleep(100000)
```

## 48. ui.setOnChange    设置控件改变事件 (ui.setOnChange)
**函数:** `ui.setOnChange(name,event)`  
**描述:** ui.setOnChange    设置控件改变事件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	toast("按钮被点击了",0,0,30)
end

ui.newLayout("layout1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(100000)
```

## 49. ui.getValue  获取控件值 (ui.getValue)
**函数:** `ui.getValue(name)`  
**描述:** ui.getValue  获取控件值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型 |

**示例:**
```lua
function onClick()
	print(ui.getValue("ckId1"))
end

ui.newLayout("layout1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(100000)
```

## 50. ui.getData  获取当前界面所有控件的值 (ui.getData)
**函数:** `ui.getData()`  
**描述:** ui.getData  获取当前界面所有控件的值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 表格类型 |

**示例:**
```lua
function onClick()
	local ret = ui.getData()
	print(ret.ckId1)
end

ui.newLayout("layout1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(100000)
```

## 51. ui.loadProfile  读取设置 (ui.loadProfile)
**函数:** `ui.loadProfile(path)`  
**描述:** ui.loadProfile  读取设置

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	print(ui.getValue("ckId1"))
	ui.saveProfile("/sdcard/test.txt")
end

ui.newLayout("layout1")
ui.addEditText("layout1","editId1","中国牛逼")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(1000)
ui.loadProfile("/sdcard/test.txt")

sleep(100000)
```

## 52. ui.saveProfile  保存配置 (ui.saveProfile)
**函数:** `ui.saveProfile(path)`  
**描述:** ui.saveProfile  保存配置

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	print(ui.getValue("ckId1"))
	ui.saveProfile("/sdcard/test.txt")
end

ui.newLayout("layout1")
ui.addEditText("layout1","editId1","中国牛逼")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
sleep(1000)
ui.loadProfile("/sdcard/test.txt")

sleep(100000)
```

## 53. ui.beginUiQueue  创建一个快速ui命令队列 (ui.beginUiQueue)
**函数:** `ui.beginUiQueue(path)`  
**描述:** ui.beginUiQueue  创建一个快速ui命令队列

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	print(ui.getValue("ckId1"))
	ui.saveProfile("/sdcard/test.txt")
end
ui.beginUiQueue()
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","中国牛逼")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.newRow("layout1","row2")
ui.addButton("layout1","btn2","测试按钮2", 250, 50)
ui.newRow("layout1","row2")
ui.addButton("layout1","btn3","测试按钮3", 250, 50)
ui.newRow("layout1","row3")
ui.addButton("layout1","btn4","测试按钮4", 250, 50)
ui.newRow("layout1","row4")
ui.addButton("layout1","btn5","测试按钮5", 250, 50)
ui.newRow("layout1","row5")
ui.addButton("layout1","btn6","测试按钮6", 250, 50)
ui.newRow("layout1","row6")
ui.addButton("layout1","btn7","测试按钮7", 250, 50)
ui.newRow("layout1","row7")
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
ui.endUiQueue()
sleep(1000)
ui.loadProfile("/sdcard/test.txt")

sleep(100000)
```

## 54. ui.endUiQueue  执行这个ui命令队列 (ui.endUiQueue)
**函数:** `ui.endUiQueue(path)`  
**描述:** ui.endUiQueue  执行这个ui命令队列

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
function onClick()
	print(ui.getValue("ckId1"))
	ui.saveProfile("/sdcard/test.txt")
end
ui.beginUiQueue()
ui.newLayout("layout1")
ui.addEditText("layout1","editId1","中国牛逼")
ui.newRow("layout1","row1")
ui.addButton("layout1","btn1","点击我", 250, 50)
ui.newRow("layout1","row2")
ui.addButton("layout1","btn2","测试按钮2", 250, 50)
ui.newRow("layout1","row2")
ui.addButton("layout1","btn3","测试按钮3", 250, 50)
ui.newRow("layout1","row3")
ui.addButton("layout1","btn4","测试按钮4", 250, 50)
ui.newRow("layout1","row4")
ui.addButton("layout1","btn5","测试按钮5", 250, 50)
ui.newRow("layout1","row5")
ui.addButton("layout1","btn6","测试按钮6", 250, 50)
ui.newRow("layout1","row6")
ui.addButton("layout1","btn7","测试按钮7", 250, 50)
ui.newRow("layout1","row7")
ui.addCheckBox("layout1","ckId1","选项1")
ui.setOnClick("btn1","onClick()")
ui.show("layout1")
ui.endUiQueue()
sleep(1000)
ui.loadProfile("/sdcard/test.txt")

sleep(100000)
```

## 55. ui.addTableView    添加表格控件 (ui.addTableView)
**函数:** `ui.addTableView(layout, name, headers, data,...)`  
**描述:** ui.addTableView    添加表格控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1",-1,-2)
-- 创建简单表格
local headers = {"ID" , "名称" , "年龄"}
local userId = 4
local data = {
	{"1" , "李明" , "25"} ,
	{"2" , "萧红" , "30"} ,
	{"3" , "小咪" , "28"}
}

-- 创建固定尺寸的表格
ui.addTableView("layout1" , "tableview" , headers , data , 600 , 400)

local attrib = {
	width = -1 ,
	height = - 2 ,
	showheader = true ,
	headerbgcolor = 0x88000088 ,
	headertextcolor = 0xffffffff ,
	headertextsize = 13 ,
	rowbgcolor = 0xeeeeeeee ,
	rowselcolor = 0x553Ff2fd ,
	rowtextcolor = 0xee333333 ,
	rowtextsize = 13
}

function onAddRow()
	local item = {
		userId ,
		"李贺"..userId ,
		25
	}
	userId = userId + 1
	ui.addTableViewRow("tableview" , item)
	toast("添加行" , 0 , 0 , 20)
end

function onDelRow()
	local cnt = ui.getTableViewRowCnt("tableview")
	if cnt > 0 then
		ui.removeTableViewRow("tableview" , cnt - 1)
		toast("删除行" , 0 , 0 , 20)
	end
end

function onGetAllData()
	local ret = ui.getTableViewAllData("tableview")
	if ret ~= nil then
		local tb = jsonLib.decode(ret)
		print(tb)
	end
end

function onGetRowData()
	local selindex = ui.getTableViewSelectIndex("tableview")
	if selindex >= 0 then
		local ret = ui.getTableViewRowData("tableview" , selindex)
		if ret ~= nil then
			toast(ret,0,0,12)
			local tb = jsonLib.decode(ret)
			print(tb)
		end
	else
		toast("请先选中一行" , 0 , 0 , 20)
	end
end

function onTableViewEvent()
	onGetRowData()
end

ui.setTableViewAttrib("tableview" , attrib)
ui.newRow("layout1" , "row1")
ui.addButton("layout1" , "btnAddRow" , "添加行")
ui.addLine("layout1" , "line1" , 10 , - 2)
ui.addButton("layout1" , "btnDelRow" , "删除最后一行")

ui.newRow("layout1" , "row2")
ui.addButton("layout1" , "btnGetAllData" , "获取表全部数据")
ui.addLine("layout1" , "line2" , 10 , - 2)
ui.addButton("layout1" , "btnGetRowData" , "获取选中行数据")

ui.setOnClick("btnAddRow" , "onAddRow()")
ui.setOnClick("btnDelRow" , "onDelRow()")
ui.setOnClick("btnGetAllData" , "onGetAllData()")
ui.setOnClick("btnGetRowData" , "onGetRowData()")
ui.setOnChange("tableview","onTableViewEvent()")

ui.show("layout1")

sleep(1000000)
```

## 56. ui.setTableViewAttrib    设置表格属性 (ui.setTableViewAttrib)
**函数:** `ui.setTableViewAttrib(name, attribs)`  
**描述:** ui.setTableViewAttrib    设置表格属性

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| attribs: 属性表，包含以下可选字段 | string | 是 |  |
| headertextsize: 表头文字大小（单位 | string | 是 | sp） |
| rowtextsize: 行文字大小（单位 | string | 是 | sp） |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
-- 创建表格
ui.newLayout("layout1", -1, -2)
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, 400)

-- 设置表格属性
local attrib = {
    width = -1,               -- 宽度填满父容器
    height = -2,              -- 高度自适应内容
    showheader = true,        -- 显示表头
    headerbgcolor = 0x88000088, -- 表头背景色（半透明紫色）
    headertextcolor = 0xffffffff, -- 表头文字颜色（白色）
    headertextsize = 13,      -- 表头文字大小13sp
    rowbgcolor = 0xeeeeeeee,  -- 行背景色（浅灰色）
    rowselcolor = 0x553Ff2fd, -- 选中行背景色（半透明浅蓝色）
    rowtextcolor = 0xee333333, -- 行文字颜色（深灰色）
    rowtextsize = 13,         -- 行文字大小13sp
    rowheight = 50,           -- 行高50像素
}

ui.setTableViewAttrib("tableview", attrib)
ui.show("layout1")
sleep(100000)
```

## 57. ui.getTableViewAllData    获取表格全部数据 (ui.getTableViewAllData)
**函数:** `data = ui.getTableViewAllData(name)`  
**描述:** ui.getTableViewAllData    获取表格全部数据

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型（JSON格式的表格数据），失败返回nil
说明: 
  1. 返回包含整个表格数据的JSON字符串
  2. 数据结构为二维数组：[[行1数据], [行2数据], ...]
  3. 可使用jsonLib.decode()转换为Lua表
  4. 包含所有行数据，但不包含表头 |

**示例:**
```lua
-- 创建简单表格
ui.newLayout("layout1")
local headers = {"ID" , "名称" , "年龄"}
local data = {
	{"1" , "李明" , "25"} ,
	{"2" , "萧红" , "30"} ,
	{"3" , "小咪" , "28"}
}
ui.addTableView("layout1" , "tableview" , headers , data , 600 , 400)
ui.newRow("layout1" , "row1")
-- 添加按钮获取数据
ui.addButton("layout1" , "btnGetData" , "获取表格数据")
function getAllData()
	local jsonData = ui.getTableViewAllData("tableview")
	if jsonData then
		local tableData = jsonLib.decode(jsonData)
		print("表格数据:")
		for i , row in ipairs(tableData) do
			print(string.format("行%d: ID=%s, 名称=%s, 年龄=%s" ,
			i , row[1] , row[2] , row[3]))
		end
		toast("数据已打印到控制台" , 0 , 0 , 20)
	else
		toast("获取数据失败" , 0 , 0 , 20)
	end
end
ui.setOnClick("btnGetData" , "getAllData()")

ui.show("layout1")
sleep(1000000)
```

## 58. ui.getTableViewRowData    获取表格指定行数据 (ui.getTableViewRowData)
**函数:** `rowData = ui.getTableViewRowData(name, rowIndex)`  
**描述:** ui.getTableViewRowData    获取表格指定行数据

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型（JSON格式的行数据），失败返回nil
说明: 
  1. 返回单行数据的JSON字符串
  2. 数据结构为一维数组：["值1", "值2", ...]
  3. 可使用jsonLib.decode()转换为Lua表
  4. 行索引从0开始计数
  5. 如果行索引无效（超出范围），返回nil |

**示例:**
```lua
-- 创建简单表格
ui.newLayout("layout1")
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, 400)
ui.newRow("layout1","row1")
-- 添加按钮获取第二行数据
ui.addButton("layout1", "btnGetRow", "获取第二行数据")
ui.setOnClick("btnGetRow", [[
    -- 行索引从0开始，所以第二行索引为1
    local jsonData = ui.getTableViewRowData("tableview", 1)
    if jsonData then
        local rowData = jsonLib.decode(jsonData)
        toast("第二行数据: " .. table.concat(rowData, ", "), 0, 0, 20)
        print("行数据:", rowData[1], rowData[2], rowData[3])
    else
        toast("获取行数据失败", 0, 0, 20)
    end
]])

ui.show("layout1")
sleep(10000000)
```

## 59. ui.getTableViewRowData    获取表格指定行数据 (ui.getTableViewRowData)
**函数:** `rowData = ui.getTableViewRowData(name, rowIndex)`  
**描述:** ui.getTableViewRowData    获取表格指定行数据

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 字符串类型（JSON格式的行数据），失败返回nil
说明: 
  1. 返回单行数据的JSON字符串
  2. 数据结构为一维数组：["值1", "值2", ...]
  3. 可使用jsonLib.decode()转换为Lua表
  4. 行索引从0开始计数
  5. 如果行索引无效（超出范围），返回nil |

**示例:**
```lua
-- 创建简单表格
ui.newLayout("layout1")
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, 400)
ui.newRow("layout1","row1")
-- 添加按钮获取第二行数据
ui.addButton("layout1", "btnGetRow", "获取第二行数据")
ui.setOnClick("btnGetRow", [[
    -- 行索引从0开始，所以第二行索引为1
    local jsonData = ui.getTableViewRowData("tableview", 1)
    if jsonData then
        local rowData = jsonLib.decode(jsonData)
        toast("第二行数据: " .. table.concat(rowData, ", "), 0, 0, 20)
        print("行数据:", rowData[1], rowData[2], rowData[3])
    else
        toast("获取行数据失败", 0, 0, 20)
    end
]])

ui.show("layout1")
sleep(1000000)
```

## 60. ui.addTableViewRow    添加表格行 (ui.addTableViewRow)
**函数:** `ui.addTableViewRow(name, rowData)`  
**描述:** ui.addTableViewRow    添加表格行

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1", -1, -2)
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, -2)
ui.newRow("layout1","row1")
-- 添加按钮
ui.addButton("layout1", "btnAdd", "添加新行")

-- 新行计数器
local newId = 4

function onAddRow()
    -- 创建新行数据
    local newRow = {
        tostring(newId),
        "新用户"..newId,
        tostring(math.random(20, 40))
    }
    
    -- 添加行
    if ui.addTableViewRow("tableview", newRow) then
        toast("添加成功: ID "..newId, 0, 0, 20)
        newId = newId + 1
    else
        toast("添加失败", 0, 0, 20)
    end
end

ui.setOnClick("btnAdd", "onAddRow()")
ui.show("layout1")
sleep(1000000)
```

## 61. ui.removeTableViewRow   删除指定行 (ui.removeTableViewRow)
**函数:** `ui.removeTableViewRow(name, row)`  
**描述:** ui.removeTableViewRow   删除指定行

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
ui.newLayout("layout1" , - 1 , - 2)
local headers = {"ID" , "名称" , "年龄"}
local data = {
	{"1" , "李明" , "25"} ,
	{"2" , "萧红" , "30"} ,
	{"3" , "小咪" , "28"}
}
ui.addTableView("layout1" , "tableview" , headers , data , 600 , - 2)
ui.newRow("layout1" , "row1")
-- 添加按钮
ui.addButton("layout1" , "btnDel" , "删除第一行")

-- 新行计数器
local newId = 4

function onDelRow()
	local cnt = ui.getTableViewRowCnt("tableview")
	if cnt > 0 then
		if ui.removeTableViewRow("tableview" , 0) then
			toast("删除成功" , 0 , 0 , 20)
		else
			toast("添加失败" , 0 , 0 , 20)
		end
	end
end

ui.setOnClick("btnDel" , "onDelRow()")
ui.show("layout1")
sleep(1000000)
```

## 62. ui.getTableViewRowCnt   获取表格行数 (ui.getTableViewRowCnt)
**函数:** `ui.getTableViewRowCnt(name)`  
**描述:** ui.getTableViewRowCnt   获取表格行数

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 整数类型（返回表格当前数据行数，不含表头行；表格不存在返回-1）
注意事项:
  1. 该方法仅统计数据行数，不包含表头行
  2. 如果表格不存在或未初始化，将返回-1
  3. 行号从0开始计数（与removeTableViewRow等方法保持一致） |

**示例:**
```lua
ui.newLayout("layout1", -1, -2)
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, -2)

-- 获取行数示例
local rowCount = ui.getTableViewRowCnt("tableview")
toast("当前表格行数: "..rowCount, 0, 0, 20)  -- 显示"当前表格行数: 3"

-- 动态操作示例
function onAddRow()
    local newId = ui.getTableViewRowCnt("tableview") + 1
    ui.addTableViewRow("tableview", {tostring(newId), "新用户", "20"})
    toast("新增后行数: "..ui.getTableViewRowCnt("tableview"), 0, 0, 20)
end
ui.newRow("layout1","row1")
ui.addButton("layout1", "btnAdd", "添加行")
ui.setOnClick("btnAdd", "onAddRow()")
ui.show("layout1")
sleep(1000000)
```

## 63. ui.getTableViewSelectIndex   获取表格选中行索引 (ui.getTableViewSelectIndex)
**函数:** `ui.getTableViewSelectIndex(name)`  
**描述:** ui.getTableViewSelectIndex   获取表格选中行索引

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 整数类型
  - 返回当前选中行的索引（从0开始）
  - 无选中行时返回-1
  - 表格不存在时返回-2

注意事项:
  1. 行索引从0开始计数（与removeTableViewRow等方法保持一致）
  2. 返回值-1表示有效表格但无选中行
  3. 返回值-2表示表格不存在
  4. 通常与getTableViewRowData配合使用获取选中行数据 |

**示例:**
```lua
ui.newLayout("layout1", -1, -2)
local headers = {"ID", "名称", "年龄"}
local data = {
    {"1", "李明", "25"},
    {"2", "萧红", "30"},
    {"3", "小咪", "28"}
}
ui.addTableView("layout1", "tableview", headers, data, 600, -2)

-- 选中行操作示例
function onShowSelection()
    local selIndex = ui.getTableViewSelectIndex("tableview")
    if selIndex >= 0 then
        toast("当前选中第"..(selIndex+1).."行", 0, 0, 20)
    elseif selIndex == -1 then
        toast("请先点击选中某行", 0, 0, 20)
    else
        toast("表格不存在", 0, 0, 20)
    end
end

-- 获取选中行数据示例
function onGetSelectedData()
    local selIndex = ui.getTableViewSelectIndex("tableview")
    if selIndex >= 0 then
        local rowData = ui.getTableViewRowData("tableview", selIndex)
        toast("选中行数据: "..rowData, 0, 0, 15)
    end
end

ui.newRow("layout1", "row1")
ui.addButton("layout1", "btnShowSel", "显示选中行")
ui.addLine("layout1","line1",10,-2)
ui.addButton("layout1", "btnGetData", "获取选中数据")
ui.setOnClick("btnShowSel", "onShowSelection()")
ui.setOnClick("btnGetData", "onGetSelectedData()")
ui.show("layout1")
sleep(1000000)
```

