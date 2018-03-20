#编译s_的单个.c文件
#makefile文件中仅仅只能是使用`来执行shell命令

include Makefile.inc

all: single chapters 

single: $(SINGLE_SRCS)
	for i in $(SINGLE_SRCS) ;do echo "compile single file:$$i"; name=`echo $$i | sed -n 's/\.c//p'` ; $(CC) $(CFLAGS) -o $(BIN_DIR)/$$name $$i; done 
common: 
	(cd $(COMMON_DIR) && make && cd ..)
chapters: common
	echo "chapter..."
	#@for i in $(CHAPTER_DIRS); do\
	#	echo "compile chapter:$$i"\
	#	cd $$i;\
	#	make ; \
	#	cd ..; \
	#done
clean:
	@find $(BIN_DIR) -type f -executable -exec rm -f {} \;
	@find ${BIN_DIR} -type f -iname "*.o" -exec rm -f {} \;
cleanall:clean
	@find $(OBJ_DIR) -type f -iname "*.o" -exec rm -f {} \; 
