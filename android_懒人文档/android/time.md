# 时间方法 (time)

本章节收录与时间、时钟相关的函数与用法。

---

## 1. 系统时间戳（毫秒） (systemTime)
**函数:** `systemTime()`

**描述:** 返回系统当前时间戳，单位为毫秒。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 系统当前时间戳（毫秒） |

示例:
```lua
local tm = systemTime()
print(tm)
```

---

## 2. 获取网络时间字符串 (getNetWorkTime)
**函数:** `getNetWorkTime()`

**描述:** 从网络获取当前时间并以 `年-月-日_时-分-秒` 的格式返回字符串。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 网络时间字符串，格式为 `年-月-日_时-分-秒` |

示例:
```lua
local tm = getNetWorkTime()
print(tm) -- e.g. 2023-01-01_12-00-00
```

---

## 3. 脚本运行时间（毫秒） (tickCount)
**函数:** `tickCount()`

**描述:** 返回脚本自启动以来的运行时长，单位为毫秒。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 脚本运行时间（毫秒） |

示例:
```lua
local t = tickCount()
print(t)
```

---

## 4. 日期格式化 (os.date)
**函数:** `os.date(format [, time])`

**描述:** 用于格式化时间戳为可读时间字符串，time为可选时间戳，省略时取当前时间。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| format | string | 是 | 格式化字符串 |
| time | number | 否 | 时间戳（默认当前时间） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 格式化后的时间字符串 |

示例:
```lua
local now = os.date("%Y-%m-%d %H:%M:%S")
-- %a abbreviated weekday name (e.g., Wed)
-- %A full weekday name (e.g., Wednesday)
-- %b abbreviated month name (e.g., Sep)
-- %B full month name (e.g., September)
-- %c date and time (e.g., 09/16/98 23:48:10)
-- %d 一个月中的几号[01~31]
-- %H 24小时[00~23]
-- %I 12小时[01~12]
-- %j 一年中的第几天[001~366]
-- %M 分钟[00~59]
-- %m 月份[01~12]
-- %p am(上午),pm(下午)
-- %S 秒[00~59]
-- %w 星期几[0~6 = 星期日~星期六]
-- %x date (e.g., 09/16/98)
-- %X time (e.g., 23:48:10)
-- %y two-digit year (98) [00~99]
-- %Y 年份(1998)
-- %% the character '%'

--获取当前时间戳(秒)
local secs = os.time()
local year = string.sub(now,1,4)
local month = string.sub(now,6,7)
local day = string.sub(now,9,10)
local hour = string.sub(now,12,13)
local minute = string.sub(now,15,16)
local second = string.sub(now,18,19)

--获取7天前的时间
local ta = {
    year=year,
    month=month,
    day=day-7,
    hour=hour,
    min=minute,
    sec=second
}
--2018-05-02 09:50:57
local t = os.date("%Y-%m-%d %H:%M:%S", os.time(ta))

--获取今年2月份的天数
--3月份开始减去1天就是2月份的最后一天
local ta = {
    year=year,
    month=3,
    day=0,
}
--28
local days = os.date("%d", os.time(ta))
```

---

## 5. 获取时间戳 (os.time)
**函数:** `os.time([table])`

**描述:** 默认获取当前时间戳（秒），也可以指定table参数。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| table | table | 否 | 时间表（包含year, month, day等字段） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 时间戳（秒） |

示例:
```lua
local time = os.time()
local hour = os.date("*t", time).hour
print(hour)

--获取指定时间的时间戳
local ta = {
    year=2023,
    month=1,
    day=1,
    hour=12,
    min=0,
    sec=0
}
local timestamp = os.time(ta)
print(timestamp)
``` 
