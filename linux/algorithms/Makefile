#编译s_的单个.c文件
#makefile文件中仅仅只能是使用`来执行shell命令
#TARGET input when execute commandline

include Makefile.inc

#lib_common := common
chapters := $(sort $(wildcard chap*))

#.PHONY: all $(chapters) $(lib_common)
all:$(chapters)

#描述chapter和common之间的依赖关系
$(chapters) $(lib_common):
	@$(MAKE) -C $@ $(TARGET)

#$(chapters) :$(lib_common)

