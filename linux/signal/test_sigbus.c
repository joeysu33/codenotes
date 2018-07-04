/*!
 * 访问的地址（总线）不对齐
 */

#include <signal.h>
#include <string.h> //strsignal
#include <stdlib.h>
#include <stdio.h>

void 
sigact(int sig) {
    printf("%s\n", strsignal(sig));
    exit(1);
}

int
main(int argc, char *argv[]) {
    /*! 0x00000001 报错是sigsegv
     * 0x00001111报错是sigbus*/
    int *pi = (int*)0x00001111;
    signal(SIGBUS, sigact);
    *pi = 1;
    return 0;
}


