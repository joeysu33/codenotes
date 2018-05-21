/*!
 * Cancel thread
 *
 * API:
 * int pthread_cancel(pthread_t thread);
 * int pthread_setcancelstate(int state, int* oldstate);
 * int pthread_setcanceltype(int type, int* oldtype);
 *
 * pthread_cancelstate的取值
 * PTHREAD_CANCEL_DISABLE 设置为disable，则遇到取消操作pthread_cancel，则挂起该操作，操作不可中断的时候设置
 * PTHREAD_CANCEL_ENABLE
 *
 * pthread_canceltype的取值
 * PTHREAD_CANCEL_DEFERED      延迟取消，遇到取消点函数（一般是等待或IO)，或pthread_testcancel()
 * PTHREAD_CANCEL_ASYNCHRONOUS 异步取消
 */

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void*
threadfunc(void *arg) {
    int i;
    for(i=0;;) {
        sleep(1);
        i++;
        printf("[0x%ld] sleep counter:%d.\n", pthread_self(), i);
    }
    return NULL;
}

void 
showError(int errNum) {
    char s[128];
    strerror_r(errNum, s, sizeof(s));
    printf("errNum:%d, %s.\n", errNum, s);
    exit(1);
}

int main() {
    int s;
    pthread_t tid;
    void *retval;

    printf("main-thread[%ld].\n", pthread_self());
    s = pthread_create(&tid, NULL, threadfunc,NULL);
    if(s) {
        showError(s);
    }

    sleep(5);
    pthread_cancel(tid);
    s = pthread_join(tid, &retval);
    if(s) showError(s);

    return 0;
}


