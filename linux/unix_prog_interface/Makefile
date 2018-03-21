#编译s_的单个.c文件
#makefile文件中仅仅只能是使用`来执行shell命令

include Makefile.inc

clean:
	@find $(BIN_DIR) -type f -executable -exec rm -f {} \;
	@find ${BIN_DIR} -type f -iname "*.o" -exec rm -f {} \;
cleanall:clean
	@find $(OBJ_DIR) -type f -iname "*.o" -exec rm -f {} \; 
