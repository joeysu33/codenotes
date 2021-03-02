#!/usr/bin/sed -f

#多命令模式，使用{}，使用;进行分割
/Certificate/{p;=}


#多次编辑操作
#sed -n '/Certificate/{s/i/I/g;s/This/this/g;p;=}' input


#超级多次编辑
#sed -n '/[cC]ertifi[Cc]ate/{s/i/I/g;s/[tT]h[iI]s/athis/g;s/athis/THIS/;s/THIS/((&))/g;p;=}' input
