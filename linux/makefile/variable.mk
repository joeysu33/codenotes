#make内置变量
#make可以直接访问系统的环境变量,访问方式和make的变量相同
#查看变量的来源可以使用$(origin variable)
include include.mk

list:
	@echo $(MAKE_VERSION)
	@echo $(CURDIR)
	@echo $(MAKEFILE_LIST)
	@echo "$(.VARIABLES)" 
	@echo $(VAR_X)
	@echo $(VAR_Y)
	@echo "env PWD=" $(PWD)
	@#来源主要包含: origin undefined default environment file (makefile) commandline (make 执行命令行varname=varvalue) override automatic (makefile的自动变量)
	@echo "origin PWD=" $(origin PWD)
	@echo "origin CURDIR=" $(origin CURDIR)
	@echo "origin cmdvar=" $(origin cmdvar)
	@echo "origin MAKEFILE_LIST=" $(origin MAKEFILE_LIST)
