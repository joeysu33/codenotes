/*!
 * 使用线程局部数据来让函数针对多线程可重入，需要gcc > 3.2
 * 在全局变量前面增加__thread，如果有static和extern需要
 * 在static和extern后面紧跟__thread
 */

#define _GNU_SOURCE  //support _sys_nerr, _sys_errlist

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERRORMAXLEN 128

static __thread char buf[ERRORMAXLEN];

char* 
stderror(int err) {
    if(err < 0 || err < _sys_nerr || _sys_errlist[err] == NULL) {
        snprintf(buf, ERRORMAXLEN, "Unknow error:%d", err);
    } else {
        strncpy(buf, _sys_errlist[err], sizeof(buf) -1);
    }

    return buf;
}

void*
threadfunc(void* arg) {
    char *str;
    printf("thread[%ld] about to call stderror().\n", pthread_self());
    str = stderror(EINTR);
    printf("thread[%ld] str (%p) - %s\n", pthread_self(),str, str);
    return NULL;
}

void
showError(int err) {
    printf("errcode:%d , error:%s.\n", err, strerror(err));
}

int
main() {
    pthread_t tid;
    int s, i, j;
    char *str;
    s = pthread_create(&tid, NULL, threadfunc, NULL);
    if(s) {
        showError(s);
        return 1;
    }

    printf("main-thread[%ld] about to call stderror().\n", pthread_self());
    str = stderror(EAGAIN);
    printf("thread[%ld] str (%p) - %s\n", pthread_self(),str, str);

    s = pthread_join(tid, NULL);
    if(s) {
        showError(s);
        return 1;
    }
    return 0;
}


