openssl组成
  |
  ----- openssl 命令行工具
  |____ libcrypto 加密算法库
  |____ libssl 加密模块


openssl的主要指令
    genrsa
    req
    x509
    rsa
    ca

使用openssl来生成私钥
1.openssl genrsa [args] [numberbits]

-des
-des3
-aes128
-aes192
-aes256

-passout

-out

