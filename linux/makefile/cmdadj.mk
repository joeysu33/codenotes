#cmd修饰

all:
	echo  "echo without @"
	@echo "echo with @"
	@#执行失败后，整个不会再执行
	@#@cd notexist
	-cd notexist
	@echo "last cmdline"
