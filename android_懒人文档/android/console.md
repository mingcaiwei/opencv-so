# 控制台方法 (console)

## 1. console.show 显示控制台悬浮窗 (console.show)
**函数:** `console.show(...)`  
**描述:** console.show 显示控制台悬浮窗

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
console.show()
console.setPos(100,100)
```

## 2. console.showTitle 显示或者隐藏控制台标题栏 (console.showTitle)
**函数:** `console.showTitle(...)`  
**描述:** console.showTitle 显示或者隐藏控制台标题栏

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
console.show()
console.showTitle(false)
console.setPos(100,100)
```

## 3. console.lockConsole 锁定控制台窗口 (console.lockConsole)
**函数:** `console.lockConsole()`  
**描述:** console.lockConsole 锁定控制台窗口

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any |  |

**示例:**
```lua
console.show()
console.lockConsole()
```

## 4. console.unlockConsole 解除锁定控制台窗口 (console.unlockConsole)
**函数:** `console.unlockConsole()`  
**描述:** console.unlockConsole 解除锁定控制台窗口

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any |  |

**示例:**
```lua
console.show()
console.setPos(100,100)
console.lockConsole()
setStopCallBack(function(error)
	console.unlockConsole()
end)
local tick = 1
while true do
	console.println(2,"tick=>"..tick)
	tick = tick + 1
	sleep(1000)
end
```

## 5. console.dismiss 关闭控制台窗口 (console.dismiss)
**函数:** `console.dismiss()`  
**描述:** console.dismiss 关闭控制台窗口

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| boolean | true表示成功，false表示失败 |

**示例:**
```lua
console.show()
console.setPos(100,100)
for i=1,100 do
	console.println(3," 日志任务开始:"..i)
	sleep(500)
end

console.dismiss()
```

## 6. console.setPos  设置控制台窗口的位置和大小 (console.setPos)
**函数:** `console.setPos(x,y,...)`  
**描述:** console.setPos 设置控制台窗口的位置和大小

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 无 |

**示例:**
```lua
console.show()
console.setPos(100,100)
for i=1,100 do
	console.println(3," 日志任务开始:"..i)
	sleep(500)
end
console.dismiss()
```

## 7. console.println 打印日志到控制台窗口 (console.println)
**函数:** `console.println(level,log)`  
**描述:** console.println 打印日志到控制台窗口

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| level | number | 是 | 级别参数 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 无 |

**示例:**
```lua
console.show()
console.setPos(100,100)
for i=1,100 do
	console.println(3," 日志任务开始:"..i)
	sleep(500)
end

console.dismiss()
```

## 8. console.clearLog 清除日志 (console.clearLog)
**函数:** `console.clearLog()`  
**描述:** console.clearLog 清除日志

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 无 |

**示例:**
```lua
console.show()
console.clearLog()
console.setPos(100,100)
for i=1,100 do
	console.println(3," 日志任务开始:"..i)
	sleep(500)
end

console.dismiss()
```

## 9. console.setTitle 设置控制台标题 (console.setTitle)
**函数:** `console.setTitle(title)`  
**描述:** console.setTitle 设置控制台标题

**参数:**
| 参数名 | 类型 | 必填 | 说明 |
| :--- | :--- | :--- | :--- |
| title | string | 是 | title 字符串类型 |

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | 无 |

**示例:**
```lua
console.show()
console.setTitle("日志窗口")
console.clearLog()
console.setPos(100,100)
for i=1,100 do
	console.println(3," 日志任务开始:"..i)
	sleep(500)
end

console.dismiss()
```

