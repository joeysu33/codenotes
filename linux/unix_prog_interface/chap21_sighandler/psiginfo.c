/*!
 * 调用api打印siginfo的信息和strsignal类似
 * void psignal(int sig, const char* s);
 * void psiginfo(siginfo_t* si, const char* s);
 *
 * extern const char* const sys_siglist[];
 * strsignal
 *
 * ----psignal
 * ----psiginfo
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void
sighandler(int sig, siginfo_t* si, void* ucontext) {
    psignal(sig, "psignal");

    /*! ------Unsafe----- */
    printf("\n---------------------------\n");
    psiginfo(si, "psiginfo");

    /*!
     * 终端默认的kill 操作
     */
    if(sig == SIGTERM) {
    }
}

int
main() {
    struct timespec ts;
    struct sigaction sa;

    ts.tv_sec = 2;
    ts.tv_nsec = 0;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = sighandler;

    if(sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    if(sigaction(SIGTERM, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    for(;;) pause;
    return 0;
}

