#在编写Makefile的时候-l选项需要写在后面??
#gcc -ldl -o dynload $< 这么书写失败,找不到-ldl选项
#在执行的时候，如果动态库在本地，需要加上./

all: exe mod1 mod2 exe2

exe:dynamicload.o
	gcc -o dynload $< -ldl

exe2: dynamic_exec.o
	gcc -shared -o libdynamic.so.1.0 -Wl,-soname,libdynamic.so.1 -Wl,--export-dynamic dynamic_exec.o

dynamic_exec.o: dynamic_exec.c
	gcc -fPIC -g -c -o $@ $<

mod1:mod1.o
	gcc -shared -o libmod1.so.1.0 -Wl,-soname,libmod1.so.1 $<

mod2:mod2.o
	gcc -shared -o libmod2.so.1.0 -Wl,-soname,libmod2.so.1  $<

dynamicload.o:dynamicload.c
	@echo "compile dynamicload"
	gcc -g -c -o $@ $<

mod1.o:mod1.c
	gcc -g -c -fPIC -o $@ $^

mod2.o:mod2.c
	gcc -g -c -fPIC -o $@ $^

clean:
	@rm -f *.o
	@find . -maxdepth 1 -type f -executable -exec rm -f {} \;
