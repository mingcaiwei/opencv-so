# luaopenov 部分扩展 (cv)

本章节整理 `cv`（基于 OpenCV 4.5.3 的懒人扩展）提供的工具函数，帮助在 Lua 层调用图像处理与矩阵相关的操作。所有条目采用 **函数 / 描述 / 参数 / 返回值 / 示例** 的统一样式。

---

## 1. 区域截图并返回 Mat 矩阵 (cv.snapShot)
**函数:** `cv.snapShot(l, t, r, b)`

**描述:** 对屏幕指定区域截图并返回一个 OpenCV `Mat` 矩阵对象（该函数为懒人扩展）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| l | number | 是 | 截图的左边界（像素） |
| t | number | 是 | 截图的上边界（像素） |
| r | number | 是 | 截图的右边界（像素） |
| b | number | 是 | 截图的下边界（像素） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| cv.Mat | 截图对应的 Mat 对象 |

示例:
```lua
local image = cv.snapShot(0, 0, 500, 500)
if image then
	-- 处理 image
	image:release()
end
```

---

## 2. Point 操作 (cv.newPoint / cv.getPoint / cv.setPoint)
**函数:** `cv.newPoint(x, y)`, `cv.getPoint(ptr)`, `cv.setPoint(ptr, x, y)`

**描述:** 创建 `cv::Point` 指针并可获取或修改其坐标（懒人扩展）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| x | number | 是 | 点的x坐标（cv.newPoint, cv.setPoint） |
| y | number | 是 | 点的y坐标（cv.newPoint, cv.setPoint） |
| ptr | userdata | 是 | Point指针（cv.getPoint, cv.setPoint） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | Point指针（cv.newPoint） |
| table | 包含x和y坐标的表（cv.getPoint） |
| nil | cv.setPoint无返回值 |

示例:
```lua
local ptr = cv.newPoint(100, 200)
print(cv.getPoint(ptr))
cv.setPoint(ptr, 500, 500)
cv.deletePtr(ptr)
```

---

## 3. 删除并回收指针 (cv.deletePtr)
**函数:** `cv.deletePtr(ptr)`

**描述:** 回收由 `cv.new*` 系列函数分配的指针资源。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| ptr | userdata | 是 | 要回收的指针 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| nil | 无返回值 |

示例:
```lua
local p = cv.newInt(5)
cv.deletePtr(p)
```

---

## 4. Point2f 操作 (cv.newPoint2f / cv.getPoint2f / cv.setPoint2f)
**函数:** `cv.newPoint2f(x, y)`, `cv.getPoint2f(ptr)`, `cv.setPoint2f(ptr, x, y)`

**描述:** 创建和操作 `cv::Point2f`（浮点坐标）指针。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| x | number | 是 | 点的x坐标（cv.newPoint2f, cv.setPoint2f） |
| y | number | 是 | 点的y坐标（cv.newPoint2f, cv.setPoint2f） |
| ptr | userdata | 是 | Point2f指针（cv.getPoint2f, cv.setPoint2f） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | Point2f指针（cv.newPoint2f） |
| table | 包含x和y坐标的表（cv.getPoint2f） |
| nil | cv.setPoint2f无返回值 |

示例:
```lua
local p = cv.newPoint2f(100.0, 200.0)
print(cv.getPoint2f(p))
cv.setPoint2f(p, 500.0, 500.0)
cv.deletePtr(p)
```

---

## 5. 原始类型指针操作: newInt/getInt/setInt (cv.newInt/cv.getInt/cv.setInt)
**函数:** `cv.newInt(val)`, `cv.getInt(ptr)`, `cv.setInt(ptr, val)`

**描述:** 分配一个整型指针并可读写其值。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| val | number | 是 | 初始值或要设置的整数值（cv.newInt, cv.setInt） |
| ptr | userdata | 是 | 整型指针（cv.getInt, cv.setInt） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | 整型指针（cv.newInt） |
| number | 指针指向的整数值（cv.getInt） |
| nil | cv.setInt无返回值 |

示例:
```lua
local p = cv.newInt(5)
print(cv.getInt(p))
cv.setInt(p, 8)
cv.deletePtr(p)
```

---

## 6. 原始类型指针操作: newDouble/getDouble/setDouble (cv.newDouble/cv.getDouble/cv.setDouble)
**函数:** `cv.newDouble(val)`, `cv.getDouble(ptr)`, `cv.setDouble(ptr, val)`

**描述:** 分配一个双精度浮点型指针并可读写其值。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| val | number | 是 | 初始值或要设置的双精度浮点值（cv.newDouble, cv.setDouble） |
| ptr | userdata | 是 | 双精度浮点型指针（cv.getDouble, cv.setDouble） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | 双精度浮点型指针（cv.newDouble） |
| number | 指针指向的双精度浮点值（cv.getDouble） |
| nil | cv.setDouble无返回值 |

示例:
```lua
local p = cv.newDouble(5.0)
print(cv.getDouble(p))
cv.setDouble(p, 8.0)
cv.deletePtr(p)
```

---

## 7. 原始类型指针操作: newFloat/getFloat/setFloat (cv.newFloat/cv.getFloat/cv.setFloat)
**函数:** `cv.newFloat(val)`, `cv.getFloat(ptr)`, `cv.setFloat(ptr, val)`

**描述:** 分配一个单精度浮点型指针并可读写其值。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| val | number | 是 | 初始值或要设置的单精度浮点值（cv.newFloat, cv.setFloat） |
| ptr | userdata | 是 | 单精度浮点型指针（cv.getFloat, cv.setFloat） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | 单精度浮点型指针（cv.newFloat） |
| number | 指针指向的单精度浮点值（cv.getFloat） |
| nil | cv.setFloat无返回值 |

示例:
```lua
local p = cv.newFloat(5.0)
print(cv.getFloat(p))
cv.setFloat(p, 8.0)
cv.deletePtr(p)
```

---

## 8. 原始类型指针操作: newLong/getLong/setLong (cv.newLong/cv.getLong/cv.setLong)
**函数:** `cv.newLong(val)`, `cv.getLong(ptr)`, `cv.setLong(ptr, val)`

**描述:** 分配一个长整型指针并可读写其值。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| val | number | 是 | 初始值或要设置的长整数值（cv.newLong, cv.setLong） |
| ptr | userdata | 是 | 长整型指针（cv.getLong, cv.setLong） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | 长整型指针（cv.newLong） |
| number | 指针指向的长整数值（cv.getLong） |
| nil | cv.setLong无返回值 |

示例:
```lua
local p = cv.newLong(1000000000)
print(cv.getLong(p))
cv.setLong(p, 1000)
cv.deletePtr(p)
```

---

## 9. 原始类型指针操作: newByte/getByte/setByte (cv.newByte/cv.getByte/cv.setByte)
**函数:** `cv.newByte(val)`, `cv.getByte(ptr)`, `cv.setByte(ptr, val)`

**描述:** 分配一个字节型指针并可读写其值。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| val | number | 是 | 初始值或要设置的字节值（cv.newByte, cv.setByte） |
| ptr | userdata | 是 | 字节型指针（cv.getByte, cv.setByte） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| userdata | 字节型指针（cv.newByte） |
| number | 指针指向的字节值（cv.getByte） |
| nil | cv.setByte无返回值 |

示例:
```lua
local p = cv.newByte(190)
print(cv.getByte(p))
cv.setByte(p, 100)
cv.deletePtr(p)
```

---

（以上为常用扩展函数示例；懒人精灵已集成 OpenCV 4.5.3 的完整函数集合，更多高级用法请参考 OpenCV 官方文档。）

