# FFI方法 (ffi)

此章节整理 `ffi` (Foreign Function Interface) 库中常用的方法，条目采用统一的样式格式，方便查阅与复制示例。

---

## 1. 定义C语言类型和函数 (ffi.cdef)
**函数:** `ffi.cdef(str)`

**描述:** 用于定义C语言的类型和函数。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| str | string | 是 | 该字符串包含 C 语言的类型声明和函数原型。 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| nil | 返回为空 |

示例:
```lua
-- 定义C函数原型
ffi.cdef[[
        int getpid(void);
]]

-- 加载C库
local clib = ffi.load("libc")

-- 调用getpid函数获取当前进程PID
local pid = clib.getpid()

-- 打印PID
print("当前进程pid:" .. pid)
```

---

## 2. 加载动态库 (ffi.load)
**函数:** `ffi.load(str)`

**描述:** 加载一个动态库。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| str | string | 是 | 该字符串指定要加载的库的路径和名称。 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| userdata | 返回一个指针对象 |

示例:
```lua
-- 定义 C 函数的原型
ffi.cdef[[
        int add(int a, int b);
]]

-- 加载动态库
local mylib = ffi.load("/data/local/tmp/liblrapi.so")

-- 调用 C 函数
local result = mylib.add(3, 4)
print(result)
```
