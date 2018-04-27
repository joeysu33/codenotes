/*!
 * 异步信号中不可以调用含静态数据的函数，否则
 * 会导致再次调用会引发的上下文错误
 * 不可以调用的函数，例如printf，里面含有静态的buffer
 * getpwent，返回静态数据,time等
 */

#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

static const char* sc_s1 = "oooo";
static const char* sc_s2 = "xxxx";
static const char* sc_salt =  "xx";
static volatile sig_atomic_t handled;

void
handler_inter(int sig) {
    /*!这里调用非异步安全函数，可能会对程序有影响*/
    crypt(sc_s2, sc_salt);
    handled++;
}

int 
main() {
    char* cr1 ;
    struct sigaction sa;
    int mismatch, callnum;
    cr1 = strdup(crypt(sc_s1, sc_salt));
    if(!cr1) {
        perror("strdup ");
        return 1;
    }

    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler_inter;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }
    
    printf("开始执行测试...\ncr1=%s\n", cr1);
    for(callnum=0, mismatch=0;;) {
        if(strcmp(crypt(sc_s1, sc_salt), cr1)) {
            mismatch++;
            printf("不匹配, handled=%d, callnum=%d, mismatch=%d\n", handled, callnum, mismatch);
        }
        callnum++;
    }

    free(cr1);
    return 0;
}

