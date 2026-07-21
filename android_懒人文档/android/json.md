# json方法 (json)
## 1. jsonLib.encode 把lua表格编码成json字符串 (jsonLib.encode)
**函数:** `jsonLib.encode(tb)`  
**描述:** jsonLib.encode 把lua表格编码成json字符串

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| string | json字符串 |

**示例:**
```lua
local tb={
	code = 1,
	data = {
		ret = "hello ok",
		status = 123
	}
}
print(jsonLib.encode(tb))
```

## 2. jsonLib.decode 把json字符串转换成lua表格 (jsonLib.decode)
**函数:** `jsonLib.decode(json)`  
**描述:** jsonLib.decode 把json字符串转换成lua表格

**返回值:**
| 类型 | 说明 |
| :--- | :--- |
| any | lua表格 |

**示例:**
```lua
local json = "{\"data\":{\"ret\":\"hello ok\",\"status\":123},\"code\":1}"
print(jsonLib.decode(json))
```
