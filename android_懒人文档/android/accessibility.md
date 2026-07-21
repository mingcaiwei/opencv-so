# 无障碍相关方法

## 1. 检测无障碍服务是否开启 (`nodeLib.isAccServiceOk`)
**说明:** 检测无障碍服务是否开启了

**函数:** `nodeLib.isAccServiceOk()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 无障碍服务是否已开启 true/false |

示例:
```lua
local r = nodeLib.isAccServiceOk()
if r then
	print("无障碍服务已经开启")
else
	print("无障碍服务没有开启")
end
```

---

## 2. 打开截图服务 (`nodeLib.openSnapService`)
**说明:** 打开截图服务(这个方法一般用于手动模式，调用这方法会弹出允许截图窗口需要手动完成点击确认)

**函数:** `nodeLib.openSnapService()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 截图服务是否开启成功 true/false |

示例:
```lua
local r = nodeLib.openSnapService()
if r then
	if nodeLib.isAccServiceOk() == false then
		r = false
	end
end
if r then
	print("截图服务开启成功")
else
	print("截图服务开启失败")
end
```

---

## 3. 检测截图服务是否开启 (`nodeLib.isSnapServiceOk`)
**说明:** 检测截图服务是否开启(如果是root或者激活模式不需要用这个去检测，因为使用的截图方法不一样)

**函数:** `nodeLib.isSnapServiceOk()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 截图服务是否已开启 |

示例:
```lua
local r = nodeLib.isSnapServiceOk()
if r then
	print("截图服务已经开启")
else
	print("截图服务没有开启")
end
```

---

## 4. 获取指定节点的下一个兄弟节点 (`nodeLib.findNextNode`)
**说明:** 获取指定节点的下一个兄弟节点

**函数:** `nodeLib.findNextNode(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 满足要求的节点的下一个兄弟节点 |

示例:
```lua
local ret = nodeLib.findNextNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},true)
if ret ~= nil then
	print(ret)
end
```

---

## 5. 获取指定节点的上一个兄弟节点 (`nodeLib.findPreNode`)
**说明:** 获取指定节点的上一个兄弟节点

**函数:** `nodeLib.findPreNode(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 满足要求的节点的上一个兄弟节点 |

示例:
```lua
local ret = nodeLib.findPreNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
	print(ret)
end
```

---

## 6. 在指定节点中查找符合要求的子节点 (`nodeLib.findInNode`)
**说明:** 在指定节点中查找符合要求的子节点

**函数:** `nodeLib.findInNode(src, dst, isfindall, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| src | table | 是 | 要被查找的节点对象 |
| dst | table | 是 | 要查找的节点对象 |
| isfindall | boolean | 是 | 是否查找并返回所有符合要求的节点，true返回所有，false找到一个就返回 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 满足要求的节点或者节点数组 |

示例:
```lua
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.FrameLayout",id="com.nx.nxproj.assist:id/title"},true)
if ret ~= nil then
	local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
	print(ret)
	if r~= nil then
		for i=1,#r do
			print(r[i])
		end
	end
end
```

---

## 7. 查找出一个节点 (`nodeLib.findOne`)
**说明:** 查找出一个节点

**函数:** `nodeLib.findOne(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |


| 返回值类型 | 说明 |
|:---:|:---:|
| table | 满足要求的节点 |

示例:
```lua
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.RelativeLayout"},true)
if ret ~= nil then
	local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
	if r ~= nil then
		for i=1,#r do
			print(r[i])
		end
	end
end
```

---

## 8. 查找所有满足要求的节点 (`nodeLib.findAll`)
**说明:** 查找所有满足要求的节点

**函数:** `nodeLib.findAll(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 所有满足要求的节点 |

示例:
```lua
local ret = nodeLib.findAll({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
	print(ret)
end
```

---

## 9. 查找一个节点的所有子节点 (`nodeLib.findChildNodes`)
**说明:** 查找所有满足要求的节点的所有子节点

**函数:** `nodeLib.findChildNodes(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 所有满足要求的节点所有子节点 |

示例:
```lua
local ret = nodeLib.findChildNodes({class="android.widget.RelativeLayout",id="com.android.flysilkworm:id/main_banner_view"},false)
if ret ~= nil then
	for i = 1,#ret do
		print(ret[i])
	end
end
```

---

## 10. 查找出一个节点的父节点 (`nodeLib.findParentNode`)
**说明:** 查找出一个节点的父节点

**函数:** `nodeLib.findParentNode(selector, fuzzy_match)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| selector | table | 是 | 节点选择器，里面的键值对通过节点工具勾选直接生成 |
| fuzzy_match | boolean | 是 | true表示使用正则匹配去查询，false表示完全匹配 |


| 返回值类型 | 说明 |
|:---:|:---:|
| table | 满足要求的节点的父节点 |

示例:
```lua
local ret = nodeLib.findParentNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
	print(ret)
end
```

---

## 11. 根据节点所在树的每个分支顺序查找 (`nodeLib.findByIndex`)
**说明:** 根据节点所在树的每个分支顺序查找

**函数:** `nodeLib.findByIndex(indexs)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| indexs | string | 是 | 从顶层节点到该节点顺序字符串 |

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 所有满足要求的节点 |

示例:
```lua
local ret = nodeLib.findByIndex("0|1|2")
if ret ~= nil then
	print(ret)
end
```

---

## 12. 锁定当前界面到内存 (`nodeLib.keepNode`)
**说明:** 锁定当前界面到内存，下次节点查找查找都会直接从内存中获取该节点

**函数:** `nodeLib.keepNode()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 成功返回true，失败返回false |

示例:
```lua
nodeLib.keepNode()
local search_edit = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local input_edit = {class="android.widget.EditText",id="com.android.launcher3:id/input_edit"}
local ret1 = nodeLib.findOne(search_edit,true)
local ret2 = nodeLib.findOne(input_edit,true)
if ret1 ~= nil and ret2 ~= nil then
	nodeLib.setText(input_edit,"abc")
end
nodeLib.releaseNode()
```

---

## 13. 释放锁定在内存中的节点信息 (`nodeLib.releaseNode`)
**说明:** 这个方法是配合旧版节点函数使用注意和unlockNode(新版的节点函数)区别开了

**函数:** `nodeLib.releaseNode()`

参数: 无

返回值: 无

示例:
```lua
nodeLib.keepNode()
local search_edit = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local input_edit = {class="android.widget.EditText",id="com.android.launcher3:id/input_edit"}
local ret1 = nodeLib.findOne(search_edit,true)
local ret2 = nodeLib.findOne(input_edit,true)
if ret1 ~= nil and ret2 ~= nil then
	nodeLib.setText(input_edit,"abc")
end
nodeLib.releaseNode()
```

---

## 14. 给文本输入框节点输入文字 (`nodeLib.setText`)
**说明:** 给文本输入框节点输入文字

**函数:** `nodeLib.setText(node, text)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| node | table | 是 | 节点表格 |
| text | string | 是 | 要输入的文本字符串 |


| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功设置文本 true/false |

示例:
```lua
local node = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local ret = nodeLib.findOne(node,true)
if ret ~= nil then
	nodeLib.setText(ret,"abc")
end
```

---

## 15. 点击节点 (`nodeLib.click`)
**说明:** 点击指定节点

**函数:** `nodeLib.click(node, mode)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| node | table | 是 | 节点表格 |
| mode | boolean | 否 | true表示节点点击(需要节点可点击)，false表示模拟触摸式点击，默认为false |

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功点击 true/false |

示例:
```lua
local ret = nodeLib.findByIndex("0|1|2")
if ret ~= nil then
	nodeLib.click(ret)
end
```

---

## 16. 设置获取节点模式 (`nodeLib.setNodeMode`)
**说明:** 设置获取节点模式

**函数:** `nodeLib.setNodeMode(mode, enableGetInVisibleNode)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| mode | integer | 是 | 0表示获取所有节点，1表示获取节点模式为简单模式(不重要的节点将被过滤) |
| enableGetInVisibleNode | boolean | 是 | 抓取节点的时候是否获取不可见的节点 |


| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功设置 true/false |

示例:
```lua
nodeLib.setNodeMode(1,false)
```

---

## 17. 刷新节点 (`nodeLib.updateNode`)
**说明:** 刷新节点

**函数:** `nodeLib.updateNode()`

参数: 无

返回值: 无

示例:
```lua
nodeLib.updateNode()
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.RelativeLayout"},true)
if ret ~= nil then
	local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
	if r ~= nil then
		for i=1,#r do
			print(r[i])
		end
	end
end
```

---

## 18. 实例化一个Path路径对象 (`Path.new`)
**说明:** 实例化一个Path路径对象

**函数:** `Path:new()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| Path | Path对象 |

示例:
```lua
local path = Path:new() --创建一个轨迹路径
```

---

## 19. 设置滑动的起始时间 (`Path.setStartTime`)
**说明:** 设置滑动的起始时间

**函数:** `path:setStartTime(time)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| time | integer | 是 | 从触发事件的多少毫秒后开始滑动 |

返回值: 无

示例:
```lua
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
```

---

## 20. 设置滑动持续的时间 (`Path.setDurTime`)
**说明:** 设置滑动持续的时间

**函数:** `path:setDurTime(time)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| time | integer | 是 | 滑动的时间（毫秒） |

返回值: 无

示例:
```lua
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
```

---

## 21. 添加路径经过的滑动点坐标 (`Path.addPoint`)
**说明:** 添加路径经过的滑动点坐标

**函数:** `path:addPoint(x, y)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | integer | 是 | X坐标 |
| y | integer | 是 | Y坐标 |

返回值: 无

示例:
```lua
--从A点滑动到B点的例子
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
```

---

## 22. 创建一个手势滑动对象 (`Gesture.new`)
**说明:** 创建一个手势滑动对象

**函数:** `Gesture:new()`

参数: 无

| 返回值类型 | 说明 |
|:---:|:---:|
| Gesture | 手势滑动对象 |

示例:
```lua
local gesture = Gesture:new() --创建一个手势滑动对象
```

---

## 23. 添加一个滑动路径 (`Gesture.addPath`)
**说明:** 添加一个滑动路径

**函数:** `gesture:addPath(path)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | Path | 是 | 路径对象 |

返回值: 无

示例:
```lua
local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
```

---

## 24. 开始执行手势操作 (`Gesture.dispatch`)
**说明:** 开始执行手势操作

**函数:** `gesture:dispatch(callback)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| callback | function | 否 | 执行结果回调函数，type为0执行完成，为1是执行中途被取消。如果不写则会阻塞等待执行完成返回结果 |

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 如果为false则执行失败 |

示例:
```lua
nodeLib.openAccessibility()
local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
local r = gesture:dispatch()
if r then
	print("执行成功")
else
	print("执行失败")
end

local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
function onFinishEvent(type) --执行结果回调函数 type为0执行完成，为1是执行中途被取消
	if type == 1 then
		print("执行成功")
	else
		print("执行失败")
	end
end

local r = gesture:dispatch(onFinishEvent)
if r then
	print("任务已被发送")
else
	print("执行失败")
end
sleep(10000)
```
