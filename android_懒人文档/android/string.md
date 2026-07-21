# 字符串方法 (string / utf8)

收集常见字符串处理函数（含 utf8 扩展），按统一样式说明用法与示例。

---

## 1. 字符串分割 (splitStr)
**函数:** `splitStr(src, sep)`

**描述:** 根据分隔符 `sep` 把 `src` 拆分为多个子串并返回结果（实现为懒人扩展）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| src | string | 是 | 要分割的源字符串 |
| sep | string | 是 | 分隔符 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 分割后的子串数组 |

示例:
```lua
local parts = splitStr("ab#cd#ef#gh", "#")
-- parts 示例: {"ab","cd","ef","gh"}
```

---

## 2. 大小写转换 (string.lower / string.upper)
**函数:** `string.lower(s)`, `string.upper(s)`

**描述:** 将字符串转换为小写或大写。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 要转换的字符串 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 转换后的字符串 |

示例:
```lua
print(string.lower("AbC")) -- "abc"
print(string.upper("AbC")) -- "ABC"
```

---

## 3. 查找子串 (string.find)
**函数:** `string.find(s, pattern [, init [, plain]])`

**描述:** 在字符串 `s` 中查找 `pattern`，返回起始和结束索引，找不到返回 `nil`。`plain=true` 可关闭模式匹配，做纯文本查找。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 目标字符串 |
| pattern | string | 是 | 要查找的模式 |
| init | number | 否 | 开始查找的位置（默认 1） |
| plain | boolean | 否 | 是否关闭模式匹配（默认 false） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number, number | 找到的子串起始和结束索引 |
| nil | 找不到时返回 nil |

示例:
```lua
local i, j = string.find("Hello Lua ok", "Lua", 1)
print(i, j)
```

---

## 4. 字符串反转 (string.reverse)
**函数:** `string.reverse(s)`

**描述:** 反转字符串中的字符顺序。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 要反转的字符串 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 反转后的字符串 |

示例:
```lua
print(string.reverse("abc")) -- "cba"
```

---

## 5. 字符串格式化 (string.format)
**函数:** `string.format(formatstring, ...)`

**描述:** 根据格式化字符串生成新字符串。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| formatstring | string | 是 | 格式化字符串 |
| ... | any | 否 | 要格式化的值 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 格式化后的字符串 |

示例:
```lua
print(string.format("value is %d", 666))
```

---

## 6. 字符编码转换 (string.char / string.byte)
**函数:** `string.char(...)`, `string.byte(s [, i [, j]])`

**描述:** `string.char` 将 ASCII 码转换为字符；`string.byte` 将字符转换为 ASCII 码。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| ... | number | 是 | ASCII 码（string.char） |
| s | string | 是 | 目标字符串（string.byte） |
| i | number | 否 | 起始位置（string.byte，默认 1） |
| j | number | 否 | 结束位置（string.byte，默认 i） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 转换后的字符串（string.char） |
| number | 字符的 ASCII 码（string.byte） |

示例:
```lua
print(string.char(97,98,99)) -- "abc"
print(string.byte("abc", 2)) -- 98
```

---

## 7. 字符串长度与重复 (string.len / string.rep)
**函数:** `string.len(s)`, `string.rep(s, n)`

**描述:** `string.len` 返回字符串的字节长度；`string.rep` 重复字符串 n 次。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 目标字符串 |
| n | number | 是 | 重复次数（string.rep） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 字符串的字节长度（string.len） |
| string | 重复后的字符串（string.rep） |

示例:
```lua
print(string.len("abcdef")) -- 6
print(string.rep("abc", 2)) -- "abcabc"
```

---

## 8. UTF-8 字符串查找 (utf8.inStr / utf8.inStrRev)
**函数:** `utf8.inStr(start, s, pattern)`, `utf8.inStrRev(s, pattern, start, compare)`

**描述:** 提供对 UTF-8 字符串的查找功能。`utf8.inStr` 从指定位置开始查找；`utf8.inStrRev` 反向查找。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| start | number | 是 | 开始查找的位置（utf8.inStr） |
| s | string | 是 | 目标字符串 |
| pattern | string | 是 | 要查找的模式 |
| compare | function | 否 | 比较函数（utf8.inStrRev） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 找到的位置索引 |
| nil | 找不到时返回 nil |

示例:
```lua
print(utf8.inStr(1, "中国人民万岁", "人民"))
```

---

## 9. UTF-8 字符串反转 (utf8.strReverse)
**函数:** `utf8.strReverse(s)`

**描述:** 反转 UTF-8 字符串中的字符顺序。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 要反转的 UTF-8 字符串 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 反转后的 UTF-8 字符串 |

示例:
```lua
print(utf8.strReverse("中国人民"))
```

---

## 10. UTF-8 字符串长度 (utf8.length)
**函数:** `utf8.length(s)`

**描述:** 以字符为单位计算 UTF-8 字符串的长度。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 目标 UTF-8 字符串 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 字符串的字符长度 |

示例:
```lua
print(utf8.length("中国人民万岁"))
```

---

## 11. UTF-8 字符串截取 (utf8.left / utf8.right / utf8.mid)
**函数:** `utf8.left(s, n)`, `utf8.right(s, n)`, `utf8.mid(s, start, len)`

**描述:** 截取 UTF-8 字符串的指定部分。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 目标 UTF-8 字符串 |
| n | number | 是 | 截取的字符数（left/right） |
| start | number | 是 | 开始截取的位置（mid） |
| len | number | 是 | 截取的字符数（mid） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 截取后的 UTF-8 字符串 |

示例:
```lua
print(utf8.left("中国人民万岁", 2))
print(utf8.mid("中国人民万岁", 2, 2))
```

---

## 12. UTF-8 字符串裁剪 (utf8.strCut)
**函数:** `utf8.strCut(s, start, len)`

**描述:** 移除 UTF-8 字符串中指定范围的字符并返回新字符串。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| s | string | 是 | 目标 UTF-8 字符串 |
| start | number | 是 | 开始位置 |
| len | number | 是 | 要移除的字符数 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 裁剪后的 UTF-8 字符串 |

示例:
```lua
print(utf8.strCut("中国人民万岁", 2, 2))
``` 
