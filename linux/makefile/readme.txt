Linux的Makefile是非常实用的自动化构建工具，cmake,qmake等都是在此基础之上进行
Makefile中执行命令，可以通过`cmd`来执行,例如:
Makefile中的变量通过$(var)来进行描述
object: depends
[tab]command (command必须以tab键来进行分割)
如果在command中需要执行shell，则可以通过$(shell cmd)来执行
如果在command的前面加上@，则不显示该命令，否则显示,如果在command中要直接执行shell的命令，可以`cmd`来执行
命令的执行中，变量必须实用$$来约束，进行转义

single:
    1.@表示不显示命令行
    2.$(shell cmd) 执行shell命令
    3.`cmd`来执行命令
    4.$$i 对shell的变量名称进行转义
    5.cmd必须按照行进行编写
	@for i in $(shell ls s_*.c) ;do echo "compile:$$i"; j=`echo $$i | sed -n 's/\.c//p'` ; gcc -o $$j $$i; done
