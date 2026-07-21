# 节点方法 (node)

## 1. id 根据节点的id属性匹配 (id)
**函数:** `id(str)`  
**描述:** id 根据节点的id属性匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的具体控件的id |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = id("com.nx.nxprojit:id/detail_tv_title")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 2. idContains 根据id包含的部分字符串匹配 (idContains)
**函数:** `idContains(str)`  
**描述:** idContains 根据id包含的部分字符串匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的模糊的包含id某一段字符串的内容 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = idContains("detail_tv_title")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 3. idStartsWith 根据id的前缀去匹配 (idStartsWith)
**函数:** `idStartsWith(str)`  
**描述:** idStartsWith 根据id的前缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的id的前缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = idStartsWith("com.nx.nxprojit")
local node = sel:findOne(10000)
if node~= nil then
	print(node:id())
end
```

## 4. idEndsWith 根据id的后缀去匹配 (idEndsWith)
**函数:** `idEndsWith(str)`  
**描述:** idEndsWith 根据id的后缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的id的后缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = idEndsWith("detail_tv_title")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 5. idMatches 正则匹配id (idMatches)
**函数:** `idMatches(str)`  
**描述:** idMatches 正则匹配id

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = idMatches(".*detail_tv_title$")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 6. text 根据节点的text属性匹配 (text)
**函数:** `text(str)`  
**描述:** text 根据节点的text属性匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的具体控件的text |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = text("懒人高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 7. textContains 根据text包含的部分字符串匹配 (textContains)
**函数:** `textContains(str)`  
**描述:** textContains 根据text包含的部分字符串匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的模糊的包含text某一段字符串的内容 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = textContains("懒人")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 8. textStartsWith 根据text的前缀去匹配 (textStartsWith)
**函数:** `textStartsWith(str)`  
**描述:** textStartsWith 根据text的前缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的text的前缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = textStartsWith("懒人")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 9. textEndsWith 根据text的后缀去匹配 (textEndsWith)
**函数:** `textEndsWith(str)`  
**描述:** textEndsWith 根据text的后缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的text的后缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = textEndsWith("高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 10. textMatches 正则匹配text (textMatches)
**函数:** `textMatches(str)`  
**描述:** textMatches 正则匹配text

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = textMatches(".*高级版$")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 11. desc 根据节点的desc属性匹配 (desc)
**函数:** `desc(str)`  
**描述:** desc 根据节点的desc属性匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的具体控件的desc |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = desc("懒人高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 12. descContains 根据desc包含的部分字符串匹配 (descContains)
**函数:** `descContains(str)`  
**描述:** descContains 根据desc包含的部分字符串匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的模糊的包含desc某一段字符串的内容 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = descContains("懒人")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 13. descStartsWith 根据text的前缀去匹配 (descStartsWith)
**函数:** `descStartsWith(str)`  
**描述:** descStartsWith 根据text的前缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的desc的前缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = descStartsWith("懒人")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 14. descEndsWith 根据text的后缀去匹配 (descEndsWith)
**函数:** `descEndsWith(str)`  
**描述:** descEndsWith 根据text的后缀去匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的desc的后缀 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = descEndsWith("高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 15. descMatches 正则匹配text (descMatches)
**函数:** `descMatches(str)`  
**描述:** descMatches 正则匹配text

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = descMatches(".*高级版$")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 16. className 根据节点的className属性匹配 (className)
**函数:** `className(str)`  
**描述:** className 根据节点的className属性匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找的具体控件的类名 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 17. classNameContains 根据className属性所包含的字符串模糊匹配 (classNameContains)
**函数:** `classNameContains(str)`  
**描述:** classNameContains 根据className属性所包含的字符串模糊匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找className包含该字符的节点 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = classNameContains("android.widget")
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 18. classNameStartsWith 根据className属性前缀匹配 (classNameStartsWith)
**函数:** `classNameStartsWith(str)`  
**描述:** classNameStartsWith 根据className属性前缀匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找className前缀为该字符的节点 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = classNameStartsWith("android.widget")
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 19. classNameEndsWith 根据className属性后缀匹配 (classNameEndsWith)
**函数:** `classNameEndsWith(str)`  
**描述:** classNameEndsWith 根据className属性后缀匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要查找className后缀为该字符的节点 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = classNameEndsWith("TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 20. classNameMatches 根据className属性正则匹配 (classNameMatches)
**函数:** `classNameMatches(str)`  
**描述:** classNameMatches 根据className属性正则匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要匹配className的正则表达式 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = classNameMatches("^android.*TextView$")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 21. packageName 根据packageName属性全字段匹配 (packageName)
**函数:** `packageName(str)`  
**描述:** packageName 根据packageName属性全字段匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，指定要匹配节点所属的包名 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = packageName("com.nx.nxprojit"):className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 22. packageNameContains 匹配包含指定字符串的的节点 (packageNameContains)
**函数:** `packageNameContains(str)`  
**描述:** packageNameContains 匹配包含指定字符串的的节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，包含该字符串的包名的节点将被匹配到 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = packageNameContains("nxprojit"):className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 23. packageNameStartsWith 匹配包名前缀为指定字符串的的节点 (packageNameStartsWith)
**函数:** `packageNameStartsWith(str)`  
**描述:** packageNameStartsWith 匹配包名前缀为指定字符串的的节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，包名为该字符的前缀的节点将被匹配到 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = packageNameStartsWith("com.nx"):className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 24. packageNameEndsWith 匹配包名后缀为指定字符串的的节点 (packageNameEndsWith)
**函数:** `packageNameEndsWith(str)`  
**描述:** packageNameEndsWith 匹配包名后缀为指定字符串的的节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，包名为该字符的后缀的节点将被匹配到 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = packageNameEndsWith("nx.nxprojit"):className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 25. packageNameMatches 包名正则匹配 (packageNameMatches)
**函数:** `packageNameMatches(str)`  
**描述:** packageNameMatches 包名正则匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| str | string | 是 | str 字符串类型，根据这个正则字符串匹配所有符合规则包名的节点 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = packageNameMatches("com.nx.*"):className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 26. bounds 根据节点的范围匹配 (bounds)
**函数:** `bounds(l,t,r,b)`  
**描述:** bounds 根据节点的范围匹配

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| l | number | 是 | 左范围 |
| t | number | 是 | 上范围 |
| r | number | 是 | 右范围 |
| b | number | 是 | 下范围 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = bounds(30,212,236,250)
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 27. boundsInside 匹配该范围内的节点 (boundsInside)
**函数:** `boundsInside(l,t,r,b)`  
**描述:** boundsInside 匹配该范围内的节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| l | number | 是 | 左范围 |
| t | number | 是 | 上范围 |
| r | number | 是 | 右范围 |
| b | number | 是 | 下范围 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = boundsInside(30,212,236,250)
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 28. drawingOrder 根据绘制顺序匹配 (drawingOrder)
**函数:** `drawingOrder(level)`  
**描述:** drawingOrder 根据绘制顺序匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = drawingOrder(1)
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 29. depth 根据深度索引匹配 (depth)
**函数:** `depth(level)`  
**描述:** depth 根据深度索引匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = depth(1)
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 30. index 根据在当前父节点里面的索引顺序查找 (index)
**函数:** `index(level)`  
**描述:** index 根据在当前父节点里面的索引顺序查找

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = index(1)
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 31. visibleToUser 根据是否可见匹配 (visibleToUser)
**函数:** `visibleToUser(b)`  
**描述:** visibleToUser 根据是否可见匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = visibleToUser(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 32. selected 根据是否选中匹配 (selected)
**函数:** `selected(b)`  
**描述:** selected 根据是否选中匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = selected(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 33. clickable 根据是否可点击匹配 (clickable)
**函数:** `clickable(b)`  
**描述:** clickable 根据是否可点击匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = clickable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 34. longClickable 根据是否可长按点击匹配 (longClickable)
**函数:** `longClickable(b)`  
**描述:** longClickable 根据是否可长按点击匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = longClickable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 35. enabled 根据是否可用匹配 (enabled)
**函数:** `enabled(b)`  
**描述:** enabled 根据是否可用匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = enabled(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 36. password 根据是否是密码框匹配 (password)
**函数:** `password(b)`  
**描述:** password 根据是否是密码框匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = password(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 37. scrollable 根据是否可以滚动来匹配 (scrollable)
**函数:** `scrollable(b)`  
**描述:** scrollable 根据是否可以滚动来匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 38. checked 是否被勾选来匹配 (checked)
**函数:** `checked(b)`  
**描述:** checked 是否被勾选来匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = checked(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 39. checkable 是否可以被勾选来匹配 (checkable)
**函数:** `checkable(b)`  
**描述:** checkable 是否可以被勾选来匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = checkable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 40. focusable 根据是否允许抢占焦点来匹配 (focusable)
**函数:** `focusable(b)`  
**描述:** focusable 根据是否允许抢占焦点来匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = focusable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 41. focused 根据是否抢占了焦点来匹配 (focused)
**函数:** `focused(b)`  
**描述:** focused 根据是否抢占了焦点来匹配

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| selector | 返回一个选择器对象，该对象支持级联选择 |

**示例:**
```lua
local sel = focused(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:className())
end
```

## 42. findOne 获取匹配到的第一个节点 (sel:findOne)
**函数:** `sel:findOne(...)`  
**描述:** findOne 获取匹配到的第一个节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| timeout | number | 否 | 匹配超时时间（毫秒） |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| node | 返回匹配到的节点对象 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
```

## 43. findAll 获取匹配到的所有节点 (sel:findAll)
**函数:** `sel:findAll(...)`  
**描述:** findAll 获取匹配到的所有节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| timeout | number | 否 | 匹配超时时间（毫秒） |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| node | 返回匹配到的节点对象 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findAll(10000)
if node~= nil then
for i=1,#node do
	print(node[i]:text())
end
end
```

## 44. findOnce 根据索引获取匹配到的节点 (sel:findOnce)
**函数:** `sel:findOnce(...)`  
**描述:** findOnce 根据索引获取匹配到的节点

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| index | number | 否 | 节点索引 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| node | 返回匹配到的节点对象 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOnce(1) --匹配查找到的第二个节点
if node~= nil then
	print(node:text())
end
```

## 45. click 点击所有匹配到的节点 (sel:click)
**函数:** `sel:click()`  
**描述:** click 点击所有匹配到的节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.TextView"):text("雷电游戏中心")
sel:click()
```

## 46. sel:longClick 长按点击所有匹配到的节点 (sel:longClick)
**函数:** `sel:longClick()`  
**描述:** sel:longClick 长按点击所有匹配到的节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.TextView"):text("雷电游戏中心")
sel:longClick()
```

## 47. node:id 获取节点的id属性值 (node:id)
**函数:** `node:id()`  
**描述:** node:id 获取节点的id属性值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回id |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:id())
end
```

## 48. node:toJson 获取节点的所有属性以json字符串的形式 (node:toJson)
**函数:** `node:toJson()`  
**描述:** node:toJson 获取节点的所有属性以json字符串的形式

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回json字符串 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:toJson())
end
```

## 49. node:text 获取节点的text属性值 (node:text)
**函数:** `node:text()`  
**描述:** node:text 获取节点的text属性值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回text |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:text())
end
```

## 50. node:desc 获取节点的desc属性值 (node:desc)
**函数:** `node:desc()`  
**描述:** node:desc 获取节点的desc属性值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回desc |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:desc())
end
```

## 51. node:className 获取节点的className属性值 (node:className)
**函数:** `node:className()`  
**描述:** node:className 获取节点的className属性值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回className |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:className())
end
```

## 52. node:packageName 获取节点的className属性值 (node:packageName)
**函数:** `node:packageName()`  
**描述:** node:packageName 获取节点的className属性值

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回packageName |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:packageName())
end
```

## 53. node:bounds 获取当前节点的范围信息 (node:bounds)
**函数:** `node:bounds()`  
**描述:** node:bounds 获取当前节点的范围信息

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number[] | 返回4个整数，依次是左范围，上范围，右范围，下范围 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:bounds())
end
```

## 54. node:boundsInParent 获取当前节点相对父节点中的范围信息 (node:boundsInParent)
**函数:** `node:boundsInParent()`  
**描述:** node:boundsInParent 获取当前节点相对父节点中的范围信息

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| number[] | 返回4个整数，依次是左范围，上范围，右范围，下范围 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node ~= nil then
	print(node:boundsInParent())
end
```

## 55. node:childCount 获取当前节点的子节点个数 (node:childCount)
**函数:** `node:childCount()`  
**描述:** node:childCount 获取当前节点的子节点个数

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any |  |

**示例:**
```lua
local sel = className("android.widget.LinearLayout")
local node = sel:findOne(10000)
if node~= nil then
	print(node:childCount())
end
```

## 56. node:childs 获取当前节点下的所有子节点 (node:childs)
**函数:** `node:childs()`  
**描述:** node:childs 获取当前节点下的所有子节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any |  |

**示例:**
```lua
local sel = bounds(0,36,540,960)
local node = sel:findOne(10000)
if node~= nil then
	local arr = node:childs()
	local cnt = node:childCount()
	print(cnt)
	for i=1,#arr do
		print(arr[i]:className())
	end
end
```

## 57. node:parent 获取父节点 (node:parent)
**函数:** `node:parent()`  
**描述:** node:parent 获取父节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any |  |

**示例:**
```lua
local sel=index(1):text("192.168.1.3"):desc("")
local node = sel:findOne(10000)
if node~= nil then
	local p = node:parent()
	print(p:bounds())
end
```

## 58. node:drawingOrder 获取当前节点的绘制顺序的索引 (node:drawingOrder)
**函数:** `node:drawingOrder()`  
**描述:** node:drawingOrder 获取当前节点的绘制顺序的索引

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 返回当前节点的绘制顺序的索引 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:drawingOrder())
end
```

## 59. node:depth 获取当前节点深度索引 (node:depth)
**函数:** `node:depth()`  
**描述:** node:depth 获取当前节点深度索引

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 返回当前节点的绘制顺序的索引 |

**示例:**
```lua
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:depth())
end
```

## 60. node:setText 设置当前节点控件显示的的文本内容 (node:setText)
**函数:** `node:setText()`  
**描述:** node:setText 设置当前节点控件显示的的文本内容

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:setText("hello"))
end
```

## 61. node:scrollTo 滚动滚动条控件到指定位置 (node:scrollTo)
**函数:** `node:scrollTo()`  
**描述:** node:scrollTo 滚动滚动条控件到指定位置

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollTo(100,0))
end
```

## 62. node:scrollUp  向上滚动 (node:scrollUp)
**函数:** `node:scrollUp()`  
**描述:** node:scrollUp  向上滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollUp())
end
```

## 63. node:scrollDown 向下滚动 (node:scrollDown)
**函数:** `node:scrollDown()`  
**描述:** node:scrollDown 向下滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollDown())
end
```

## 64. node:scrollLeft 向左滚动 (node:scrollLeft)
**函数:** `node:scrollLeft()`  
**描述:** node:scrollLeft 向左滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollLeft())
end
```

## 65. node:scrollRight 向右滚动 (node:scrollRight)
**函数:** `node:scrollRight()`  
**描述:** node:scrollRight 向右滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollRight())
end
```

## 66. node:scrollForward 向前滚动 (node:scrollForward)
**函数:** `node:scrollForward()`  
**描述:** node:scrollForward 向前滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollForward())
end
```

## 67. node:scrollBackward 向后滚动 (node:scrollBackward)
**函数:** `node:scrollBackward()`  
**描述:** node:scrollBackward 向后滚动

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = scrollable(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:scrollBackward())
end
```

## 68. node:click 点击当前节点 (node:click)
**函数:** `node:click()`  
**描述:** node:click 点击当前节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = text("懒人高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:click())
end
```

## 69. node:longClick 长按当前节点 (node:longClick)
**函数:** `node:longClick()`  
**描述:** node:longClick 长按当前节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = text("懒人高级版")
local node = sel:findOne(10000)
if node~= nil then
	print(node:longClick())
end
```

## 70. node:focus 抢占焦点 (node:focus)
**函数:** `node:focus()`  
**描述:** node:focus 抢占焦点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:focus())
end
```

## 71. node:clearFocus 清占焦点 (node:clearFocus)
**函数:** `node:clearFocus()`  
**描述:** node:clearFocus 清占焦点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:clearFocus())
end
```

## 72. node:copy 获取当前节点输入框的文本到剪贴板 (node:copy)
**函数:** `node:copy()`  
**描述:** node:copy 获取当前节点输入框的文本到剪贴板

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:copy())
end
```

## 73. node:paste 粘贴剪贴板里面的内容到节点的输入框 (node:paste)
**函数:** `node:paste()`  
**描述:** node:paste 粘贴剪贴板里面的内容到节点的输入框

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:paste())
end
```

## 74. node:cut 剪切输入框选中的内容 (node:cut)
**函数:** `node:cut()`  
**描述:** node:cut 剪切输入框选中的内容

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:cut())
end
```

## 75. node:select 选择选项、标记复选框、选择单选按钮、选择列表项等操作 (node:select)
**函数:** `node:select()`  
**描述:** node:select 选择选项、标记复选框、选择单选按钮、选择列表项等操作

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = selected(true)
local node = sel:findOne(10000)
if node~= nil then
	print(node:select())
end
```

## 76. node:setSelection 设置文本输入框或可编辑文本区域中选定文本 (node:setSelection)
**函数:** `node:setSelection(start,end)`  
**描述:** node:setSelection 设置文本输入框或可编辑文本区域中选定文本

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.EditText")
local node = sel:findOne(10000)
if node~= nil then
	print(node:setSelection(1,3))
end
```

## 77. node:setProgress 设置节点所在控件的进度条的进度 (node:setProgress)
**函数:** `node:setProgress(pos)`  
**描述:** node:setProgress 设置节点所在控件的进度条的进度

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.ProgressBar")
local node = sel:findOne(10000)
if node~= nil then
	print(node:setProgress(1.0))
end
```

## 78. node:collapse 折叠控件 (node:collapse)
**函数:** `node:collapse()`  
**描述:** node:collapse 折叠控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.ListView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:collapse())
end
```

## 79. node:expand 展开折叠的控件 (node:expand)
**函数:** `node:expand()`  
**描述:** node:expand 展开折叠的控件

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.ListView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:expand())
end
```

## 80. node:contextClick 右键点击节点 (node:contextClick)
**函数:** `node:contextClick()`  
**描述:** node:contextClick 右键点击节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local sel = className("android.widget.ListView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:contextClick())
end
```

## 81. nodeLib.getNodeXml 导出节点xml信息 (nodeLib.getNodeXml)
**函数:** `nodeLib.getNodeXml()`  
**描述:** nodeLib.getNodeXml 导出节点xml信息

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | 返回xml字符串 |

**示例:**
```lua
local xml = nodeLib.getNodeXml()
if xml~= nil then
	print(xml)
end
```

## 82. nodeLib.saveNode 导出当前界面节点数据(1.4.8版本及之前的) (nodeLib.saveNode)
**函数:** `nodeLib.saveNode(path)`  
**描述:** nodeLib.saveNode 导出当前界面节点数据(1.4.8版本及之前的)

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local r = nodeLib.saveNode("/sdcard/test.node")
print(r)
```

## 83. nodeLib.saveNodeNew 导出当前界面节点数据(1.5及以后的版本) (nodeLib.saveNodeNew)
**函数:** `nodeLib.saveNodeNew(path)`  
**描述:** nodeLib.saveNodeNew 导出当前界面节点数据(1.5及以后的版本)

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
local r = nodeLib.saveNodeNew("/sdcard/test.node")
print(r)
```

## 84. nodeLib.lockNode 锁定节点到内存 (nodeLib.lockNode)
**函数:** `nodeLib.lockNode()`  
**描述:** nodeLib.lockNode 锁定节点到内存

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
nodeLib.lockNode()
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end

sel = className("android.widget.TextView")
node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
nodeLib.unlockNode()
```

## 85. nodeLib.lockNode 解锁之前锁定在内存中的节点 (nodeLib.unlockNode)
**函数:** `nodeLib.unlockNode()`  
**描述:** nodeLib.lockNode 解锁之前锁定在内存中的节点

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
nodeLib.lockNode()
local sel = className("android.widget.TextView")
local node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end

sel = className("android.widget.TextView")
node = sel:findOne(10000)
if node~= nil then
	print(node:text())
end
nodeLib.unlockNode()
```

## 86. nodeLib.openAccessibility 自动打开无障碍服务 (nodeLib.openAccessibility)
**函数:** `nodeLib.openAccessibility()`  
**描述:** nodeLib.openAccessibility 自动打开无障碍服务

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
nodeLib.openAccessibility()
```

## 87. nodeLib.closeAccessibility 自动关闭无障碍服务 (nodeLib.closeAccessibility)
**函数:** `nodeLib.closeAccessibility()`  
**描述:** nodeLib.closeAccessibility 自动关闭无障碍服务

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
nodeLib.closeAccessibility()
```
