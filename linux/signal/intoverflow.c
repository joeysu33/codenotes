/*!
 * 测试整型溢出
 */

#include <signal.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    /*! Unsafe in sig asyncIO, printf, strsignal */
    printf("Receive signo:%d, %s, code=%d, strcode=%s.\n", sig, strsignal(sig), si->si_code,
            (si->si_code == FPE_INTOVF) ? "INTOVF" : "other");
}

int main() {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;

    if(sigaction(SIGFPE, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    int i,j,k;
    i=0x80000000;
    printf("i=%d\n", i);
    j=i*10;
    //k=1/0; //赋值才会生效，编译器自动优化

    return 0;
}

