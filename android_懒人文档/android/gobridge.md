# GoBridge相关方法 (gobridge)

本章节整理 `gobridge` 提供的相关方法，帮助在 Lua 层调用 Go 语言相关功能。所有条目采用 **函数 / 描述 / 参数 / 返回值 / 示例** 的统一样式。

---

## 1. gobridge.register(funcname, function) : 注册Lua回调函数

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| funcname | string | 是 | 注册的函数名称 |
| function | function | 是 | Lua回调函数 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 注册的函数可以被Go代码通过cgo调用 | 无 |

示例代码:
```lua

-- 注册带返回值的函数
gobridge.register("add" , function (a,b)
	return a + b
end)

gobridge.call("libgo.so" , "Run")

-- Go端调用示例:
package main

import (
	"sync"
	"github.com/LrGo/LibGo/LibGo/bridge"
)

func Run() {
	results, err := bridge.Call("add", 1, 2)
	if err == nil {
		bridge.PrintLogf("测试结果:%d", results[0].(int64))
	}
}

var registerOnce sync.Once

func init() {
	registerOnce.Do(func() {
		funcs := []struct {
			name string
			fn   interface{}
		}{
			{"Run", Run},
		}
		for _, f := range funcs {
			if !bridge.Register(f.name, f.fn) {
				bridge.PrintLog("函数 %s 注册失败", f.name)
			}
		}
	})
}

func main() {}

```

---

## 2. gobridge.call(libpath, funcname, ...) : 调用Go函数

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| libpath | string | 是 | Go编译的动态库路径(如"libgo.so") |
| funcname | string | 是 | Go导出的函数名 |
| ... | any | 否 | 传递给Go函数的参数(可变参数) |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| any | 返回Go函数的执行结果(多种类型) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 支持传递多种类型的参数 | 无 |
| 支持返回多种类型的返回值 | 无 |
| 可以传递二进制数据 | 无 |

示例代码:
```lua

-- 调用加法函数
local sum = gobridge.call("libgo.so", "Add", 8, 3)
print(sum)  -- 输出11

-- 调用字符串处理
local msg = gobridge.call("libgo.so", "Greet", "World")
print(msg)  -- 输出"Hello World"

-- 二进制数据传递
local data = gobridge.tobytes("123")
local md5 = gobridge.call("libgo.so", "GetMD5", data)
print(md5)  -- 输出"202cb962ac59075b964b07152d234b70"

--对应的go注册函数如下
package main

import (
	"sync"
	"crypto/md5"
	"encoding/hex"
	"github.com/LrGo/LibGo/LibGo/bridge"
)

// Add 加法函数
func Add(a, b int) int {
	return a + b
}

// Greet 问候函数
func Greet(name string) string {
	return "Hello, " + name + "!"
}

// GetMD5 获取数据的md5
func GetMD5(data []byte) string {
	hash := md5.Sum(data)
	return hex.EncodeToString(hash[:])
}

var registerOnce sync.Once

func init() {
	registerOnce.Do(func() {
		funcs := []struct {
			name string
			fn   interface{}
		}{
			{"Add", Add},     // 注册加法函数
			{"Greet", Greet}, // 注册问候函数
			{"GetMD5",GetMD5}, // 注册MD5函数
		}

		for _, f := range funcs {
			bridge.Register(f.name, f.fn)
		}
	})
}

func main() {
}


```

---
