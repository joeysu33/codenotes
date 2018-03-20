#编译s_的单个.c文件
#makefile文件中仅仅只能是使用`来执行shell命令
BIN=./bin
CHAP04DIR=chap04_io
COMMONDIR=common
CHAPS = $(shell find . -maxdepth 1 -type d -iname "chap*")
all: chap single
	@echo "compile all"
single:
	@for i in $(shell ls s_*.c) ;do echo "compile:$$i"; j=`echo $$i | sed -n 's/\.c//p'` ; gcc -o $(BIN)/$$j $$i; done
chap:$(BIN)/common.o 
	@for c in $(CHAPS) ;\
		do \
		echo "chapter=$(CHAP)"; \
		dir=$$c;\
		for i in $(shell ls $${dir}/*.c); \
		do \
		echo "compile:$$i"; \
		j=`echo $$i | sed -n 's/\.c//p' | sed -n 's/$(CHAP04DIR)\///p'`; \
		gcc -g -c -o $(BIN)/$$j.o $$i; \
		gcc -o $(BIN)/$$j $(BIN)/$$j.o $(BIN)/common.o ; \
		done; \
		done
$(BIN)/common.o:$(COMMONDIR)/common.c
	@mkdir -p $(BIN)
	@gcc -g -c -o $(BIN)/common.o $(COMMONDIR)/common.c
clean:
	@find . -maxdepth 1 -type f -executable -exec rm -f {} \;
	@rm -f *.txt
	@find $(BIN) -type f -iname "*.o" -exec rm -f {} \;
	@find $(BIN) -type f -executable -exec rm -f {} \;
