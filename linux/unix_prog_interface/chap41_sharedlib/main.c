#include <stdio.h>

extern int add(int a, int b);

int add(int a, int b) {
    fprintf(stdout, "main::add(%d,%d)=%d.\n",a, b, (a+b));
    return a+b;
}

int main() {
    printf("add(5,3)=%d\n", add(5,3));
    return 0;
}
