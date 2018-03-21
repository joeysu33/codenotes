include ../../Makefile.inc

obj := $(patsubst %.c, $(obj_dir)/%.o,$(wildcard *.c))
tar := $(patsubst $(obj_dir)/%.o, $(bin_dir)/%,$(obj))

test:
	@echo "obj="$(obj)
	@echo "tar="$(tar)

$(bin_dir)/% : $(obj_dir)/%.o
	gcc -o $@ $<

$(obj_dir)/%.o : $(wildcard *.c)
	gcc -c $(CFLAGS) -o $@ $<


