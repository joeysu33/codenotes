#宏定义操作
#1.marco调用
#2.marco参数调用
#3.marco声明
#4.marco的域问题，展开，内外均有效果
#5.宏的参数$1 或$(1)

#不带参数的宏 $(m1)
define m1
	@echo "===marco m1===="
	@find . -type f -iname "*.mk" -print
endef

#带参数的宏，可以使用call函数进行调用
define m2 
	@echo "====marco m2===="
	@echo "arg1 = $(1) arg2 = $(2)"
endef


#宏的域，宏的域首先展开再替换，不存在栈帧
define m_parent
	@echo "====marco m_parent===="
	@echo "parent-arg1 = $(1) parent-arg2 = $(2)"
	@#命令行的注释也要加上@符号，否则会在执行过程中显示出来
	@#说明这个问题已经在新版本中已经修复了
	@#宏的调用，不会在完全展开替换之后调用，而是先展开，后替换调用
	@$(call m_child,$(1), kk)
endef

define m_child
	@echo "======maraco m_child===="
	@echo "child-arg1 = $(1) child-arg2 = $(2)"
endef

all:
	$(m1)
	$(call m2, one, two)
	$(call m_parent, xx,yy)
