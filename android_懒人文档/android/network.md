# 网络方法

## 1. HTTP GET请求 (httpGet)
**函数:** `httpGet(url, [timeout], [header])`
**描述:** HTTP GET请求
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | GET请求的网络地址可带参数 |
| timeout | number | 否 | 请求超时时间单位是秒可不填写默认30秒 |
| header | table | 否 | http请求头默认为空 |

```lua
local ret, code = httpGet("http://www.baidu.com")
print(ret)
```

## 2. HTTP POST请求 (httpPost)
**函数:** `httpPost(url, postdata, [timeout], [header])`
**描述:** HTTP POST请求
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | POST请求的网络地址可带参数 |
| postdata | string | 是 | POST传递的数据 |
| timeout | number | 否 | 请求超时时间单位是秒可不填写默认30秒 |
| header | table | 否 | http请求头默认为空 |

示例:
```lua
local ret, code = httpPost("http://www.baidu.com", "arg=123")
print(ret)
```

## 3. HTTP POST异步请求 (asynHttpPost)
**函数:** `asynHttpPost(callback, url, postdata, [timeout], [header])`
**描述:** HTTP POST异步请求
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| callback | function | 是 | 当服务器响应返回数据时调用该函数 |
| url | string | 是 | POST请求的网络地址可带参数 |
| postdata | string | 是 | POST传递的数据 |
| timeout | number | 否 | 请求超时时间单位是秒可不填写默认30秒 |
| header | table | 否 | http请求头默认为空 |

```lua
function callback(response, code)
    print(response)
end
asynHttpPost(callback, "http://www.baidu.com", "arg=123")
while true do
    sleep(1000)
end
```

## 4. HTTP GET异步请求 (asynHttpGet)
**函数:** `asynHttpGet(callback, url, [timeout], [header])`
**描述:** HTTP GET异步请求
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| callback | function | 是 | 当服务器响应返回数据时调用该函数 |
| url | string | 是 | GET请求的网络地址可带参数 |
| timeout | number | 否 | 请求超时时间单位是秒可不填写默认30秒 |
| header | table | 否 | http请求头默认为空 |

```lua
function callback(response, code)
    print(response)
end
asynHttpGet(callback, "http://www.baidu.com")
while true do
    sleep(1000)
end
```

## 5. 下载文件 (downloadFile)
**函数:** `downloadFile(url, savepath, [progress])`
**描述:** 下载文件
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 请求的网络地址 |
| savepath | string | 是 | 保存的文件路径 |
| progress | function | 否 | 可选项,函数类型,下载进度回调方法 |
返回值:

```lua
function progress(pos)
    toast("下载进度:"..pos, 0, 0, 30)
end
downloadFile("http://www.xxx.com/download/update.zip", "/mnt/sdcard/update.zip")
```

## 6. 上传文件 (uploadFile)
**函数:** `uploadFile(url, uploadfile, [timeout])`
**描述:** 上传文件
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 请求的网络地址 |
| uploadfile | string | 是 | 要上传到服务器的文件路径 |
| timeout | number | 否 | 请求超时时间单位是秒可不填写默认30秒 |

```lua
local ret = uploadFile("http://ceshiabc123.com?arg=1", "/data/img/test.ico")
print(ret)
```

## 7. 打开一个websocket连接 (startWebSocket)
**函数:** `startWebSocket(url, onOpened, onClosed, onError, onRecv)`
**描述:** 打开一个websocket连接
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | ws地址,目前只支持ws协议wss暂不支持 |
| onOpened | function | 是 | 当连接服务器成功后会回调这个函数 |
| onClosed | function | 是 | 当连接服务器断开后会回调这个函数 |
| onError | function | 是 | 当连接服务器失败后会回调这个函数 |
| onRecv | function | 是 | 当有接收到数据时会回调这个函数 |

```lua
local ws = nil

function wLog(text)
    print(text)
    toast(text, 0, 0, 20)
end

function onOpened(handle)
    ws = handle
    print("连接上服务器")
end

function reConnect()
    ws = nil
    wLog("断开连接，3秒后重连")
    setTimer(function()
        startWebSocket("ws://192.168.2.105:5586", onOpened, onClosed, onError, onRecv)
    end, 3000)
end

function onClosed(handle)
    reConnect()
end

function onError(handle)
    reConnect()
end

function onRecv(handle, message)
    local text = "消息:"..message
    wLog(text)
end

local handle = startWebSocket("ws://192.168.2.105:5586", onOpened, onClosed, onError, onRecv)

if handle ~= nil then
    local tick = 1
    while true do
        if ws ~= nil then
            sendWebSocket(ws, string.format("hello:%d", tick))
            tick = tick + 1
        end
        sleep(100)
    end
end
```

## 8. 关闭一个websocket连接 (closeWebSocket)
**函数:** `closeWebSocket(handle)`
**描述:** 关闭一个websocket连接
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 由startWebSocket返回的句柄 |

```lua
function onOpened(handle)
    ws = handle
    print("连接上服务器,三秒后关闭")
    setTimer(function()
        closeWebSocket(handle)
    end, 3000)
end

function onClosed(handle)
    print("连接断开")
end

function onError(handle)
    print("连接异常")
end

function onRecv(handle, message)

end

local handle = startWebSocket("ws://192.168.2.105:5586", onOpened, onClosed, onError, onRecv)

sleep(10000)
```

## 9. 向服务器发送数据 (sendWebSocket)
**函数:** `sendWebSocket(handle, text)`
**描述:** 向服务器发送数据
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | number | 是 | 由startWebSocket返回的句柄 |
| text | string | 是 | 待发送的字符串 |

```lua
local ws = nil

function wLog(text)
    print(text)
    toast(text, 0, 0, 20)
end

function onOpened(handle)
    ws = handle
    print("连接上服务器")
end

function reConnect()
    ws = nil
    wLog("断开连接，3秒后重连")
    setTimer(function()
        startWebSocket("ws://192.168.2.105:5586", onOpened, onClosed, onError, onRecv)
    end, 3000)
end

function onClosed(handle)
    reConnect()
end

function onError(handle)
    reConnect()
end

function onRecv(handle, message)
    local text = "消息:"..message
    wLog(text)
end

local handle = startWebSocket("ws://192.168.2.105:5586", onOpened, onClosed, onError, onRecv)

if handle ~= nil then
    local tick = 1
    while true do
        if ws ~= nil then
            sendWebSocket(ws, string.format("hello:%d", tick))
            tick = tick + 1
        end
        sleep(100)
    end
end
```

## 10. java层http post (LuaEngine.httpPost)
**函数:** `LuaEngine.httpPost(url, params, headers, timeout)`
**描述:** LuaEngine.httpPost java层http post
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 访问的网络地址 |
| params | table | 是 | 参数键值对 |
| headers | table | 是 | 通params一样 |
| timeout | number | 是 | 超时时间 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
local params = {}
params["id"] = "123"
params["token"] = "abc"
local headers = {}
headers["User-Agent"] = "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.3) Gecko/2008092417 Firefox/3.0.3"
local postRet = LuaEngine.httpPost("https://www.baidu.com", params, headers, 60)
print(postRet)
```

## 11. java层http post 任意数据 (LuaEngine.httpPostData)
**函数:** `LuaEngine.httpPostData(url, params, headers, timeout)`
**描述:** LuaEngine.httpPostData java层http post 任意数据
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 访问的网络地址 |
| params | string | 是 | 参数 |
| headers | string | 是 | 请求头 |
| timeout | number | 是 | 超时时间 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
url = "https://api.xxxx.com/data"
params = {}
params["data"] = "abc"
local arg = jsonLib.encode(params)
local status = LuaEngine.httpPostData(url, arg, "application/json;charset=utf-8", 30)
print(status)
```

## 12. 发送一个普通文本邮件 (LuaEngine.sendMail)
**函数:** `LuaEngine.sendMail(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, [发送结果回调])`
**描述:** LuaEngine.sendMail 发送一个普通文本邮件
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| 账号 | string | 是 | 需要用此账号的邮箱去发送邮件 |
| 密码 | string | 是 | 密码 |
| 发送给谁 | string | 是 | 发送给谁 |
| 邮箱服务器 | string | 是 | 邮箱服务器 |
| 是否开启认证 | boolean | 是 | 是否开启认证 |
| 邮件标题 | string | 是 | 邮件标题 |
| 邮件内容 | string | 是 | 邮件内容 |
| 发送结果回调 | function | 否 | 发送结果回调 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.IOnMailResult')

local 账号 = "xxxxx.com" --需要用此账号的邮箱去发送邮件
local 密码 = "xxxxxxxxx" --此密码是临时密码不是邮箱真正的密码由邮箱后台系统分配
local 发送给谁 = "xxxxx@qq.com"
local 邮箱服务器 = "smtp.163.com"
local 是否开启认证 = true
local 邮件标题 = "你好我是懒人"
local 邮件内容 = "你好我是懒人"

function log(str)
    toast(str, 0, 0, 20)
end

function 发送普通邮件()
    LuaEngine.sendMail(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, IOnMailResult{
        onSuccess = function()
            log("发送成功")
        end,
        onFailed = function(err)
            log("发送失败=>"..err)
        end
    })
end
```

## 13. 发送一个带单个附件的邮件 (LuaEngine.sendMailWithFile)
**函数:** `LuaEngine.sendMailWithFile(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, 文件路径, [发送结果回调])`
**描述:** LuaEngine.sendMailWithFile 发送一个带附件的邮件
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| 账号 | string | 是 | 需要用此账号的邮箱去发送邮件 |
| 密码 | string | 是 | 密码 |
| 发送给谁 | string | 是 | 发送给谁 |
| 邮箱服务器 | string | 是 | 邮箱服务器 |
| 是否开启认证 | boolean | 是 | 是否开启认证 |
| 邮件标题 | string | 是 | 邮件标题 |
| 邮件内容 | string | 是 | 邮件内容 |
| 文件路径 | string | 是 | 文件路径 |
| 发送结果回调 | function | 否 | 发送结果回调 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.IOnMailResult')

local 账号 = "xxxxx.com" --需要用此账号的邮箱去发送邮件
local 密码 = "xxxxxxxxx" --此密码是临时密码不是邮箱真正的密码由邮箱后台系统分配
local 发送给谁 = "xxxxx@qq.com"
local 邮箱服务器 = "smtp.163.com"
local 是否开启认证 = true
local 邮件标题 = "你好我是懒人"
local 邮件内容 = "你好我是懒人"

function log(str)
    toast(str, 0, 0, 20)
end

function 发送文件邮件()
    local path = "/sdcard/test.png"
    snapShot(path)
    if fileExist(path) then
        LuaEngine.sendMailWithFile(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, path, IOnMailResult{
            onSuccess = function()
                log("发送成功")
            end,
            onFailed = function(err)
                log("发送失败=>"..err)
            end
        })
    else
        log("不存在=>"..path)
    end
end
```

## 14. 发送一个带多个附件的邮件 (LuaEngine.sendMailWithMultiFile)
**函数:** `LuaEngine.sendMailWithMultiFile(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, 文件路径数组, [发送结果回调])`
**描述:** LuaEngine.sendMailWithMultiFile 发送一个带多个附件的邮件
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| 账号 | string | 是 | 需要用此账号的邮箱去发送邮件 |
| 密码 | string | 是 | 密码 |
| 发送给谁 | string | 是 | 发送给谁 |
| 邮箱服务器 | string | 是 | 邮箱服务器 |
| 是否开启认证 | boolean | 是 | 是否开启认证 |
| 邮件标题 | string | 是 | 邮件标题 |
| 邮件内容 | string | 是 | 邮件内容 |
| 文件路径数组 | table | 是 | 文件路径数组 |
| 发送结果回调 | function | 否 | 发送结果回调 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
import('com.nx.assist.lua.IOnMailResult')

local 账号 = "xxxxx.com" --需要用此账号的邮箱去发送邮件
local 密码 = "xxxxxxxxx" --此密码是临时密码不是邮箱真正的密码由邮箱后台系统分配
local 发送给谁 = "xxxxx@qq.com"
local 邮箱服务器 = "smtp.163.com"
local 是否开启认证 = true
local 邮件标题 = "你好我是懒人"
local 邮件内容 = "你好我是懒人"

function log(str)
    toast(str, 0, 0, 20)
end

function 发送多个文件邮件()
    local list = {"/sdcard/test1.png", "/sdcard/test2.png"}
    for i = 1, #list do
        snapShot(list[i])
        if fileExist(list[i]) == false then
            log("不存在=>"..list[i])
            return
        end
    end
    LuaEngine.sendMailWithMultiFile(账号, 密码, 发送给谁, 邮箱服务器, 是否开启认证, 邮件标题, 邮件内容, list, IOnMailResult{
        onSuccess = function()
            log("发送成功")
        end,
        onFailed = function(err)
            log("发送失败=>"..err)
        end
    })
end
```

## 15. java层http get (LuaEngine.httpGet)
**函数:** `LuaEngine.httpGet(url, params, timeout)`
**描述:** LuaEngine.httpGet java层http get
参数:
| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 访问的网络地址 |
| params | table | 是 | 参数键值对 |
| timeout | number | 是 | 超时时间 |

```lua
import('java.lang.*')
import('java.util.*')
import('com.nx.assist.lua.LuaEngine')
local headers = {}
headers["User-Agent"] = "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.3) Gecko/2008092417 Firefox/3.0.3"

local getRet = LuaEngine.httpGet("https://www.baidu.com", headers, 30)
print(getRet)
```
