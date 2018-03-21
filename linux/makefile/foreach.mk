#makefile 内置函数foreach的使用
#$(foreach var,var_list, opt)

dirs = testdir/include testdir/bin 
d=$(foreach i, $(dirs), $(wildcard $(i)/*))

.PHONY : all
all:
	@echo "d=$(d)"
