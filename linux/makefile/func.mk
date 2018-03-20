#1.内置函数,函数参数使用,进行分割
#warning
#error
#strip 
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

a = " xy bb "
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
	@echo "strip---"
	@echo ,$(strip " aa cc "),
	$(newline)



