/*!
 * 访问的地址（总线）不对齐
 */

#include <signal.h>
#include <string.h> //strsignal
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void 
sigact(int sig) {
    printf("%s\n", strsignal(sig));
    fflush(stdout);
    exit(1);
}

void
sigact2(int sig, siginfo_t *si, void *ucontext) {
    printf("signal:%d, code=%d\n", si->si_signo, si->si_code);
}

int
main(int argc, char *argv[]) {
    /*! 0x00000001 报错是sigsegv
     * 0x00001111报错是sigbus*/

    int *pi ;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = sigact2;
    sa.sa_flags = SA_SIGINFO;
    assert(sigaction(SIGBUS, &sa, NULL) >= 0);
    //signal(SIGBUS, sigact);
    pi= (int*)0x00001111;
    *pi = 1;
    return 0;
}


