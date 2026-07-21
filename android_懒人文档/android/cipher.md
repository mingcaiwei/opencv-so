# 加解密方法 (Cipher)

## 1. AES 加密/解密 (cryptLib.aes_crypt)
**函数:** `cryptLib.aes_crypt(data, key, operation, mode, [iv], [padding])`

**描述:** 对数据执行 AES 加密或解密操作，支持多种模式（ECB/CBC/CFB/OFB/CTR）和可选填充。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| data | string | 是 | 要加密或解密的原始数据 |
| key | string | 是 | 加密密钥（16/24/32 字节，对应 AES-128/192/256） |
| operation | string | 是 | 操作类型，`"encrypt"` 或 `"decrypt"` |
| mode | string | 是 | 加密模式：`"ecb"`, `"cbc"`, `"cfb"`, `"ofb"`, `"ctr"` |
| iv | string | 否 | 初始化向量（16 字节），ECB 模式不需要 |
| padding | boolean | 否 | 是否启用 PKCS#7 填充，默认为 `true` |

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 加密或解密后的数据 |

**注意事项:**
- ECB 模式不需要 `iv` 参数
- 密钥长度必须为 16/24/32 字节
- 当模式不是 ECB 时，`iv` 长度必须为 16 字节

示例:
```lua
local data = "Hello LazyScript!"
local key = "1234567890123456"  -- 16 字节 AES-128
local iv = "0000000000000000"   -- 16 字节 IV

-- AES-CBC 加密
local encrypted = cryptLib.aes_crypt(data, key, "encrypt", "cbc", iv, true)
print("加密结果:", encrypted)

-- AES-CBC 解密
local decrypted = cryptLib.aes_crypt(encrypted, key, "decrypt", "cbc", iv, true)
print("解密结果:", decrypted)
```

---

## 2. 生成 AES 密钥 (cryptLib.aes_keygen)
**函数:** `cryptLib.aes_keygen(key_length)`

**描述:** 随机生成指定长度的 AES 密钥（16/24/32）。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| key_length | number | 是 | 密钥长度（16/24/32） |


| 返回值类型 | 说明 |
|:---:|:---:|
| string | 随机生成的密钥 |

示例:
```lua
local key = cryptLib.aes_keygen(32) -- 生成 32 字节密钥 (AES-256)
print("生成的密钥:", key)
```

---

## 3. 生成随机 IV (cryptLib.aes_ivgen)
**函数:** `cryptLib.aes_ivgen()`

**描述:** 生成一个 16 字节的随机初始化向量 (IV)，用于 CBC/CFB/OFB 等模式。

返回值:

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 16 字节随机 IV |

示例:
```lua
local iv = cryptLib.aes_ivgen()
print("生成的IV:", iv)
```

---

## 4. 生成 RSA 密钥对 (cryptLib.rsa_generate_key)
**函数:** `cryptLib.rsa_generate_key([key_bits])`

**描述:** 生成 RSA 公钥/私钥对，返回 PEM 格式的公钥和私钥。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| key_bits | number | 否 | 密钥长度，默认 2048（常见 1024/2048/4096） |

| 返回值类型 | 说明 |
|:---:|:---:|
| string | PEM 格式的公钥 |
| string | PEM 格式的私钥 |

**注意事项:**
- 密钥长度越长越安全，但性能越低；一般建议至少使用 2048 位。

示例:
```lua
local pubkey, privkey = cryptLib.rsa_generate_key(2048)
print("公钥:\n", pubkey)
print("私钥:\n", privkey)
```

---

## 5. RSA 加密（或签名）(cryptLib.rsa_encrypt)
**函数:** `cryptLib.rsa_encrypt(data, key, is_public_key)`

**描述:** 使用 RSA 公钥（或私钥）对数据进行加密；当使用私钥加密时可用于签名场景。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| data | string | 是 | 要加密的数据 |
| key | string | 是 | 公钥或私钥（PEM 格式） |
| is_public_key | boolean | 是 | `true` 表示使用公钥加密，`false` 表示使用私钥加密 |

| 返回值类型 | 说明 |
|:---:|:---:|
| string | 加密后的数据（原始字节） |

**注意事项:**
- RSA 加密的数据长度受限（通常不能超过密钥长度减填充开销，例如 PKCS#1 填充为 key_len-11），大数据推荐使用混合加密（对称加密数据，RSA 加密对称密钥）。

示例:
```lua
-- 假设已生成 pubkey, privkey
local original_data = "需要加密的敏感数据"
local encrypted_data = cryptLib.rsa_encrypt(original_data, pubkey, true)
print("加密后长度:", #encrypted_data)

-- 使用私钥解密
local decrypted = cryptLib.rsa_decrypt(encrypted_data, privkey, false)
print("解密结果:", decrypted)
```

---

## 6. RSA 解密（或验证签名）(cryptLib.rsa_decrypt)
**函数:** `cryptLib.rsa_decrypt(data, key, is_public_key)`

**描述:** 使用 RSA 私钥（或公钥）对数据进行解密；当使用公钥解密私钥“加密”的数据时可用于验证签名。

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| data | string | 是 | 要解密的数据 |
| key | string | 是 | 私钥或公钥（PEM 格式） |
| is_public_key | boolean | 是 | `true` 表示使用公钥解密，`false` 表示使用私钥解密 |


| 返回值类型 | 说明 |
|:---:|:---:|
| string | 解密后的原始数据 |

示例:
```lua
local decrypted = cryptLib.rsa_decrypt(encrypted_data, privkey, false)
print("解密结果:", decrypted)
``` 
