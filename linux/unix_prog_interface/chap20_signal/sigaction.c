/*!
 * 使用sigaction来控制信号行为,相比较signal
 * sigaction更加具备可移植性和更好的控制性，
 * sigaction在设置进入信号处理函数的时候，会
 * 自动将本信号加入屏蔽，避免自递归信号操作
 */

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void
hanlder_signals(int sig) {
}


void
dumpSigAction(int sig, struct sigaction *sa) {
    if(!sa) return ;
    char buf[16];
    /*!
     * 忽略该信号
     */
    if(sa->sa_handler == SIG_IGN) {
        strcpy(buf, "忽略");
    } else if(sa->sa_handler == SIG_DFL) {
        strcpy(buf, "默认");
    } else {
        sprintf(buf, "0x%p", sa->sa_handler);
    }

    printf("signal-%d : %s, 行为:%s\n", sig, strsignal(sig), buf);
}

int
main() {
   int i;
   struct sigaction sa;

   /*!显示当前信号的默认行为*/
   for(i=1; i<NSIG; ++i) {
       if(sigaction(i, NULL, &sa) == -1) {
           return 1;
       } else {
           dumpSigAction(i, &sa);
       }
   }

   return 0;
}

