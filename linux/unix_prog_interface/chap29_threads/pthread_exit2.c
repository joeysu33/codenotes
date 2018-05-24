/*!
 * 如果主线程调用pthread_exit()程序会退出吗
 * ，如果还有未完成的子线程,该子进程并不join
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define handle_error(s, what) \
    do { errno = s; perror(what); exit(1); } while(0)

void 
startwork(const char *s) {
    printf("%s:PID=%d, PPID=%d, TID=0x%lx.\n", s,
            getpid(), getppid(),pthread_self());
    printf("%s:Ready to call pthread_exit!\n", s);
}

void
endwork(const char *s) {
    printf("%s:Finish to call pthread_exit!\n", s);
}

void*
threadRun(void* v) {
    int i;
    
    startwork("threadRun");
    for(i=40; i; --i) {
        sleep(1);
        printf("counter:%d.\n", i+1);
    }
    endwork("threadRun");

    return NULL;
}

int 
main() {
    int s;
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    startwork("main");
    s = pthread_create(&tid, &attr, threadRun, NULL);
    if(s)  handle_error(s, "pthread_create");
    pthread_attr_destroy(&attr);

    pthread_exit(0);
    endwork("main");
    return 0;
}


