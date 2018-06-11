#include <stdio.h>

static int si;
int ig;

/*!在符号表中.symtab，GLOBAL*/
void m1() {
    printf("dynamic_exec m1 called!\n");
}

/*!
 * 在符号表.symtab中显示为LOCAL,本地可见*/
void __attribute__((visibility("hidden")))
m2() {
    printf("dynamic_exec m2 called!\n");
}

/*!在符号表.symtab中显示为LOCAL，本地可见*/
static void 
m3() {
    printf("dynamic_exec m3 called!\n");
}

int
main(int argc, char* argv[]) {
    printf("%s:\n", argv[0]);
    return 0;
}
