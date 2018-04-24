/*!
 * 课后练习2
 * 编写一个程序展示当对信号的处置改为SIG_IGN时，程序看不到
 * （捕获)该信号
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void
action_handler(int sig){
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    /*!Don't use non-async func in handler,like printf, strsignal etc. */
    printf("Receive signal(%d): %s\n", sig, strsignal(sig));
    if(sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction ");
    }
}

int
main() {
    sigset_t s;
    struct sigaction sa;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sa.sa_handler = action_handler;
    sa.sa_flags = 0;

    /*!清除SIGINT掩码*/
    if(sigprocmask(SIG_UNBLOCK, &s, NULL) == -1) {
        perror("sigprocmask ");
        return 1;
    }

    if(sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
    }

    for(;;) {
        pause();
    }

    return 0;
}
