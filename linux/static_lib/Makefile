string.a:string.c
	gcc -c -o string.o string.c
	ar -rcs $@ string.o
test:string.a
	gcc -o test test.c string.a
