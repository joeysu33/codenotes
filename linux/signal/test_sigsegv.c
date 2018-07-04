/*!
 * 测试sigsegv
 * 访问地址不合法
 */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strsignal

void sigact(int sig) {
    printf("%s\n", strsignal(sig));
    exit(1);
}

int
main(int argc, char *argv[]) {
    char *pc = (char*)0x00000001;
    signal(SIGSEGV, sigact) ;
    *pc = 1;
    return 0;
}


