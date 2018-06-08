#include <stdio.h>

extern int add(int a, int b);

int main() {
    printf("add(5,3)=%d\n", add(5,3));
    return 0;
}
