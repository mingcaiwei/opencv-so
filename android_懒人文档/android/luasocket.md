# luasocket 部分方法 (http)

此章节收录 `luasocket`（含 ssl/http 支持）常用方法，示例如下。

---

## 1. 发起网络请求 (http.request)
**函数:** `http.request(arg)`

**描述:** 发起 HTTP/HTTPS 请求，`arg` 可为字符串 URL 或一个表，表中可指定更详细的请求参数（method、headers、sink、timeout 等）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| url | string | 是 | 请求地址 |
| method | string | 否 | HTTP 方法（GET/POST） |
| headers | table | 否 | 请求头表 |
| chunked | boolean | 否 | 是否使用分块传输编码 |
| version | number | 否 | HTTP 协议版本，默认为 1.1 |
| keepAlive | boolean | 否 | 是否保持连接，默认为 false |
| proxy | table | 否 | 包含代理服务器的信息，包括代理类型（"http"或"ftp"）、地址等 |
| proxyCreds | table | 否 | 包含代理服务器的认证信息（如用户名和密码） |
| cookie | string | 否 | 要发送的 Cookie |
| norequestheaders | boolean | 否 | 是否不发送请求头，默认为 false |
| requestheaders | table | 否 | 包含自定义的请求头信息 |
| sink | function/table | 否 | 响应输出处理（如 `ltn12.sink.table`） |
| timeout | number | 否 | 超时时间（秒） |
| sslverify | boolean | 否 | 是否验证 SSL 证书 |

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| number | HTTP 响应状态码（成功时，如 200、404 等） |
| string | HTTP 响应状态码对应的文本描述 |
| table | 服务器返回的 HTTP 头信息，是一个包含各种头字段的表 |
| string | 服务器的响应主体内容 |
| nil, string | 失败时返回 nil 和错误信息 |

示例:
```lua
local https = require("ssl.https")
local ltn12 = require("ltn12")

local url = "http://www.baidu.com/"
local responseBody = {}

local _, status, _, _ = https.request{
  url = url,
  method = "GET",
  protocol = "tlsv1_2",
  sink = ltn12.sink.table(responseBody)
}

if status == 200 then
  print(table.concat(responseBody))
else
  print("Request failed:", status)
end
``` 
