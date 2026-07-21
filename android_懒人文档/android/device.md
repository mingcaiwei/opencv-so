# 设备方法 (Device)

此章节整理懒人精灵的设备相关方法，条目采用统一的样式格式，方便查阅与复制示例。

---

## 1. 获取 CPU 架构 (`getCpuArch`)
**函数**: `getCpuArch()`

**描述**: 获取 CPU 架构（0=x86，1=arm，2=arm64）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 0=x86，1=arm，2=arm64 |

示例:
```lua
local t = getCpuArch()
if t == 0 then
  print("x86")
elseif t == 1 then
  print("arm")
elseif t == 2 then
  print("arm64")
end
```

---

## 2. 获取 SD 卡路径 (`getSdPath`)
**函数**: `getSdPath()`

**描述**: 获取 SD 卡的绝对路径。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | SD 卡的绝对路径 |

示例:
```lua
local path = getSdPath()
print("sd卡路径:"..path)
```

---

## 3. 设置悬浮窗位置 (`setControlBarPosNew`)
**函数**: `setControlBarPosNew(x, y)`

**描述**: 设置悬浮窗位置（按屏幕宽高比例）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| x | 浮点 | 是 | 水平位置，范围 0-1 |
| y | 浮点 | 是 | 垂直位置，范围 0-1 |

返回值: 无

示例:
```lua
setControlBarPosNew(0.5, 0.5) -- 居中
```

---

## 4. 显示或隐藏悬浮按钮 (`showControlBar`)
**函数**: `showControlBar(isShow)`

**描述**: 显示或隐藏悬浮按钮。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| isShow | 布尔 | 是 | true 显示，false 隐藏 |

返回值: 无

示例:
```lua
showControlBar(true)
```

---

## 5. 重启当前脚本 (`restartScript`)
**函数**: `restartScript()`

**描述**: 重启当前脚本。

参数: 无

返回值: 无

示例:
```lua
toast("开始重启当前脚本")
sleep(1000)
restartScript()
```

---

## 6. 获取脚本工作目录 (`getWorkPath`)
**函数**: `getWorkPath()`

**描述**: 获取脚本工作目录（具有可执行权限）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 脚本工作目录的绝对路径 |

示例:
```lua
local path = getWorkPath()
print("当前工作目录:"..path)
```

---

## 7. 获取 apk 壳子版本 (`getApkVerInt`)
**函数**: `getApkVerInt()`

**描述**: 获取 apk 壳子版本（整数）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | apk 壳子版本 |

示例:
```lua
local ver = getApkVerInt()
print("apk ver:"..ver)
```

---

## 8. 获取脚本版本号 (`getScriptVersion`)
**函数**: `getScriptVersion()`

**描述**: 获取脚本版本号（整数）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 脚本版本号 |

示例:
```lua
local ver = getScriptVersion()
print("当前脚本版本:"..ver)
```

---

## 9. 设备震动 (`vibrate`)
**函数**: `vibrate(during)`

**描述**: 使设备震动。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| during | 整数 | 是 | 震动持续时间，单位毫秒 |

返回值: 无

示例:
```lua
for i=1,5 do
  vibrate(100)
  sleep(500)
end
```

---

## 10. 获取设备 IMSI (`getSubscriberId`)
**函数**: `getSubscriberId()`

**描述**: 获取设备 IMSI。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 设备 IMSI |

示例:
```lua
local imsi = getSubscriberId()
print(imsi)
```

---

## 11. 获取 SIM 卡序列号 (`getSimSerialNumber`)
**函数**: `getSimSerialNumber()`

**描述**: 获取 SIM 卡序列号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | SIM 卡序列号 |

示例:
```lua
local simn = getSimSerialNumber()
print(simn)
```

---

## 12. 获取设备 DPI (`getDisplayDpi`)
**函数**: `getDisplayDpi()`

**描述**: 获取设备 DPI。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 设备 DPI |

示例:
```lua
local dpi = getDisplayDpi()
print(dpi)
```

---

## 13. 获取设备电量 (`getBatteryLevel`)
**函数**: `getBatteryLevel()`

**描述**: 获取设备电量。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 设备电量百分比 |

示例:
```lua
local battery = getBatteryLevel()
print(battery)
```

---

## 14. 读取 UI 配置 (`getUIConfig`)
**函数**: `getUIConfig(configName)`

**描述**: 读取 UI 配置，返回键值对数组/表。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| configName | 字符串 | 是 | 配置文件名 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 表 | 键值对表，若配置不存在则返回 nil |

示例:
```lua
local arr = getUIConfig("main.config")
if arr ~= nil then
  for k,v in pairs(arr) do
    print("key:"..k.." val:"..v)
  end
end
```

---

## 15. 播放音频文件 (`playAudio`)
**函数**: `playAudio(audio_path)`

**描述**: 播放音频文件。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| audio_path | 字符串 | 是 | 资源文件名或路径 |

返回值: 无

示例:
```lua
playAudio("test.mp3")
sleep(10000)
stopAudio()
```

---

## 16. 停止播放音频 (`stopAudio`)
**函数**: `stopAudio()`

**描述**: 停止播放音频。

参数: 无

返回值: 无

示例:
```lua
stopAudio()
```

---

## 17. 安装 lrj 更新包 (`installLrPkg`)
**函数**: `installLrPkg(lrpath)`

**描述**: 安装 lrj 更新包（非 apk）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| lrpath | 字符串 | 是 | 待安装包的绝对路径 |

返回值: 无

示例:
```lua
installLrPkg("/mnt/sdcard/update.lrj")
```

---

## 18. 获取当前应用包名 (`getPackageName`)
**函数**: `getPackageName()`

**描述**: 获取当前应用包名。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 当前应用包名 |

示例:
```lua
local pkg = getPackageName()
print(pkg)
```

---

## 19. 获取已安装 APK (`getInstalledApk`)
**函数**: `getInstalledApk()`

**描述**: 获取已安装 APK（列表或字符串）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或表 | 已安装 APK 信息 |

示例:
```lua
local list = getInstalledApk()
print(list)
```

---

## 20. 获取已安装应用信息 (`getInstalledApps`)
**函数**: `getInstalledApps()`

**描述**: 获取已安装应用的信息（可遍历）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 表 | 已安装应用信息表，若获取失败则返回 nil |

示例:
```lua
local list = getInstalledApps()
if list ~= nil then
  for i=1,#list do
    print(list[i])
  end
end
```

---

## 21. 获取懒人开放的 API 接口指针 (`getLrApi`)
**函数**: `getLrApi()`

**描述**: 获取懒人开放的 API 接口指针（供 FFI 使用）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 指针或 userdata | API 接口指针 |

示例:
```lua
local ptr = getLrApi()
print(ptr)
```

---

## 22. 获取设备 OAID (`getOaid`)
**函数**: `getOaid()`

**描述**: 获取设备 OAID。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或 nil | 设备 OAID，若获取失败则返回 nil |

示例:
```lua
local oaid = getOaid()
if oaid ~= nil then print(oaid) end
```

---

## 23. 获取所有已安装 app 的详细信息 (`getInsallAppInfos`)
**函数**: `getInsallAppInfos()`

**描述**: 获取所有已安装 app 的详细信息（JSON）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或 nil | 已安装 app 详细信息的 JSON 字符串，若获取失败则返回 nil |

示例:
```lua
local json = getInsallAppInfos()
if json ~= nil then print(json) end
```

---

## 24. 获取设备分辨率等详细信息 (`getDisplayInfo`)
**函数**: `getDisplayInfo()`

**描述**: 获取设备分辨率等详细信息（JSON）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或 nil | 设备分辨率等详细信息的 JSON 字符串，若获取失败则返回 nil |

示例:
```lua
local json = getDisplayInfo()
if json ~= nil then print(json) end
```

---

## 25. 获取所有传感器信息 (`getSensorsInfo`)
**函数**: `getSensorsInfo()`

**描述**: 获取所有传感器信息（JSON）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或 nil | 所有传感器信息的 JSON 字符串，若获取失败则返回 nil |

示例:
```lua
local json = getSensorsInfo()
if json ~= nil then print(json) end
```

---

## 26. 安装 APK (`installApk`)
**函数**: `installApk(apkpath)`

**描述**: 安装 APK（通过路径）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| apkpath | 字符串 | 是 | apk 文件绝对路径 |

返回值: 无

示例:
```lua
installApk("/mnt/sdcard/test.apk")
```

---

## 27. 判断当前是否处于调试状态 (`checkIsDebug`)
**函数**: `checkIsDebug()`

**描述**: 判断当前是否处于调试状态。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 布尔 | true 表示处于调试状态，false 表示非调试状态 |

示例:
```lua
local r = checkIsDebug()
if r then print("调试中") else print("非调试") end
```

---

## 28. 获取设备 ID (`getDeviceId`)
**函数**: `getDeviceId()`

**描述**: 获取设备 ID。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 设备 ID |

示例:
```lua
local devId = getDeviceId()
print(devId)
```

---

## 29. 获取设备品牌 (`getBrand`)
**函数**: `getBrand()`

**描述**: 获取设备品牌（BRAD）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 设备品牌 |

示例:
```lua
local brand = getBrand()
print(brand)
```

---

## 30. 获取 Bootloader 版本号 (`getBootLoader`)
**函数**: `getBootLoader()`

**描述**: 获取 Bootloader 版本号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | Bootloader 版本号 |

示例:
```lua
print(getBootLoader())
```

---

## 31. 获取主板编号 (`getBoard`)
**函数**: `getBoard()`

**描述**: 获取主板编号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 主板编号 |

示例:
```lua
print(getBoard())
```

---

## 32. 获取制造商代号 (`getManufacturer`)
**函数**: `getManufacturer()`

**描述**: 获取制造商代号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 制造商代号 |

示例:
```lua
print(getManufacturer())
```

---

## 33. 获取产品代号 (`getProduct`)
**函数**: `getProduct()`

**描述**: 获取产品代号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 产品代号 |

示例:
```lua
print(getProduct())
```

---

## 34. 获取设备别名 (`getDevice`)
**函数**: `getDevice()`

**描述**: 获取设备别名。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 设备别名 |

示例:
```lua
print(getDevice())
```

---

## 35. 获取设备型号 (`getModel`)
**函数**: `getModel()`

**描述**: 获取设备型号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 设备型号 |

示例:
```lua
print(getModel())
```

---

## 36. 获取硬件序列号 (`getHardware`)
**函数**: `getHardware()`

**描述**: 获取硬件序列号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 硬件序列号 |

示例:
```lua
print(getHardware())
```

---

## 37. 获取 id 修订号 (`getId`)
**函数**: `getId()`

**描述**: 获取 id 修订号。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | id 修订号 |

示例:
```lua
print(getId())
```

---

## 38. 获取编译指纹 (`getFingerprint`)
**函数**: `getFingerprint()`

**描述**: 获取编译指纹（fingerprint）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 编译指纹 |

示例:
```lua
print(getFingerprint())
```

---

## 39. 获取 CPU 支持类型 (`getCpuAbi` / `getCpuAbi2`)
**函数**: `getCpuAbi()` / `getCpuAbi2()`

**描述**: 获取 CPU 支持类型。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | CPU 支持类型 |

示例:
```lua
print(getCpuAbi())
print(getCpuAbi2())
```

---

## 40. 获取 SDK 版本 (`getSdkVersion`)
**函数**: `getSdkVersion()`

**描述**: 获取 SDK 版本。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | SDK 版本 |

示例:
```lua
print(getSdkVersion())
```

---

## 41. 获取系统版本名 (`getOsVersionName`)
**函数**: `getOsVersionName()`

**描述**: 获取系统版本名。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 系统版本名 |

示例:
```lua
print(getOsVersionName())
```

---

## 42. 获取 WiFi MAC 地址 (`getWifiMac`)
**函数**: `getWifiMac()`

**描述**: 获取 WiFi MAC 地址。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | WiFi MAC 地址 |

示例:
```lua
print(getWifiMac())
```

---

## 43. 打开指定应用 (`runApp`)
**函数**: `runApp(package_name, [component_name], [is_open_by_super])`

**描述**: 打开指定应用，可传组件名或用最高权限打开。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| package_name | 字符串 | 是 | 应用包名 |
| component_name | 字符串 | 否 | 组件名 |
| is_open_by_super | 布尔 | 否 | 是否用最高权限打开 |

返回值: 无

示例:
```lua
runApp("com.tencent.mm")
```

---

## 44. 关闭指定应用 (`stopApp`)
**函数**: `stopApp(package_name)`

**描述**: 关闭指定应用。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| package_name | 字符串 | 是 | 应用包名 |

返回值: 无

示例:
```lua
stopApp("com.tencent.mm")
```

---

## 45. 刷新图片到媒体库 (`scanImage`)
**函数**: `scanImage(imagepath)`

**描述**: 刷新图片到媒体库（图库）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| imagepath | 字符串 | 是 | 图片文件路径 |

返回值: 无

示例:
```lua
scanImage("/sdcard/test.png")
```

---

## 46. 获取最顶层 Activity 名称 (`getCurrentActivity`)
**函数**: `getCurrentActivity()`

**描述**: 获取最顶层 Activity 名称（需节点或无障碍权限）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 最顶层 Activity 名称 |

示例:
```lua
local activity = getCurrentActivity()
print(activity)
```

---

## 47. 获取前台应用包名 (`frontAppName`)
**函数**: `frontAppName()`

**描述**: 获取前台应用包名。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 前台应用包名 |

示例:
```lua
print(frontAppName())
```

---

## 48. 判断指定包名是否为前台运行 (`appIsFront`)
**函数**: `appIsFront(package_name)`

**描述**: 判断指定包名是否为前台运行。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| package_name | 字符串 | 是 | 应用包名 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 布尔 | true 表示前台运行，false 表示非前台运行 |

示例:
```lua
if not appIsFront("com.tencent.mm") then
  runApp("com.tencent.mm")
end
```

---

## 49. 暂停/恢复主线程运行 (`setMainThreadPause` / `setMainThreadResume`)
**函数**: `setMainThreadPause()` / `setMainThreadResume()`

**描述**: 在回调中暂停/恢复主线程运行（用于协同逻辑）。

参数: 无

返回值: 无

示例:
```lua
function cb()
  sleep(3000)
  setMainThreadPause()
  sleep(3000)
  setMainThreadResume()
end
beginThread(cb)
```

---

## 50. 读写剪贴板内容 (`readPasteboard` / `writePasteboard`)
**函数**: `readPasteboard()` / `writePasteboard(str)`

**描述**: 读写剪贴板内容。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| str | 字符串 | 否 | 要写入剪贴板的内容（仅 `writePasteboard` 使用） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 剪贴板内容（仅 `readPasteboard` 返回） |

示例:
```lua
writePasteboard("123")
print(readPasteboard())
```

---

## 51. 判断 app 是否正在运行 (`appIsRunning`)
**函数**: `appIsRunning(package_name)`

**描述**: 判断 app 是否正在运行。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| package_name | 字符串 | 是 | 应用包名 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 布尔 | true 表示正在运行，false 表示未运行 |

示例:
```lua
if not appIsRunning("com.tencent.mm") then runApp("com.tencent.mm") end
```

---

## 52. 生成随机整数 (`rnd`)
**函数**: `rnd(begin,end)`

**描述**: 生成指定范围的随机整数（包含端点）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| begin | 整数 | 是 | 范围起始值 |
| end | 整数 | 是 | 范围结束值 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 指定范围内的随机整数 |

示例:
```lua
print(rnd(-5,5))
```

---

## 53. 以最高权限执行命令 (`exec`)
**函数**: `exec(cmd, [isRet])`

**描述**: 以最高权限执行命令（root/激活权限）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cmd | 字符串 | 是 | 要执行的命令 |
| isRet | 布尔 | 否 | 是否返回执行结果 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串或 nil | 命令执行结果（当 isRet 为 true 时返回） |

示例:
```lua
local r = exec("ls /")
print(r)
```

---

## 54. 构建并发送 Intent (`runIntent`)
**函数**: `runIntent(intent)`

**描述**: 以表格形式构建并发送 Intent（部分手机需要允许后台弹窗）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| intent | 表 | 是 | Intent 配置表，包含 action、uri、extra 等字段 |

返回值: 无

示例:
```lua
i = { action = "android.intent.action.VIEW", uri = "http://www.baidu.com", extra = { data = "hello" } }
runIntent(i)
```

---

## 55. 发送短信 (`sendSms`)
**函数**: `sendSms(number, content)`

**描述**: 发送短信。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| number | 字符串 | 是 | 目标电话号码 |
| content | 字符串 | 是 | 短信内容 |

返回值: 无

示例:
```lua
sendSms("10086", "测试短信")
```

---

## 56. 拨号或直接打出电话 (`phoneCall`)
**函数**: `phoneCall(number, state)`

**描述**: 拨号或直接打出电话（state=0 拨号，其他直接打出）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| number | 字符串 | 是 | 目标电话号码 |
| state | 整数 | 是 | 0 表示拨号，其他值表示直接打出 |

返回值: 无

示例:
```lua
phoneCall("10086", 1)
```

---

## 57. 获取屏幕分辨率 (`getDisplaySize`)
**函数**: `getDisplaySize()`

**描述**: 获取屏幕分辨率（宽、高）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数, 整数 | 屏幕宽度和高度 |

示例:
```lua
local w,h = getDisplaySize()
print(w,h)
```

---

## 58. 设置息屏运行 (`setDisplayPowerOff`)
**函数**: `setDisplayPowerOff(isPoweroff)`

**描述**: 设置息屏运行（需要 root 或激活权限）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| isPoweroff | 布尔 | 是 | true 表示息屏，false 表示亮屏 |

返回值: 无

示例:
```lua
setDisplayPowerOff(true)
sleep(10000)
setDisplayPowerOff(false)
```

---

## 59. 切换虚拟分辨率/恢复真实分辨率 (`setDpiToVir` / `setDpiToRealy`)
**函数**: `setDpiToVir(dpi)` / `setDpiToRealy()`

**描述**: 切换虚拟分辨率/恢复真实分辨率（需打包并赋予权限）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| dpi | 整数 | 否 | 虚拟分辨率值（仅 `setDpiToVir` 使用） |

返回值: 无

示例:
```lua
setDpiToVir(240)
setDpiToRealy()
```

---

## 60. 关闭或开启日志输出 (`setLogOff`)
**函数**: `setLogOff(iscloselog)`

**描述**: 关闭或开启日志输出。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| iscloselog | 布尔 | 是 | true 表示关闭日志，false 表示开启日志 |

返回值: 无

示例:
```lua
setLogOff(true)
```

---

## 61. 获取屏幕旋转方向 (`getDisplayRotate`)
**函数**: `getDisplayRotate()`

**描述**: 获取屏幕旋转方向（0/1/2/3）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 屏幕旋转方向（0/1/2/3） |

示例:
```lua
print(getDisplayRotate())
```

---

## 62. 释放资源到目录 (`extractAssets` / `extractApkAssets`)
**函数**: `extractAssets(assets, outdir, pattern)` / `extractApkAssets(res, outdir)`

**描述**: 将打包资源或指定资源释放到目录，支持文件名或通配符。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| assets | 字符串 | 是 | 资源文件名（仅 `extractAssets` 使用） |
| outdir | 字符串 | 是 | 输出目录路径 |
| pattern | 字符串 | 否 | 通配符模式（仅 `extractAssets` 使用） |
| res | 字符串 | 是 | 资源文件名（仅 `extractApkAssets` 使用） |

返回值: 无

示例:
```lua
extractAssets("test.rc", "/mnt/sdcard/", "*.bmp")
extractApkAssets("test.txt", "/mnt/sdcard/")
```

---

## 63. 压缩/解压文件或文件夹 (`zip` / `unZip`)
**函数**: `zip(file, zippath)` / `unZip(zippath, outdir, pass, charset)`

**描述**: 压缩/解压文件或文件夹。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| file | 字符串 | 是 | 要压缩的文件或文件夹路径（仅 `zip` 使用） |
| zippath | 字符串 | 是 | 压缩文件路径 |
| outdir | 字符串 | 是 | 解压输出目录（仅 `unZip` 使用） |
| pass | 字符串 | 否 | 解压密码（仅 `unZip` 使用） |
| charset | 字符串 | 否 | 字符集（仅 `unZip` 使用） |

返回值: 无

示例:
```lua
zip("/sdcard/test.png", "/mnt/sdcard/test.zip")
unZip("/sdcard/test.zip", "/mnt/sdcard/mydir")
```

---

## 64. 定时执行指定函数 (`setTimer`)
**函数**: `setTimer(function, time, arg, ...)`

**描述**: 定时执行指定函数（毫秒）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| function | 函数 | 是 | 要执行的回调函数 |
| time | 整数 | 是 | 时间间隔，单位毫秒 |
| arg, ... | 任意类型 | 否 | 传递给回调函数的参数 |

返回值: 无

示例:
```lua
function callback(a,b)
  print(a,b)
  setTimer(callback, 1000, a, b)
end
setTimer(callback, 1000, 1, 2)
```

---

## 65. 打开或关闭蓝牙/WiFi/飞行模式 (`setBTEnable` / `setWifiEnable` / `setAirplaneMode`)
**函数**: `setBTEnable(state)` / `setWifiEnable(state)` / `setAirplaneMode(state)`

**描述**: 打开或关闭蓝牙/WiFi/飞行模式（state=true/false）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| state | 布尔 | 是 | true 表示打开，false 表示关闭 |

返回值: 无

示例:
```lua
setBTEnable(true)
setWifiEnable(true)
setAirplaneMode(true)
```

---

## 66. 线程休眠 (`sleep`)
**函数**: `sleep(time)`

**描述**: 线程休眠（毫秒）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| time | 整数 | 是 | 休眠时间，单位毫秒 |

返回值: 无

示例:
```lua
sleep(5000)
```

---

## 67. 调试输出 (`print` / `printEx`)
**函数**: `print(...)` / `printEx(str)`

**描述**: 调试输出（`printEx` 为原生标准输出）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| ... | 任意类型 | 否 | 要输出的内容（仅 `print` 使用） |
| str | 字符串 | 是 | 要输出的内容（仅 `printEx` 使用） |

返回值: 无

示例:
```lua
print("hello world")
printEx("hello world")
```

---

## 68. 保持屏幕常亮或释放常亮状态 (`lockScreen` / `unLockScreen`)
**函数**: `lockScreen()` / `unLockScreen()`

**描述**: 保持屏幕常亮或释放常亮状态。

参数: 无

返回值: 无

示例:
```lua
lockScreen()
sleep(10000)
unLockScreen()
```

---

## 69. 设置悬浮按钮菜单自定义事件回调 (`setUserEventCallBack`)
**函数**: `setUserEventCallBack(cb)`

**描述**: 设置悬浮按钮菜单自定义事件回调（新版悬浮菜单支持）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cb | 函数 | 是 | 自定义事件回调函数 |

返回值: 无

示例:
```lua
setUserEventCallBack(function(type)
  toast("用户事件",0,0,30)
end)
```

---

## 70. Java 层设置脚本结束回调 (`LuaEngine.registerExitCallback`)
**函数**: `LuaEngine.registerExitCallback(cb)`

**描述**: Java 层设置脚本结束回调。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cb | 函数 | 是 | 脚本结束回调函数 |

返回值: 无

示例: 请参考 symbol.xml 中的 Java/FFI 示例。

---

## 71. 插件事件接口 (`setPluginEventCallBack` / `sendPluginEvent`)
**函数**: `setPluginEventCallBack(cb)` / `sendPluginEvent(what, arg)`

**描述**: 插件事件接口，插件通过 PluginService 发送自定义数据。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cb | 函数 | 是 | 插件事件回调函数（仅 `setPluginEventCallBack` 使用） |
| what | 整数 | 是 | 事件类型（仅 `sendPluginEvent` 使用） |
| arg | 任意类型 | 是 | 事件参数（仅 `sendPluginEvent` 使用） |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 字符串 | 插件回调函数的返回值（仅 `setPluginEventCallBack` 返回） |

示例:
```lua
function onPluginEvent(e,arg)
  print("插件发送过来的数据:",e,arg)
  return "返回给插件结果"
end
setPluginEventCallBack(onPluginEvent)
```

---

## 72. 设置系统通知事件回调 (`setNotifyEventCallBack`)
**函数**: `setNotifyEventCallBack(cb)`

**描述**: 设置系统通知事件回调（回调接收类型和结果）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cb | 函数 | 是 | 系统通知事件回调函数 |

返回值: 无

示例: 请参考 symbol.xml 中的示例（包含 Android Toast 演示）。

---

## 73. 设置截图缓存图片或缓存时长 (`LuaEngine.setSnapCacheBitmap` / `setSnapCacheTime`)
**函数**: `LuaEngine.setSnapCacheBitmap(bmp)` / `setSnapCacheTime(time)`

**描述**: 设置截图缓存图片或缓存时长以加速图色相关操作。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| bmp | userdata | 是 | 截图缓存图片（仅 `LuaEngine.setSnapCacheBitmap` 使用） |
| time | 整数 | 是 | 缓存时长（仅 `setSnapCacheTime` 使用） |

返回值: 无

示例:
```lua
local bmp = LuaEngine.snapShot(0,0,0,0)
LuaEngine.setSnapCacheBitmap(bmp)
LuaEngine.setSnapCacheBitmap(nil)
LuaEngine.releaseBmp(bmp)
```

---

## 74. 设置脚本结束回调 (`setStopCallBack`)
**函数**: `setStopCallBack(cb)`

**描述**: 设置脚本结束回调（回调内不宜执行 UI 显示操作）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| cb | 函数 | 是 | 脚本结束回调函数 |

返回值: 无

示例:
```lua
setStopCallBack(function(error, exitcode)
  if error then print("异常结束") else print("正常结束") end
end)
```

---

## 75. 捕获错误并调用自定义错误处理函数 (`xpcall`)
**函数**: `xpcall(func, errHandler)`

**描述**: 捕获错误并调用自定义错误处理函数，返回 [成功, 返回值/错误]。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| func | 函数 | 是 | 要执行的函数 |
| errHandler | 函数 | 是 | 错误处理函数 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 布尔, 任意类型 | 第一个返回值为 true 表示执行成功，false 表示执行失败；第二个返回值为函数返回值或错误信息 |

示例:
```lua
local ok, res = xpcall(function() error("err") end, function(e) print(e) end)
```

---

## 76. 停止脚本运行 (`exitScript`)
**函数**: `exitScript()`

**描述**: 停止脚本运行。

参数: 无

返回值: 无

示例:
```lua
exitScript()
```

---

## 77. 获取运行环境类型 (`getRunEnvType`)
**函数**: `getRunEnvType()`

**描述**: 获取运行环境类型（0=root/激活，1=无障碍）。

参数: 无

返回值:

| 返回值类型 | 说明 |
|:---:|:---|
| 整数 | 运行环境类型（0=root/激活，1=无障碍） |

示例:
```lua
local r = getRunEnvType()
print(r)
```

---

## 78. 设置脚本引擎的运行模式 (`setRootEnvMode` / `setHandleEnvMode` / `setAccessibilityEnvMode`)
**函数**: `setRootEnvMode(mode)` / `setHandleEnvMode()` / `setAccessibilityEnvMode()`

**描述**: 设置脚本引擎的运行模式（设置后需重启脚本生效）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---|
| mode | 布尔 | 是 | 是否启用 root 模式（仅 `setRootEnvMode` 使用） |

返回值: 无

示例:
```lua
setRootEnvMode(true)
restartScript()
``` 
