/*!
 * 使用SIGALRM和阻塞read来实现一个超时退出读操作
 */

#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <unistd.h>
#include <errno.h>

static volatile sig_atomic_t gotSignal ;

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    gotSignal = 1;
}

int
main() {
    char buf[16];
    struct sigaction sa;
    int savedError;

    memset(&sa, 0, sizeof(sa)); /*默认不设置标志位,C语言不像C++,RAII (Resource Aquire Is Initialization) */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags &= ~SA_RESTART; //去掉SA_RESTART标志位,多此一举，为了表示该标志位的重要性，如果存在，则无法超时
    sa.sa_sigaction = sigaction_handler; //设置处理函数
    if(sigaction(SIGALRM, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    /*! 如果3秒之内没有输入的话，直接退出阻塞状态*/
    alarm(3);
    if(read(STDIN_FILENO, buf, sizeof(buf)) < 0) {
        if(errno == EINTR) {
            printf("timeout\n");
        } else {
            perror("read");
            return 1;
        }
    }


    savedError = errno;
    alarm(0); //关闭alarm，避免errno被修改，先保存再恢复
    errno = savedError;

    return 0;
}


