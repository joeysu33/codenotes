/*!
 * 获取默认进程的信号掩码
 */

#include <signal.h>
#include <string.h> //support strsignal
#include <stdio.h>

void
dumpSigSet(sigset_t *s) {
    /*!在异步信号中不可使用stdio,在此函数中printf仅供测试 */
    int i;
    for(i=1; i<NSIG; ++i) {
        if(sigismember(s, i)) {
            printf("\tsignal %d : %s\n", i, strsignal(i));
        }
    }
}

int
main(int argc, char*argv[]) {
    sigset_t sigProcMask;
    /*!
     * 如果仅获取当前进程的信号掩码，可以直接将set的掩码置为空指针
     * int sigprocmask(int flag, sigset_t* new, sigset_t* old);
     * flag:
     * SIG_BLOCK: new和old并集
     * SIG_UNBLOCK: old - new
     * SIG_SETMASK: 使用new替换old
     * 如果将new设置为NULL,则忽略flag标志位
     */
    if(sigprocmask(0, NULL, &sigProcMask) == -1) {
        perror("sigprocmask ");
        return 1;
    }

    printf("Signal process mask:\n");
    dumpSigSet(&sigProcMask);

    return 0;
}
