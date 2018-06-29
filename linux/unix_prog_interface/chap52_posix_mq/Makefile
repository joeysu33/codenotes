#chap04_io Makefile

include ../Makefile.inc

sources := $(wildcard *.c)
tmp_obj := $(patsubst %.c, %.o, $(sources))
tmp_tar := $(patsubst %.c, %, $(sources))

#call和join均可以实现操作
objects := $(foreach i,$(tmp_obj), $(call fnc_add_obj_dir,$(i)))
targets := $(foreach i, $(tmp_tar), $(join $(BIN_DIR),$(i)))

#最后目标只能有一个
all:$(targets)

$(targets): $(objects)
	@gcc -o $@ $(join $(join $(OBJ_DIR), $(basename $(notdir $@))), .o) $(CLIBFLAGS) -lrt

$(objects):$(sources)
	gcc -c -g -o $@ $(join $(basename $(notdir $@)), .c) 

clean:
	@rm -f $(objects) $(targets)
