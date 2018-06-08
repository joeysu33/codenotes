#chap04_io Makefile

include ../Makefile.inc

all: exec shared static 

exec : shared main.c
	gcc -o test main.c -lmycalc -L. -Wl,-rpath,.
	@readelf -a test > test.elf

shared: mycalc.c
	gcc -fPIC -g -c -o mycalc-shared.o $<
	gcc -g -c -o mycalc-nofpic-shared.o $<
	gcc -shared mycalc-shared.o -o libmycalc.so -Wl,-soname,libbar.so.1.0.0 
	@#gcc -shared mycalc-nofpic-shared.o -o libnopicmycalc.so

static:mycalc.c
	gcc -g -c -o mycalc-static.o $<
	ar -rc libmycalc.a mycalc-static.o 

clean:
	@rm -f *.o
	@rm -f *.a 
	@find . -maxdepth 1 -type f -executable -exec rm -f {} \;
