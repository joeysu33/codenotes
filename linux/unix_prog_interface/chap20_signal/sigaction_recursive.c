/*!
 * sigaction recursive
 * 由于sigaction在执行的过程中会默认屏蔽本身信号，所以
 * 不会立刻再次触发本身信号的终端
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h> //support strsignal

static volatile int s_cnt;

void
action_handler(int sig) {
    /*!It's not safe in async call */
    printf("Caught signal-(%d) : %s\n", sig, strsignal(sig));

    /*!不会再次中断递归，而是形成一次信号阻塞，这次调用完成之后
     * 再次进入本中断函数调用
     */
    raise(sig);
    printf("counter = %d\n", s_cnt++);
}


int
main(int argc, char* argv[]) {
    struct sigaction sa;

    /*!设置stdout无缓存*/
    if(setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        return 2;
    }

    sa.sa_handler = action_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGINT, &sa, NULL) == -1) {
        return 1;
    }

    for(;;)
        pause();

    return 0;
}

