#!/usr/bin/sed -f

#将/etc/passwd中与root相匹配的行写入保持缓冲区，并与ds相匹配的行进行互换
#最后输出缓冲区内容
/root/h;/ds/G;/root/d;p
