/*!
 * 使用线程特有数据，将不可重入函数，转换为可重入函数，
 * pthread_key_t
 * pthread_once_t
 *
 * 涉及到的几个重要函数
 * int pthread_once(pthread_once_t* once, void (*)(void)); //初始化pthread_key
 * int pthread_key_create(pthread_key_t* k, void (*destorybuf) (void*)); //创建pthread_key_t
 * int pthread_key_delete(pthread_key_t k);
 *
 * void* pthread_getspecific(pthread_key_t k); //直接使用key获取thread specific data
 * int pthread_setspecific(pthread_key_t k);   //直接使用key获取thread specific data
 */

#define _GNU_SOURCE  //support _sys_nerr, _sys_errlist

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERRORMAXLEN 128

static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t key;

void 
destorySpecificData(void* d) ;

//case1: 创建一个线程特有数据键
void
onceInit() {
    int s ;
    s = pthread_key_create(&key, destorySpecificData);
    if(s) abort();
}

//case2:编写特有数据释放函数
void
destorySpecificData(void* d) {
    fprintf(stderr, "free data:%p\n", d);
    if(d) free(d);
}

char* 
stderror(int err) {
    int s;
    char *buf;
    void* d;

    s = pthread_once(&once, onceInit);
    if(s) {
        abort();
    }

    buf = pthread_getspecific(key);
    if(!buf) {
        d = malloc(ERRORMAXLEN);
        fprintf(stderr, "alloc data:%p.\n", d);
        s = pthread_setspecific(key, d);
        if(s) abort();
        buf = d;
    }

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


