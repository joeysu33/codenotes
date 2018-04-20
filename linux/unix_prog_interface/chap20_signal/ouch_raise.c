/*!
 * 信号的处理机制
 * 信号的处理和中断是一致的，可以称为软中断
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>

void handler_intr(int sig) {
    printf("Ouch!!!");
}

int
main() {
    int i;
    signal(SIGINT, handler_intr);
    for(i=0; ;i++) {
        printf("tick:%d\n", i);
        sleep(1);
        raise(SIGINT);
    }

    return 0;
}

