#chap04_io Makefile
#$$ORIGIN表示程序执行的当前路径

include ../Makefile.inc

all: exec shared static exer sv 

#使用-Wl,-z,origin '-Wl,-rpath,$$ORIGIN:XXX'
#和使用-Wl,-rpath,'$$ORIGIN:XXX' 的区别是上述方法会在动态库段多一个FLAGS_1 ORIGIN (readelf -d XXX)

exec : shared main.c
	gcc -o test main.c -lmycalc -L. -Wl,-z,origin '-Wl,-rpath,$$ORIGIN'
	@#gcc -o test  -lmycalc -L. main.c -Wl,-rpath,'$$ORIGIN'
	@readelf -a test > test.elf

shared: mycalc.c
	gcc -fPIC -g -c -o mycalc-shared.o $<
	gcc -g -c -o mycalc-nofpic-shared.o $<
	gcc -shared -Wl,-Bsymbolic -Wl,-Bsymbolic-functions mycalc-shared.o -o libmycalc.so -Wl,-soname,libbar.so.1.0.0 
	@#gcc -shared mycalc-nofpic-shared.o -o libnopicmycalc.so

static:mycalc.c
	gcc -g -c -o mycalc-static.o $<
	ar -rc libmycalc.a mycalc-static.o 

clean:
	@rm -f *.o
	@rm -f *.a 
	@find . -maxdepth 1 -type f -executable -exec rm -f {} \;

#使用static来连接C库和不适用static来链接C库
exer: exercise-41-1.c
	gcc -Wl,-Bdynamic exercise-41-1.c -o exercise-41-1-d
	gcc -static -Wl,-Bstatic -L/lib/x84_64-linux-gnu exercise-41-1.c -o exercise-41-1-s
	@#或者可以直接使用-static选项
	@#gcc -static exercise-41-1.c -o exercise-41-1-s

#符号版本化
sv:sv_lib_v1.c sv_prog.c
	gcc -c -fPIC -o sv_lib_v1.o sv_lib_v1.c
	@#增加版本脚本来控制输出
	gcc -shared -o libsv1.so sv_lib_v1.o -Wl,-version-script,sv_v1.map
	gcc -g -o p1 sv_prog.c -L. -lsv1 -Wl,-z,origin '-Wl,-rpath,$$ORIGIN'

