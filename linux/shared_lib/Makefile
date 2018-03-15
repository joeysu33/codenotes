app: app.o 
	gcc -o app app.o -L. -ltest 
app2:app.o testlib2
	gcc -o app2 app.o -L. -ltest2
app.o: app.c testlib
	gcc -g -c -o app.o app.c 
testlib: testlib.c
#always libXXX.so
	gcc -shared -fPIC -o libtest.so testlib.c
testlib2:testlib2.c
	gcc -shared -fPIC -o libtest2.so testlib2.c
app++: app++.cpp testlib
	g++ -std=c++14 -o app++ app++.cpp -L. -ltest

clean:
	@find . -maxdepth 1 -executable -type f -exec rm  {} \;
	@find . -maxdepth 1 -type f -iname "*.o" -exec rm {} \;

