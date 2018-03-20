#1.内置函数,函数参数使用,进行分割
#warning
#error
#strip 会将的多个空格，转换成一个空格
#addprefix
#addsuffix
#wildcard 野匹配，采用*来进行匹配
#filter 以pattern模式(%)来过滤text字符串中的单词，保留符合模式的单词
#filter-out  反过滤函数，以pattern模式过滤<text>字符串中的单词，去除符合模式中的单词
#call call <expression>, <param1>, <param2>... 使用param来占位表达式中的$(1) $(2)
#subst 字符串替换 $(subst <from>,<to>,<text>),将text中和from匹配的替换为to
#patsubst 模式字符串天幻函数(pattern subst),
#	$(patsubst <pattern>, <replacement>, <text>)
#	eg: $(patsubst %.c,%.o, x.c.c bar.c)
#	将x.c.c bar.c替换成x.c.o bar.o
#findstring $(findstring <target>, <wordlist>) 找到返回target，否则返回null
#sort 将<list>中的单词进行排序 $(sort foo bar lose) 返回bar foo lose
#word 取单词函数$(word 2, foo bar baz) 返回第二个单词 bar,从1开始计数
#words 单词个数统计 $(words , foo bar baz) 返回"3"
#firstword 取第一个单词 $(firstword foo bar baz) 返回foo，等价$(word 1, foo bar baz)
#wordlist 取单词串$(wordlist 2,3, foo bar baz) 返回第二个和第三个 bar baz
#dir 取目录函数 $(dir src/foo.c hacks) 返回src/ ./
#notdir 取文件函数 $(notdir src/foo.c hacks) 返回foo.c hacks
#suffix 取后缀函数 $(suffix src/foo.c src-1.0/bar.c hacks) 返回".c .c"
#basename 取base名称 $(basename src/foo.c src-10./bar.c hacks)返回src/foo src-1.0/bar hacks)
#join 连接函数 $(join aa bb, 11 22 3)返回 "aa11 bb22 3"
#
#2.makefile中的转义字符 |，输出的时候需要使用\|转义
#
#3.注意事项
#(1)函数中的第一个参数直接空格分割，其他的参数以,分割
#(2)在函数中不要随便使用“，”，会被默认当成是参数分割符号
#
#问题
#1.能否直接在make命令中来修改变量值,如何修改
#!!!!!!!!!!!!!!!!!!!!!!!!!!!


$(warning builtin-warning func)
#如果执行到error则会导致make停止执行
#$(error builtin-in-error func)

a = "      xy bb    "
b = $(strip $(a)) #strip a
#reverse 相当于变成了一个格式化字符串
reverse = $(2) $(1)
fmt0 = "arg1=$(1) arg2=$(2)"

#宏操作
define show-ab
	@echo a=$(a),b=$(b)
endef

define newline
	@echo ""
endef

all:
	$(show-ab)
	@echo $(addprefix $(a), kk)
	$(show-ab)
	@echo $(wildcard src/*) #显示src/*匹配的所有文件序列
	$(newline)
	@echo "wildcard--"
	@echo $(wildcard src/file*) #显示src/file*匹配的内容
	$(newline)
	@echo "filter--"
	@echo $(filter src/file1%.dat , $(wildcard src/*))
	$(newline)
	@echo "filter-out--"
	@echo $(filter-out src/file%.dat, $(wildcard src/*))
	$(newline)
	@echo "call--"
	@echo $(call reverse, "kk", "jj") #这里直接在call函数中写格式化字符串失败
	@echo $(call fmt0, "kk", "jj")
	@echo $(subst "ee", "EE", "feet on the street") #将ee替换成EE
	@echo $(subst 1,100, $(fmt0)); #将1替换成100
	@echo "patsubst---"
	@echo $(patsubst %.dat, %.o, $(wildcard src/file*))
	$(newline)
	@echo "strip---(将多个空格替换为一个空格)"
	@echo ="     aa cc       ff       "= #?strip没有起作用
	@echo =$(strip "     aa cc       ff       ")= #?strip没有起作用
	@echo $(strip $(a))
	$(newline)
	@echo "sort---"
	@echo $(sort foo bar zab)
	$(newline)
	@echo "word--"
	@echo $(word 2, foo bar zab)
	$(newline)
	@echo "firstword---"
	@echo $(firstword foo bar zab)
	$(newline)
	@echo "words---"
	@echo $(words foo bar zab)
	$(newline)
	@echo "dir---"
	@echo $(dir src/file1.c src-1.0-a/file2.c hacks)
	$(newline)
	@echo "notdir---"
	@echo $(notdir src/file1.c src-1.0-a/file2.c hacks)
	$(newline)
	@echo "basename---"
	@echo $(basename src/file1.c src-1.0-a/file2.c hacks)
	$(newline)
	@echo "join--"
	@echo $(join aa bb cc, 11 22 44)
	$(newline)
	@echo "suffix--"
	@echo $(suffix src/file1.c src-1.0-a/file2.c hacks.obj file.obj)
	$(newline)
	@echo "findstring--"
	@echo $(findstring x, x y z)
	@echo $(findstring x, y z)
	$(newline)





