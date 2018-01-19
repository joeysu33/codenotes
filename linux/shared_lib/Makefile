app: app.o 
	gcc -o app app.o -L. -ltest 
app.o: app.c testlib
	gcc -g -c -o app.o app.c 
testlib: testlib.c
#always libXXX.so
	gcc -shared -fPIC -o libtest.so testlib.c

app++: app++.cpp testlib
	g++ -std=c++14 -o app++ app++.cpp -L. -ltest

clean:
	@find . -maxdepth 1 -executable -type f -exec rm  {} \;
	@find . -maxdepth 1 -type f -iname "*.o" -exec rm {} \;

