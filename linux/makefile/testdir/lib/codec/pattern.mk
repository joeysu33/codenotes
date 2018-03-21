include ../../Makefile.inc

sources = $(wildcard *.c)
objects = $(patsubst %.c,$(obj_dir)/%.o,$(wildcard *.c))
targets : codec codec2

codec codec2 : $(objects)
	test -d $(bin_dir)  || mkdir -p $(bin_dir)
	ar -rcs $(bin_dir)/"lib$@.a" $<

#匹配规则如何实现的
$(objects):$(sources)
	test -d $(obj_dir) || mkdir -p $(obj_dir)
	gcc -c -o $@ $(join $(basename $(notdir $@)), .c)

clean:
	@rm -f $(subst .o,,$(targets))
	@rm -f $(obj_dir)/*.o $(bin_dir)/*.a
