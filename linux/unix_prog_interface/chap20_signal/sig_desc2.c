/*!
 * 信号描述
 * char* strsignal(int sig)
 * extern const char* sys_siglist[];
 * void psignal(int sig, const char* msg);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strsignal psignal

#include <unistd.h>
#include <signal.h> //defined NSIG

int
main() {
    int i;
    char buf[16];
    const int MAX_SIGNAL = 31;

    /*!
     * 1 ~ 31
     */
    for(i=1; i< NSIG; ++i) {
        printf("SIG[%d]:%s\n", i,strsignal(i));
    }

    printf("\n");
    for(i=1; i< NSIG; ++i) {
        snprintf(buf, sizeof(buf)-1, "%s-[%d] ", "signal", i);
        psignal(i, buf);
    }

    return 0;
}


