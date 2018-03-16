#include <stdio.h>

int add(int a, int b) { printf("finish by testlib2.\n"); return (a+b); }

int main() {
    printf("shared lib also can as exec,like libc!\n");
    return 0;
}
