#common makefile

include ../Makefile.inc

source = common.c
object = $(join $(OBJ_DIR), $(subst .c,.o, $(source)))
target = $(join $(BIN_DIR), $(patsubst %.c, lib%.a, $(source)))

all: $(target)

#项目构建依赖过程中，不能多个变量书写依赖否则无法判断 
#例如 
#$(BIN_DIR)/$(target) : $(OBJ_DIR)/$(object)
#	command1
#	command2
#
#$(OBJ_DIR)/$(object) : $(source)
#	command1
#	command2
#
#
$(target): $(object)
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)
	ar -rcs $@ $^

$(object): $(source)
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(target) $(object)
