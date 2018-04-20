/*!
 * 使用puase来阻塞进程，直到捕捉到信号位置
 * 
 * 信号错误
 * #define SIG_ERR (void(*)(int))-1
 * 默认信号
 * #define SIG_DEF (void(*)(int))0
 * 忽略信号
 * #define SIG_IGN (void(*)(int))1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pause(), wait 4 signals
#include <signal.h>

static void 
handler_signals(int sig) {
    /*!Unsafe: This hanlders uses non-async-signal-safe function*/
    /*printf() exit() */

    static int cnt = 0;
    if(sig == SIGINT) {
        cnt++;
        printf("捕捉到信号 SIGINT:(%d) \n", cnt);
        return ;
    }

    printf("捕捉到信号 SIGQUIT - that's all folks!\n");
    exit(EXIT_SUCCESS);
}

int
main() {
    /*!Establish same handler for SIGINT and SIGQUIT */
    if(signal(SIGINT, handler_signals) == SIG_ERR)
        return 1;
    if(signal(SIGQUIT, handler_signals) == SIG_ERR)
        return 2;

    for(;;) pause();
    return 0;
}


