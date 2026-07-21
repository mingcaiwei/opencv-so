# 数组方法 (Array/Table)

## 1. 获取数组长度 (`#`)
**说明:** 获取数组中连续数值索引的元素个数。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | 数组长度（连续数值索引的元素个数） |

示例:
```lua
local arr = {"A", "B", "C"}
local len = #arr
print("数组长度: " .. len)  -- 输出: 3

for i = 1, #arr do
    print(arr[i])
end
```

---

## 2. 数组元素连接 (`table.concat`)
**函数:** `table.concat(list, sep, start, end)`

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| list | table | 是 | 要连接的数组 |
| sep | string | 否 | 分隔符，默认为空字符串 |
| start | integer | 否 | 开始索引（默认 1） |
| end | integer | 否 | 结束索引（默认 #list） |


| 返回值类型 | 说明 |
|:---:|:---:|
| string | 连接后的字符串 |

示例:
```lua
local arr = {"苹果", "香蕉", "橘子"}
print(table.concat(arr))            -- 苹果香蕉橘子
print(table.concat(arr, ", "))    -- 苹果, 香蕉, 橘子
print(table.concat(arr, "-", 2, 3))-- 香蕉-橘子
```

---

## 3. 插入新元素 (`table.insert`)
**函数:** `table.insert(list, pos_or_value, [value])`

说明: 如果只传两个参数，`table.insert(list, value)` 会插入到末尾；传三个参数 `table.insert(list, pos, value)` 会在 pos 位置插入。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| list | table | 是 | 目标数组 |
| pos_or_value | number |是 | 则为插入索引，否则视为要插入的值 |
| value | any | 否 | 当提供 pos 时为插入的值 |

返回值: 无

示例:
```lua
local arr = {"A", "B"}
table.insert(arr, "C")            -- 插入到末尾: A,B,C
table.insert(arr, 1, "Top")       -- 插入到开头: Top,A,B,C
print(table.concat(arr, ","))
```

---

## 4. 移除元素 (`table.remove`)
**函数:** `table.remove(list, [pos])`

说明: 不传 pos 时移除并返回最后一个元素；传 pos 时移除并返回 pos 位置上的元素。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| list | table | 是 | 目标数组 |
| pos | integer | 否 | 要移除的索引（默认最后一个） |

| 返回值类型 | 说明 |
|:---:|:---:|
| any | 移除后的元素 |

示例:
```lua
local arr = {"A", "B", "C", "D"}
local removed = table.remove(arr, 2) -- 移除 "B"
print("被移除的是: " .. removed) -- B
print(table.concat(arr, ",")) -- A,C,D
```

---

## 5. 数组排序 (`table.sort`)
**函数:** `table.sort(list, [comp])`

说明: 默认按升序排序；提供比较函数 comp(a,b) 返回 true 表示 a 排在 b 前面。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| list | table | 是 | 目标数组 |
| comp | function | 否 | 自定义比较函数 |

返回值: 无

示例:
```lua
local nums = {5, 1, 9, 2}
table.sort(nums)
print(table.concat(nums, ",")) -- 1,2,5,9

table.sort(nums, function(a, b) return a > b end)
print(table.concat(nums, ",")) -- 9,5,2,1
```


