# IO 标准库方法

此章节整理 Lua 标准库中 `io` 模块的文件操作方法，帮助在 Lua 层进行文件的读写操作。所有条目采用 **函数 / 描述 / 参数 / 返回值 / 示例** 的统一样式。

---

## 1. 打开文件 (io.open)
**函数:** `io.open(path, mode)`

**描述:** 打开一个文件并返回文件句柄。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要打开的文件路径 |
| mode | string | 否 | 文件打开模式：
- "r": 只读模式（默认）；
- "w": 写入模式；
- "a": 追加模式；
- "r+": 更新模式，所有之前的数据将被保存；
- "w+": 更新模式，所有之前的数据将被清除；
- "a+": 追加更新模式，所有之前的数据将被保存，只能在文件末尾进行添加；
- "b": 二进制模式（某些系统支持） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| file | 文件句柄（成功时） |
| nil, string | 失败时返回 nil 和错误信息 |

示例:
```lua
local file = io.open("/mnt/sdcard/test.txt", "r")
print(file:write("123", "a"))
file:close()
local file = io.open("/mnt/sdcard/test.txt", "r+")
print(file:read("*a"))
file:close()
```

---

## 2. 设置输入文件 (io.input)
**函数:** `io.input([file])`

**描述:** 设置默认的输入文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| file | string/file | 否 | 可以是字符串路径或 io.open 返回的文件句柄 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| file | 文件句柄 |

示例:
```lua
-- 文件路径
local handle = io.input("/mnt/sdcard/test.txt")
print(io.read("*a"))
io.close(handle)
-- 文件句柄
local file = io.open("/mnt/sdcard/test.txt", "r")
print(io.input(file))
print(io.read("*a"))
print(file)
file:close()
```

---

## 3. 设置输出文件 (io.output)
**函数:** `io.output([file])`

**描述:** 设置默认的输出文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| file | string/file | 否 | 可以是字符串路径或 io.open 返回的文件句柄 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| file | 文件句柄 |

示例:
```lua
print(io.output("/mnt/sdcard/test.txt"))
io.write("123")
io.close()
```

---

## 4. 读取文件数据 (io.read)
**函数:** `io.read([format])`

**描述:** 从当前默认输入文件读取数据，等同于 io.input():read(...)

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| format | string | 否 | 读取格式：
- "n": 读取一个数字；
- "a": 读取整个文件；
- "l": 读取一行（不包括换行符）；
- "L": 读取一行（包括换行符）；
- number: 读取指定字节数 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string/number | 读取的数据 |
| nil | 到达文件末尾或读取失败 |

示例:
```lua
io.input("/mnt/sdcard/test.txt")
while true do
    local ReadContent = io.read()
    if ReadContent == nil then
        break
    end
    print(ReadContent)
end
io.close()
```

---

## 5. 写入数据到文件 (io.write)
**函数:** `io.write(value1, value2, ...)`

**描述:** 写入数据到当前默认输出文件，等同于 io.output():write(...)

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| value1, value2, ... | any | 是 | 要写入的数据，可以是多个参数 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| file | 文件句柄（用于链式调用） |

示例:
```lua
local handle = io.output("/mnt/sdcard/test.txt")
io.write(tostring("123"))
io.close(handle)
```

---

## 6. 文件行迭代器 (io.lines)
**函数:** `io.lines([path])`

**描述:** 提供一个迭代器函数，用于逐行遍历文件内容。如果指定了文件名，则在遍历结束后会自动关闭该文件；如果使用默认文件，则在遍历结束后不会自动关闭文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 否 | 要遍历的文件路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| function | 迭代器函数，用于遍历文件内容 |

示例:
```lua
for line in io.lines("/mnt/sdcard/test.txt") do
    print(line)
end
```

---