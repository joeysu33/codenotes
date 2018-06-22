/*!
 * 用于联系gdb的测试程序
 */ 

#include <stdio.h>
#include <stdlib.h>

int fab(int x) {
    if(x <= 1) return 1;
    return fab(x-1) + fab(x-2);
}

int factorial(int x) {
    if(x <= 1) return 1;
    return x*factorial(x-1);
}

int
main(int argc, char *argv[]) {
    fab(10);
    factorial(10);
    return 0;
}
