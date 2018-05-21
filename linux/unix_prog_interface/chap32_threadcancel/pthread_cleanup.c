/*!
 * Cancel thread and Cleanup
 *
 * API:
 * int pthread_cancel(pthread_t thread); //取消线程的执行
 * void pthread_testcancel(void); //自定义取消点，而不是耗时函数一类的，用于计算密集型
 * int pthread_setcancelstate(int state, int* oldstate); //设置取消的状态，是否支持取消功能，如果不支持，收到取消操作后，取消操作会被挂起
 * int pthread_setcanceltype(int type, int* oldtype); //设置取消的类型,PTHREAD_DEFERED, PTHREAD_ASYNCHRONOUS
 *
 * void pthread_cleanup_push(void (*routine)(void*), void*arg); //清理入栈
 * void pthread_cleanup_pop(int execute); //清理出栈,当线程终止或cancel的时候执行,如果execute不为0，始终执行
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
#include <stdint.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
static int16_t glob ;

void
pthread_cleanup(void*);
void
showError(int);

void*
threadfunc(void *arg) {
    int i,s;
    void *buf = NULL;

    buf = malloc(1*1024*1024);  /*!非取消点*/
    printf("thread[%ld]: allocated memory:%p.\n", pthread_self(),buf);

    s = pthread_mutex_lock(&mtx); /*!非取消点*/
    printf("lock mutex:%p\n", &mtx);
    if(s) {
        showError(s);
    }

    pthread_cleanup_push(pthread_cleanup, buf); //清理函数入栈
    while(glob == 0) {
        s =  pthread_cond_wait(&cond,&mtx);
        if(s) showError(s);
    }
    printf("thread[%li]: condition wait completed.\n", pthread_self());
    pthread_cleanup_pop(1); //参数为0不执行，1任何情况都执行
    return NULL;
}

void
pthread_cleanup(void *arg) {
    int s;
    free(arg);
    printf("free allcated memory:%p.\n", arg);
    s = pthread_mutex_unlock(&mtx);
    printf("unlock mutex:%p\n", &mtx);
    if(s) showError(s);
}

void 
showError(int errNum) {
    char s[128];
    strerror_r(errNum, s, sizeof(s));
    printf("errNum:%d, %s.\n", errNum, s);
    exit(1);
}

int main(int argc, char *argv) {
    int s;
    pthread_t tid;
    void *retval;

    printf("main-thread[%ld].\n", pthread_self());
    s = pthread_create(&tid, NULL, threadfunc,NULL);
    if(s) {
        showError(s);
    }

    sleep(3); /*!保证线程一上来就执行到了pthread_cond_wait代码处*/

    if(argc == 1) {
        printf("main: about to cancel thread.\n");
        s = pthread_cancel(tid);
        if(s) showError(s);
    } else {
        printf("main: about to signal condition variable.\n");
        glob = 1; /*!退出条件*/
        s = pthread_cond_signal(&cond); /*! 释放条件信号*/
        if(s) showError(s);
    }

    s = pthread_join(tid, &retval);
    if(s) showError(s);

    if(retval == PTHREAD_CANCELED) {
        printf("main: thread was canceled!\n");
    } else {
        printf("main: thread terminated normally!\n");
    }

    return 0;
}


