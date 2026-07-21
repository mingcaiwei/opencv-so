# 扩展方法 (extension)

## 1. 加载java类 (import)
**函数:** `import(className)`  
**描述:** 此方法是为了能更加方便扩展安卓原生调用，具体详细的使用例子请进群下载，此方法只支持android端，后续ios端不支持此方法。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| className| string | 是   | 字符串类型,表示一个java类名     |  

示例:  
```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')

print(Math.sin(1.2))

print(System.currentTimeMillis())

local headers = {}
headers["User-Agent"]
= "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.3) Gecko/2008092417 Firefox/3.0.3"

local getRet = LuaEngine.httpGet("https://www.baidu.com",headers)
print(getRet)

local ctx = LuaEngine.getContext()
local tmgr = ctx.getSystemService(Context.TELEPHONY_SERVICE)
local imei = tmgr.getImei(0)
local devId = tmgr.getDeviceId()
print(imei,devId)
```

## 2. 加载一个apk插件 (LuaEngine.loadApk)
**函数:** `LuaEngine.loadApk(name)`  
**描述:** 加载一个apk插件，此函数还可以加载autojs的插件。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| name     | string | 是   | 字符串类型，如果apk插件放到资源中则只需要写名字，如果需要从sd卡加载则这里写绝对路径     |  

示例:  
```lua
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('android.hardware.Sensor')
import('android.hardware.SensorEvent')
import('android.hardware.SensorEventListener')
import('android.hardware.SensorManager')
import('com.nx.assist.lua.LuaEngine')

--[===[LuaEngine.loadApk 参数如果是名称则使用资源文件否则使用绝对路径]===]
local loader = LuaEngine.loadApk("app-release.apk")
printEx(loader)
if loader ~= nil then
    local plugin = loader.loadClass("com.lrapp.plugin.Plugin")
    if plugin ~= nil then
        local c = plugin.add(1,2)
        print(c)
    end
end
```

## 3. 获取android上下文对象 (LuaEngine.getContext)
**函数:** `LuaEngine.getContext()`  
**描述:** 获取android上下文对象。  

 
示例:  
```lua
import('java.io.File')
import('java.lang.*')
import('java.util.Arrays')
import('android.content.Context')
import('android.hardware.Sensor')
import('android.hardware.SensorEvent')
import('android.hardware.SensorEventListener')
import('android.hardware.SensorManager')
import('com.nx.assist.lua.LuaEngine')

local ctx = LuaEngine.getContext()

print(ctx.getPackageName())
```

## 4. 连接mysql数据库 (connectSQL)
**函数:** `mysql.connectSQL(host,port,database,user,password,timeout)`  
**描述:** 连接mysql数据库。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| host     | string | 是   | MYSQL服务器地址     |  
| port     | number | 是   | MYSQL服务端口号     |  
| database | string | 是   | 要访问的数据库名称     |  
| user     | string | 否   | 访问数据库的账号名称（如果没有不用填写）     |  
| password | string | 否   | 访问数据库密码（如果没有不用填写）     |  
| timeout  | number | 是   | 超时时长，单位是毫秒     |  

示例:  
```lua
require("mysql")

local con,err = mysql.connectSQL("192.168.1.24",3306,"mydatabase","root","mtest@123",20000)

if con ~= nil then
    local sql = string.format("insert persons(name,height,age) values('%s',%d,%d)","Limi",197,23)
    local r,err = mysql.executeSQL(con,sql)
    if err ~= nil then
        print("执行错误:"..err)
    end
    local rs,err = mysql.executeQuerySQL(con,"select * from persons")
    if err ~= nil then
        print("执行错误:"..err)
    end
    print(rs,err)
    mysql.closeSQL(con)
else
    print("连接失败:"..err)
end
```

## 5. 关闭数据库连接 (closeSQL)
**函数:** `mysql.closeSQL(handle)`  
**描述:** 关闭数据库连接。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| handle   | object | 是   | 由mysql.connectSQL返回的连接对象     |  

示例:  
```lua
require("mysql")

local con,err = mysql.connectSQL("192.168.1.24",3306,"mydatabase","root","mtest@123",20000)

if con ~= nil then
    local sql = string.format("insert persons(name,height,age) values('%s',%d,%d)","Limi",197,23)
    local r,err = mysql.executeSQL(con,sql)
    if err ~= nil then
        print("执行错误:"..err)
    end
    local rs,err = mysql.executeQuerySQL(con,"select * from persons")
    if err ~= nil then
        print("执行错误:"..err)
    end
    print(rs,err)
    mysql.closeSQL(con)
else
    print("连接失败:"..err)
end
```

## 6. 执行sql语句并返回结果 (executeQuerySQL)
**函数:** `mysql.executeQuerySQL(handle,sql)`  
**描述:** 执行sql语句并返回结果。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| handle   | object | 是   | 由mysql_connect返回的连接对象     |  
| sql      | string | 是   | sql语句，请参考sql语法     |  

示例:  
```lua
require("mysql")

local con,err = mysql.connectSQL("192.168.1.24",3306,"mydatabase","root","mtest@123",20000)

if con ~= nil then
    local sql = string.format("insert persons(name,height,age) values('%s',%d,%d)","Limi",197,23)
    local r,err = mysql.executeSQL(con,sql)
    if err ~= nil then
        print("执行错误:"..err)
    end
    local rs,err = mysql.executeQuerySQL(con,"select * from persons")
    if err ~= nil then
        print("执行错误:"..err)
    end
    print(rs,err)
    mysql.closeSQL(con)
else
    print("连接失败:"..err)
end
```

## 7. 执行sql语句 (executeSQL)
**函数:** `mysql.executeSQL(handle,sql)`  
**描述:** 执行sql语句。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| handle   | object | 是   | 由mysql_connect返回的连接对象     |  
| sql      | string | 是   | sql语句，请参考sql语法     |  

示例:  
```lua
require("mysql")

local con,err = mysql.connectSQL("192.168.1.24",3306,"mydatabase","root","mtest@123",20000)

if con ~= nil then
    local sql = string.format("insert persons(name,height,age) values('%s',%d,%d)","Limi",197,23)
    local r,err = mysql.executeSQL(con,sql)
    if err ~= nil then
        print("执行错误:"..err)
    end
    local rs,err = mysql.executeQuerySQL(con,"select * from persons")
    if err ~= nil then
        print("执行错误:"..err)
    end
    print(rs,err)
    mysql.closeSQL(con)
else
    print("连接失败:"..err)
end
```

## 8. 启动一个线程 (beginThread)
**函数:** `beginThread(callback,...)`  
**描述:** 启动一个新的线程，注意新线程无法使用exitScript 和 restartScript，但是可以通过setTimer向主线程发送一个回调方法中去退出或者重启脚本，为了稳定性同时创建的线程最大并发数不能超过10个。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| callback | function | 是   | 线程回调方法     |  
| ...      | any    | 否   | 可变参数     |  

示例:  
```lua
local var = {
    exit = true,
    data = 0,
}

function thread_func(arg)
    while var.exit do
        print("我是子线程:"..arg.." 共享数据:"..var.data)
        sleep(100)
    end
end


for i=1,5 do --同时可运行线程数不能超过10个
    beginThread(thread_func,i)
end


for i=1,10 do
    local tick = 10 - i
    var.data = tick
    toast("倒计时【"..tick.."】秒后结束线程",0,0,20)
    sleep(1000)
end


var.exit = false
toast("线程结束",0,0,20)
sleep(100000)
```

## 9. 启动一个线程 (newThread)
**函数:** `Thread.newThread(callback,...)`  
**描述:** 启动一个新的线程。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| callback | function | 是   | 线程回调方法     |  
| ...      | any    | 否   | 可变参数     |  

示例:  
```lua
function thread_func(arg)
    while var.exit do
        print("我是子线程")
        sleep(1000)
    end
end


local thread = Thread.newThread(thread_func,11)
sleep(3000)
thread:stopThread()
```

## 10. 停止线程 (th.stopThread)
**函数:** `thread:stopThread()`  
**描述:** 停止线程。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  

示例:  
```lua
function thread_func(arg)
while var.exit do
print("我是子线程")
sleep(1000)
end
end


local thread = Thread.newThread(thread_func,11)
sleep(3000)
thread:stopThread()
```

## 11. 二维码解析 (qrDecode)
**函数:** `qrDecode(pngpath)`  
**描述:** 二维码解析。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| pngpath  | string | 是   | 需要解析的二维码路径     |  

示例:  
```lua
local ret,text = qrDecode("/mnt/sdcard/qq.png")
if ret == 1 then
    print("text:"..text)
end
```

## 12. 字符串的MD5 (MD5)
**函数:** `MD5(str)`  
**描述:** 获取字符串的MD5码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| str      | string | 是   | 要MD5编码的字符串     |  
 
示例:  
```lua
local ret = MD5("123");
print(ret)
```

## 13. 获取文件的MD5码 (fileMD5)
**函数:** `fileMD5(filepath)`  
**描述:** 获取文件的MD5码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| filepath | string | 是   | 要MD5编码的文件绝对路径     |  
 
示例:  
```lua
local ret = fileMD5("/mnt/sdcard/test.png");
print(ret)
```

## 14. 获取文件base64编码 (getFileBase64)
**函数:** `getFileBase64(filepath)`  
**描述:** 获取文件内容的base64编码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| filepath | string | 是   | 文件的绝对路径     |  

示例:  
```lua
local path = "/mnt/sdcard/test.png"
snapShot(path)
local e = getFileBase64(path)
print("filebase64 ret:",e)
```

## 15. base64编码 (encodeBase64)
**函数:** `encodeBase64(str)`  
**描述:** 字符串base64编码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| str      | string | 是   | 待编码的字符串     |  
  
 
示例:  
```lua
local ret = encodeBase64("欢迎使用懒人精灵")
print("encode:",ret)
```

## 16. base64解码 (decodeBase64)
**函数:** `decodeBase64(str)`  
**描述:** base64字符串解码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| str      | string | 是   | 待解码的base64字符串     |  

示例:  
```lua
local ret = encodeBase64("欢迎使用懒人精灵")
print("encode:",ret)
local dec = decodeBase64(ret)
print("decode:",dec)
```

## 17. url格式解码 (decodeUrl)
**函数:** `decodeUrl(str)`  
**描述:** decodeUrl url格式解码。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| str      | string | 是   | 待解码的url字符串     |  
 
示例:  
```lua
local r = encodeUrl("欢迎使用懒人精灵")
print("encode url:",r)
local d = decodeUrl(r)
print("decode:",d)
```

## 18. url格式编码 (encodeUrl)
**函数:** `encodeUrl(str)`  
**描述:** encodeUrl 格式编码为url格式。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| str      | string | 是   | 待编码为url的字符串     |  


示例:  
```lua
local ret = encodeUrl("欢迎使用懒人精灵")
print("encodeUrl:",ret)
```

## 19. 百度ocr (bdOcr)
**函数:** `bdOcr(url,apikey,secretkey,...)`  
**描述:** bdOcr 百度ocr。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| url      | string | 是   | 可以是网络图片也可以是本地图片     |  
| apikey   | string | 是   | 需要自己在百度进行申请     |  
| secretkey| string | 是   | 需要自己在百度进行申请     |  
| type     | number | 否   | 可以取值0,1,2,3 ,0:通用文字识别 1:通用文字识别（含位置信息版）,2:通用文字识别（高精度版）,3:通用文字识别（高精度含位置版）     |  

示例:  
```lua
local path = "/mnt/sdcard/test.png"
snapShot(path,66,119,248,186)
local ret = bdOcr(path,"Yub8co6xdEfmMHykqg38GXhB","Hyhbsc1yGf78E65ETcn1wZvPV2lnKXwZ")
print("bdocr:",ret)
```

## 20. 获取本地图片数据 (getImage)
**函数:** `getImage(path)`  
**描述:** readFile 读取本地图片数据图片类型可以是png bmp jpg。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件的路径     |  


示例:  
```lua
local path = "/mnt/sdcard/test.png"
local w,h,t = getImage(path)
print("image:",w,h,#t)
```

## 21. 旋转本地图片 (rotateImage)
**函数:** `rotateImage(path,rotate)`  
**描述:** rotateImage 旋转本地图片,图片格式可以是png bmp jpg三种类型。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件的路径     |  
| rotate   | number | 是   | 可以是90 180 270三种值，此处为顺时针旋转     |  


示例:  
```lua
local path = "/mnt/sdcard/test.png"
local ret = rotateImage(path,90)
print("rotateImage ret:",ret)
```

## 22. 缩放图片 (scaleImage)
**函数:** `scaleImage(src,dst,w,h)`  
**描述:** scaleImage 缩放图片,图片格式可以是png bmp jpg三种类型。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| src      | string | 是   | 原始路径     |  
| dst      | string | 是   | 目标路径     |  
| w        | number | 是   | 生成图片宽度     |  
| h        | number | 是   | 生成图片高度     |  


示例:  
```lua
local src = "/mnt/sdcard/src.png"
local dst = "/mnt/sdcard/dst.jpg"
snapShot(path)
local ret = scaleImage(path,dst,200,300)
print("scaleImage ret:",ret)
```

## 23. 二值化本地图片 (binaryImage)
**函数:** `binaryImage(srcimage,dstimage,...)`  
**描述:** binaryImage二值化本地图片,图片格式可以是png bmp jpg三种类型。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| srcimage | string | 是   | 源图片     |  
| dstimage | string | 是   | 生成后的二值化图片     |  
| ThresholdTypes | number | 否   | 整数型,(THRESH_BINARY = 0,THRESH_BINARY_INV = 1,THRESH_TRUNC = 2,THRESH_TOZERO = 3,THRESH_TOZERO_INV = 4,THRESH_MASK = 7,THRESH_OTSU = 8,THRESH_TRIANGLE = 16)具体含义请查看opencv文档，默认不写是8(THRESH_OTSU)     |  
| thresh   | number | 否   | 整数型，阈值默认不写是150     |  
| maxthresh| number | 否   | 整数型，最大阈值，默认不写255     |  

示例:  
```lua
local path = "/mnt/sdcard/test.png"
local save = "/mnt/sdcard/save.png"
snapShot(path,200,211,350,330,8,150,255)
local ret = binaryImage(path,save)
if ret == 1 then
    local id = createHUD()
    showHUD(id,"HelloWorld!",12,"0xffff0000",save,0,100,100,200,200)
else
    print("binaryimage failed")
end
sleep(100000)
```

## 24. 区域截图并二值化 (binaryRect)
**函数:** `binaryRect(save,l,t,r,b,...)`  
**描述:** binaryRect 区域截图二值化,保存的图片格式可以是png bmp jpg三种类型。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| save     | string | 是   | 最终生成的图片     |  
| l        | number | 是   | 区域范围左坐标     |  
| t        | number | 是   | 区域范围上坐标     |  
| r        | number | 是   | 区域范围右坐标     |  
| b        | number | 是   | 区域范围下坐标     |  
| ThresholdTypes | number | 否   | 整数型,(THRESH_BINARY = 0,THRESH_BINARY_INV = 1,THRESH_TRUNC = 2,THRESH_TOZERO = 3,THRESH_TOZERO_INV = 4,THRESH_MASK = 7,THRESH_OTSU = 8,THRESH_TRIANGLE = 16)具体含义请查看opencv文档，默认不写是8(THRESH_OTSU)     |  
| thresh   | number | 否   | 整数型，阈值默认不写是150     |  
| maxthresh| number | 否   | 整数型，最大阈值，默认不写255     |  

示例:  
```lua
local path = "/mnt/sdcard/test.png"
local ret = binaryRect(path,199,208,353,328,8,150,255)
if ret == 1 then
    local id = createHUD()
    showHUD(id,"HelloWorld!",12,"0xffff0000",path,0,100,100,200,200)
end
sleep(100000)
```

## 25. 文件或文件夹是否存在 (fileExist)
**函数:** `fileExist(file)`  
**描述:** fileExist 文件是否存在。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| file     | string | 是   | 文件绝对路径     |  

示例:  
```lua
local path = "/mnt/sdcard/test.png"
print(fileExist(path))
sleep(100000)
```

## 26. 创建文件夹 (mkdir)
**函数:** `mkdir(dir)`  
**描述:** mkdir 创建文件夹。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| dir      | string | 是   | 文件夹绝对路径     |  

示例:  
```lua
local path = "/mnt/sdcard/lr"
print(mkdir(path))
sleep(100000)
```

## 27. 删除文件或文件夹 (delfile)
**函数:** `delfile(path)`  
**描述:** delfile 删除文件或文件夹。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件夹绝对路径     |  

示例:  
```lua
local path = "/sdcard/test.txt"

writeFile(path,"hello")

if fileExist(path) then
    print(path.." 存在了")
    delfile(path)
end

if fileExist(path) == false then
    print(path.." 不存在了")
end
sleep(100000)
```

## 28. 读取文件所有内容 (readFile)
**函数:** `readFile(path)`  
**描述:** readFile 读取文件所有内容。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件绝对路径或者主资源文件中的文件名     |  
 
示例:  
```lua
local path = getSdPath().."/data.txt"
local ret = readFile(path)
print(ret)
```

## 29. 写字符串到文件 (writeFile)
**函数:** `writeFile(path,str,...)`  
**描述:** writeFile 写字符串到文件。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件绝对路径     |  
| str      | string | 是   | 要输入的字符串内容     |  
| append   | boolean | 否   | 是否追加     |  

示例:  
```lua
local path = getSdPath().."/data.txt"
local ret = writeFile(path,"hello\n",true)
print(ret)
```

## 30. 获取文件大小 (fileSize)
**函数:** `fileSize(path)`  
**描述:** fileSize 获取文件大小。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | string | 是   | 文件绝对路径     |  

示例:  
```lua
local path = getSdPath().."/data.txt"
local ret = fileSize(path)
print(ret)
```

## 31. 检测无障碍服务是否开启了 (nodeLib.isAccServiceOk)
**函数:** `nodeLib.isAccServiceOk()`  
**描述:** nodeLib.isAccServiceOk 检测无障碍服务是否开启了。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  

示例:  
```lua
local r = nodeLib.isAccServiceOk()
if r then
    print("无障碍服务已经开启")
else
    print("无障碍服务没有开启")
end
```

## 32. 打开截图服务 (nodeLib.openSnapService)
**函数:** `nodeLib.openSnapService()`  
**描述:** nodeLib.openSnapService 打开截图服务(这个方法一般用于手动模式，调用这方法会弹出允许截图窗口需要手动完成点击确认)。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  

示例:  
```lua
local r = nodeLib.openSnapService()
if r then
    if nodeLib.isAccServiceOk() == false then
        r = false
    end
end
if r then
    print("截图服务开启成功")
else
    print("截图服务开启失败")
end
```

## 33. 检测截图服务是否开启 (nodeLib.isSnapServiceOk)
**函数:** `nodeLib.isSnapServiceOk()`  
**描述:** nodeLib.isSnapServiceOk 检测截图服务是否开启(如果是root或者激活模式不需要用这个去检测，因为使用的截图方法不一样)。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  

示例:  
```lua
local r = nodeLib.isAccServiceOk()
if r then
    print("截图服务已经开启")
else
    print("截图服务没有开启")
end
```

## 34. 获取指定节点的下一个兄弟节点 (nodeLib.findNextNode)
**函数:** `nodeLib.findNextNode(selector,fuzzy_match)`  
**描述:** nodeLib.findNextNode 获取指定节点的下一个兄弟节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findNextNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},true)
if ret ~= nil then
    print(ret)
end
```

## 35. 获取指定节点的上一个兄弟节点 (nodeLib.findPreNode)
**函数:** `nodeLib.findPreNode(selector,fuzzy_match)`  
**描述:** nodeLib.findPreNode 获取指定节点的上一个兄弟节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  
 
示例:  
```lua
local ret = nodeLib.findPreNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
    print(ret)
end
```

## 36. 在指定节点中查找符合要求的子节点 (nodeLib.findInNode)
**函数:** `nodeLib.findInNode(src,dst,isfindall,fuzzy_match)`  
**描述:** nodeLib.findOne 查找出一个节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| src      | table | 是   | 要被查找的节点对象     |  
| dst      | table | 是   | 要查找的节点对象     |  
| isfindall | boolean | 是   | 是否查找并返回所有符合要求的节点，true返回所有，false找到一个就返回     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.FrameLayout",id="com.nx.nxproj.assist:id/title"},true)
if ret ~= nil then
    local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
    print(ret)
    if r~= nil then
        for i=1,#r do
            print(r[i])
        end
    end
end
```

## 37. 查找出一个节点 (nodeLib.findOne)
**函数:** `nodeLib.findOne(selector,fuzzy_match)`  
**描述:** nodeLib.findOne 查找出一个节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.RelativeLayout"},true)
if ret ~= nil then
    local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
    if r ~= nil then
        for i=1,#r do
            print(r[i])
        end
    end
end
```

## 38. 查找所有满足要求的节点 (nodeLib.findAll)
**函数:** `nodeLib.findAll(selector,fuzzy_match)`  
**描述:** nodeLib.findAll 查找所有满足要求的节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findAll({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
    print(ret)
end
```

## 39. 查找一个节点的所有子节点 (nodeLib.findChildNodes)
**函数:** `nodeLib.findChildNodes(selector,fuzzy_match)`  
**描述:** nodeLib.findChildNodes 查找所有满足要求的节点的所有子节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findChildNodes({class="android.widget.RelativeLayout",id="com.android.flysilkworm:id/main_banner_view"},false)
if ret ~= nil then
    for i = 1,#ret do
        print(ret[i])
    end
end
```

## 40. 查找出一个节点的父节点 (nodeLib.findParentNode)
**函数:** `nodeLib.findParentNode(selector,fuzzy_match)`  
**描述:** nodeLib.findParentNode 查找出一个节点的父节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| selector | table | 是   | 是一个表格,里面的键值对通过节点工具勾选直接生成     |  
| fuzzy_match | boolean | 是   | true表示使用正则匹配去查询，false表示完全匹配     |  

示例:  
```lua
local ret = nodeLib.findParentNode({class="android.widget.TextView",id="",package="com.nx.nxproj",text="名称: tmp.lr"},false)
if ret ~= nil then
    print(ret)
end
```

## 41. 根据节点所在树的每个分支顺序查找 (nodeLib.findByIndex)
**函数:** `nodeLib.findByIndex(indexs)`  
**描述:** nodeLib.findByIndex 根据节点所在树的每个分支顺序查找。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| indexs   | string | 是   | 是从顶层节点到该节点顺序字符串     |  

示例:  
```lua
local ret = nodeLib.findByIndex("0|1|2")
if ret ~= nil then
    print(ret)
end
```

## 42. 锁定当前界面到内存 (nodeLib.keepNode)
**函数:** `nodeLib.keepNode()`  
**描述:** nodeLib.keepNode 锁定当前界面到内存，下次节点查找查找都会直接从内存中获取该节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  
 
示例:  
```lua
nodeLib.keepNode()
local search_edit = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local input_edit = {class="android.widget.EditText",id="com.android.launcher3:id/input_edit"}
local ret1 = nodeLib.findOne(search_edit,true)
local ret2 = nodeLib.findOne(input_edit,true)
if ret1 ~= nil and ret2 ~= nil then
    nodeLib.setText(input_edit,"abc")
end
nodeLib.releaseNode()
```

## 43. 释放锁定在内存中的节点信息 (nodeLib.releaseNode)
**函数:** `nodeLib.releaseNode()`  
**描述:** nodeLib.releaseNode 释放锁定在内存中的节点信息。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  
 
示例:  
```lua
nodeLib.keepNode()
local search_edit = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local input_edit = {class="android.widget.EditText",id="com.android.launcher3:id/input_edit"}
local ret1 = nodeLib.findOne(search_edit,true)
local ret2 = nodeLib.findOne(input_edit,true)
if ret1 ~= nil and ret2 ~= nil then
    nodeLib.setText(input_edit,"abc")
end
nodeLib.releaseNode()
```

## 44. 给文本输入框节点输入文字 (nodeLib.setText)
**函数:** `nodeLib.setText(node,text)`  
**描述:** nodeLib.setText 给文文本输入框节点输入文字。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| node     | table | 是   | 是一个节点表格     |  
| text     | string | 是   | 要输入的文本字符串     |  

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| boolean | 布尔类型，表示输入是否成功 |  

示例:  
```lua
local node = {class="android.widget.EditText",id="com.android.launcher3:id/search_edit"}
local ret = nodeLib.findOne(node,true)
if ret ~= nil then
    nodeLib.setText(ret,"abc")
end
```

## 45. 点击节点 (nodeLib.click)
**函数:** `nodeLib.click(node,...)`  
**描述:** nodeLib.click 点击指定节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| node     | table | 是   | 是一个节点表格     |  
| mode     | boolean | 否   | 真表示节点点击(需要节点可点击)，假表示模拟触摸式点击,默认为false     |  

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| boolean | 布尔类型，表示点击是否成功 |  

示例:  
```lua
local ret = nodeLib.findByIndex("0|1|2")
if ret ~= nil then
    nodeLib.click(ret)
end
```

## 46. 设置获取节点模式 (nodeLib.setNodeMode)
**函数:** `nodeLib.setNodeMode(mode,enableGetInVisibleNode)`  
**描述:** nodeLib.setNodeMode 设置获取节点模式。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| mode     | number | 是   | 为0表示获取所节点，为1表示获取节点模式为简单模式(不重要的节点将被过滤)     |  
| enableGetInVisibleNode | boolean | 是   | 表示抓取节点的时候是否获取不可见的节点     |  

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| boolean | 布尔类型，表示设置是否成功 |  

示例:  
```lua
nodeLib.setNodeMode(1,false)
```

## 47. 刷新节点 (nodeLib.updateNode)
**函数:** `nodeLib.updateNode()`  
**描述:** nodeLib.updateNode 刷新节点。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| - | - | - | 无 |  

返回值:  
无

示例:  
```lua
nodeLib.updateNode()
local ret = nodeLib.findOne(0,0,0,0,{class="android.widget.RelativeLayout"},true)
if ret ~= nil then
    local r = nodeLib.findInNode(ret,{text=".*新建.*"},true,true)
    if r ~= nil then
        for i=1,#r do
            print(r[i])
        end
    end
end
```

## 48. 实例化一个Path路径对象 (Path.new)
**函数:** `Path.new()`  
**描述:** Path.new 实例化一个Path路径对象，仅使用无障碍模式下，其他模式无效。概念说明:无障碍模式下对屏幕的点击滑动都是基于手势操作,每根手指在屏幕上的滑动轨迹就称为路径(Path)。  
参数:  
无

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| object | Path对象 |  

示例:  
```lua
local path = Path:new() --创建一个轨迹路径
```

## 49. 设置滑动的起始时间 (Path.setStartTime)
**函数:** `path:setStartTime(delay)`  
**描述:** Path:setStartTime 设置滑动的起始时间,单位是毫秒，仅使用无障碍模式下，其他模式无效。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| delay    | number | 是   | 滑动的起始时间，单位是毫秒     |  

返回值:  
无

示例:  
```lua
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
```

## 50. 设置滑动持续的时间 (Path.setDurTime)
**函数:** `path:setDurTime(delay)`  
**描述:** Path.setDurTime 设置滑动时间,单位是毫秒，仅使用无障碍模式下，其他模式无效。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| delay    | number | 是   | 滑动持续的时间，单位是毫秒     |  

返回值:  
无

示例:  
```lua
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
```

## 51. 添加路径经过的滑动点坐标 (Path.addPoint)
**函数:** `path:addPoint(x,y)`  
**描述:** Path.addPoint 添加路径经过的滑动点坐标，仅使用无障碍模式下，其他模式无效。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| x        | number | 是   | 坐标点的x值     |  
| y        | number | 是   | 坐标点的y值     |  

返回值:  
无

示例:  
```lua
--从A点滑动到B点的例子
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
```

## 52. 创建一个手势滑动对象 (Gesture.new)
**函数:** `Gesture.new()`  
**描述:** Gesture.new 创建一个手势滑动对象，仅使用无障碍模式下，其他模式无效。  
参数:  
无

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| object | Gesture对象 |  

示例:  
```lua
local gesture = Gesture:new() --创建一个手势滑动对象
```

## 53. 添加一个滑动路径 (Gesture.addPath)
**函数:** `gesture:addPath(path)`  
**描述:** Gesture.addPath 添加一个滑动路径，仅使用无障碍模式下，其他模式无效。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| path     | object | 是   | Path路径对象     |  

返回值:  
无

示例:  
```lua
local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
```

## 54. 开始执行手势操作 (Gesture.dispatch)
**函数:** `gesture:dispatch(...)`  
**描述:** Gesture.dispatch([callback]) 开始执行手势操作，仅使用无障碍模式下，其他模式无效。  
参数:  
| 参数名   | 类型   | 必填 | 说明                 |  
|:---------|:-------|:-----|:---------------------|  
| callback | function | 否   | 执行结果回调函数，type为0执行完成，为1是执行中途被取消     |  

返回值:  
| 类型 | 说明 |  
|:-----|:-----|  
| boolean | 布尔类型，如果为false则执行失败 |  

示例:  
```lua
nodeLib.openAccessibility()
local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
local r = gesture:dispatch()
if r then
print("执行成功")
else
print("执行失败")
end

local gesture = Gesture:new() --创建一个手势滑动对象
local path = Path:new() --创建一个轨迹路径
path:setStartTime(100) --从触发事件的第100毫秒后开始滑动
path:setDurTime(3000) --滑动的时间
path:addPoint(100,500) --轨迹上的第一个点
path:addPoint(500,500) --轨迹上的第二个点
gesture:addPath(path) --添加一个滑动路径
function onFinishEvent(type) --执行结果回调函数 type为0执行完成，为1是执行中途被取消
if type == 1 then
    print("执行成功")
else
    print("执行失败")
end
end

local r = gesture:dispatch(onFinishEvent)
if r then
    print("任务已被发送")
else
    print("执行失败")
end
sleep(10000)
```
