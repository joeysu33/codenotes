1.Linux的Makefile是非常实用的自动化构建工具，cmake,qmake等都是在此基础之上进行
Makefile中执行命令，可以通过`cmd`来执行,例如:
Makefile中的变量通过$(var)来进行描述
object: depends
[tab]command (command必须以tab键来进行分割)
如果在command中需要执行shell，则可以通过$(shell cmd)来执行
如果在command的前面加上@，则不显示该命令，否则显示,如果在command中要直接执行shell的命令，可以`cmd`来执行
命令的执行中，变量必须实用$$来约束，进行转义

single:
    1.@表示不显示命令行,如果该行不是命令行，而是注释那么需要写成@#，否则仍然会显示注释行
    2.$(shell cmd) 执行shell命令
    3.`cmd`来执行命令
    4.$$i 对shell的变量名称进行转义
    5.cmd必须按照行进行编写
	@for i in $(shell ls s_*.c) ;do echo "compile:$$i"; j=`echo $$i | sed -n 's/\.c//p'` ; gcc -o $$j $$i; done

2.makefile中的常用特殊变量
$@ 输出文件（所有的，以空格分开)
$< 第一个输入依赖文件
$^ 所有的输入依赖文件（已经去掉重复)
$+ 所有的输入依赖文件 (保留重复)
$* 工作目标的主文件名(stem部分，也就是abc.dat abc是主文件名,.dat是扩展)
$? 时间戳在目标之后的所有必要文件

3.模式规则
s%.o :s%.c
    #将所有s%.c开始的文件作为输入，%进行一个对应的替换操作

4.VPATH 增加文件的搜索路径
%.o : %.c
    $(CC) $(CFLAGS) $@ $^

6.假的目标
.PHONY 保证该目标每次都能自动执行，对于clean之类的操作进行说明
.PHONE clean cleanall
clean:
    rm -f *.o
cleanall:
    find . -maxdepth 1 -type f -executable -exec rm -f {} \;

7.变量和宏
CC = gcc #常量
MKDIR = mkdir -p
#也可以写成 MKDIR := mkdir -p

sources = *.c #变量
sources = $(shell ls *.c) #和上面的变量等价，使用shell来执行
objects = $(subst .c, .o, $(sources))

#函数
maybe-make-dir = $(if $(wildcard $1),,$(MKDIR) $1)
assert-not-null = $(if $1, , $(error illegal null value.))
内置函数
$(shell ...) shell函数
$(warning ...) 警告
$(error ...) 错误
$(strip arg) 将参数arg中的空格删除,返回结果，不修改arg的值

#宏
myjar: *.class
    $(create-jar)

#格式
#define [marco-name]
#command1
#command2
#endef

define create-jar
    @echo Creating $@
    $(RM) $(TMP_JAR_DIR)
    $(MKDIR) $(TMP_JAR_DIR)
    $(CP) -r $^ $(TMP_JAR_DIR)
    cd $(TMP_JAR_DIR) && $(JAR) $(JARFLAGS) $@ .
    $(JAR) -ufm $@ $(MANIFEST)
    $(RM) $(TMP_JAR_DIR)
endef

#一个新例子
BIN := /usr/bin
PRINTF := $(BIN)/printf
DF := $(BIN)/df
AWK := $(BIN)/awk

define free-space
    $(PRINTF) "Free disk space"
    $(DF) . | $(AWK) 'NR == 2 (print $$4 }'
endef

变量赋值操作
定义     何时扩展a  合适扩展b
a = b     立即       延后
a := b    立即       立即
a += b    立即       延后或立即
define a  立即       延后
b ...
b ...
endef

8.条件指令与引入指令的处理
#COPMSPEC只会在windows上被定义
#判断COMSPEC是否已经定义
ifdef COMPSPEC
    PATH_SEP := ;
    EXE_EXT := .exe
else
    PATH_SEP := ;
    EXE_EXT :=
endif

条件指令的基本语法
if-condition
    text if the condition is true
endif
或:
if-condition
    text if the condition is true
else
    text if the condition is false
endif

if条件语句的书写格式
ifdef variable-name
ifndef  variable-name
ifeq test
ifneq test

条件指令可用在宏定义和命令脚本中，还可以放在makefile的顶层
变量测试的书写格式
ifeq (a, b) # a,b都是变量名称
ifeq ("a, "b") #a,b都是变量名称，可以用于展开
ifeq 'a' 'b'  #建议采用''或""，避免展开引起的问题

9.include指令
include defines.mk


10.标准的make变量
MAKE_VERSION makefile的版本编号
CURDIR 正在执行make进程的当前工作目录
MAKEFILE_LIST make所读取的各个makefile文件的名称所构成的列表
MAKECMDGOALS 对当前所运行的make而言，make运行时命令行上指定了那些工作目标
            此变量并不包含命令行选项或者变量的赋值。eg:
            $make -f -FOO=bar -k goal <<< 'goal:;#$(MAKECMDGOALS)'
            #goal
.VARIABLES make从各个makefile文件中所读进的变量的名称所构成的列表


10.流程控制函数
$(if condition, then-part, else-part)








