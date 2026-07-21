# 文件系统方法 (lfs)

此章节整理 `lfs` (LuaFileSystem) 库中常用的文件系统相关函数，条目采用统一的样式格式，方便查阅与复制示例。

---

## 1. 获取文件或目录属性 (lfs.attributes)
**函数:** `lfs.attributes(path)`

**描述:** 获取文件或目录的属性信息。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要获取属性的文件或目录的绝对路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 包含文件或目录属性信息的表 |

示例:
```lua
local path = "/mnt/sdcard/test.png"
local ret = lfs.attributes(path)
print(ret)
```

---

## 2. 改变当前工作目录 (lfs.chdir)
**函数:** `lfs.chdir(path)`

**描述:** 改变当前工作目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要切换到的新目录的绝对路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| nil | 无 |

示例:
```lua
local path = "/mnt/sdcard"
lfs.chdir(path)
```

---

## 3. 获取当前工作目录 (lfs.currentdir)
**函数:** `lfs.currentdir()`

**描述:** 获取当前工作目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| - | - | - | 无 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 包含当前工作目录绝对路径的字符串 |

示例:
```lua
local currentDir = lfs.currentdir()
print(currentDir)
```

---

## 4. 遍历目录 (lfs.dir)
**函数:** `lfs.dir(path)`

**描述:** 遍历目录中的文件和子目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要遍历的目录的绝对路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| function | 迭代器函数，用于遍历目录内容 |

示例:
```lua
local path = "/mnt/sdcard"
for file in lfs.dir(path) do
    print(file)
end
```

---

## 5. 创建硬链接 (lfs.link)
**函数:** `lfs.link(src, dest)`

**描述:** 创建硬链接。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| src | string | 是 | 原始文件的路径 |
| dest | string | 是 | 新链接的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number/boolean | 成功返回0，失败返回false |

示例:
```lua
local src = getWorkPath() .. "/test.png"
local dest = getWorkPath() .. "/test1.png"
local r = lfs.link(src, dest, true)
print(r)
```

---

## 6. 锁定文件 (lfs.lock)
**函数:** `lfs.lock(file, mode)`

**描述:** 锁定文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| file | file | 是 | 要锁定的文件句柄 |
| mode | string | 是 | 锁定模式："r"(读锁定), "w"(写锁定), "u"(解锁) |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功锁定文件 |

示例:
```lua
local filePath = "/mnt/sdcard/test.png"
local file, err = io.open(filePath, "w")
if file then
    local lock, lockErr = lfs.lock(file, "w")
    if lock then
        print("File lock acquired successfully")
        -- 进行文件操作
        lfs.unlock(file)
        print("File lock released")
    else
        print("Failed to acquire file lock: " .. lockErr)
    end
    file:close()
else
    print("Failed to open file: " .. err)
end
```

---

## 7. 创建目录 (lfs.mkdir)
**函数:** `lfs.mkdir(path)`

**描述:** 创建目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要创建的目录的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功创建目录 |

示例:
```lua
local path = "/mnt/sdcard/new_folder"
local created = lfs.mkdir(path)
if created then
    print("Folder created successfully.")
else
    print("Failed to create folder.")
end
```

---

## 8. 删除空目录 (lfs.rmdir)
**函数:** `lfs.rmdir(path)`

**描述:** 删除空目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要删除的空目录的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功删除目录 |

示例:
```lua
local path = "/mnt/sdcard/testdir"
mkdir(path)
local deleted = lfs.rmdir(path)
if deleted then
    print("Folder deleted successfully.")
else
    print("Failed to delete folder.")
end
```

---

## 9. 获取符号链接属性 (lfs.symlinkattributes)
**函数:** `lfs.symlinkattributes(path)`

**描述:** 获取符号链接文件的属性。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要获取属性的符号链接文件的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| table | 包含符号链接文件属性信息的表 |

示例:
```lua
local path = "/mnt/sdcard/test.txt"
local attributes = lfs.symlinkattributes(path)
if attributes then
    print("Attributes of symlink file:")
    for key, value in pairs(attributes) do
        print(key .. ": " .. value)
    end
else
    print("Failed to get attributes of symlink file.")
end
```

---

## 10. 更新文件时间 (lfs.touch)
**函数:** `lfs.touch(path)`

**描述:** 更新文件的访问和修改时间。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要更新时间的文件的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功更新文件时间 |

示例:
```lua
local path = "/mnt/sdcard/old_file"
local updated = lfs.touch(path)
if updated then
    print("File time updated successfully.")
else
    print("Failed to update file time.")
end
```

---

## 11. 解锁文件 (lfs.unlock)
**函数:** `lfs.unlock(file)`

**描述:** 解锁文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| file | file | 是 | 要解锁的文件句柄 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功解锁文件 |

示例:
```lua
local filePath = "/mnt/sdcard/test.png"
local file, err = io.open(filePath, "w")
if file then
    local lock, lockErr = lfs.lock(file, "w")
    if lock then
        print("File lock acquired successfully")
        -- 进行文件操作
        lfs.unlock(file)
        print("File lock released")
    else
        print("Failed to acquire file lock: " .. lockErr)
    end
    file:close()
else
    print("Failed to open file: " .. err)
end
```

---

## 12. 锁定目录 (lfs.lock_dir)
**函数:** `lfs.lock_dir(path)`

**描述:** 锁定目录。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| path | string | 是 | 要锁定的目录的路径 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否成功锁定目录 |

示例:
```lua
local path = "/mnt/sdcard/locked_folder"
local locked = lfs.lock_dir(path)
if locked then
    print("Directory locked successfully.")
else
    print("Failed to lock directory.")
end
```
