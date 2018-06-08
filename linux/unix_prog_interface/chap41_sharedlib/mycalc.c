#include <stdio.h>
#include <assert.h>

int add(int a, int b) {
    return a+b;
}

int divide(int a, int b) {
    if(b == 0) {
        assert(0);
        return 0;
    }

    return a/b;
}

int sub(int a, int b) {
    return a-b;
}

int multipy(int a, int b) {
    return a*b;
}

int main() {
    printf("What can i do 4 u!!!\n");
    return 0;
}
