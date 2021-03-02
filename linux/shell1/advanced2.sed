#!/usr/bin/sed -f

#多命令模式，使用{}，使用;进行分割
/good/{s/[Oo][Oo]/(&)/g;=;p}
