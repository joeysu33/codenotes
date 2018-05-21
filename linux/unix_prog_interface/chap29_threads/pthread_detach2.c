/*!
 * posix thread的使用
 * posix thread的函数返回值，0是成功，正数是错误值
 *
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start)(void*), void* arg);
 * void pthread_exit(void *retval);
 * pthread_t pthread_self(void);
 * int pthread_equal(pthread_t t1, pthread_t t2); //如果t1和t2相等则返回非0，否则返回0
 * int pthread_detach(pthread_t thread) ; //线程分离，可以在创建的时候pthread_attr_setdetachstate()...
 * int pthread_join(pthread_t thread) ;   //线程join，默认是PTHREAD_CREATE_JOINABLE，可以设置为PTHREAD_CREATE_DETACH
 *
 * 线程属性pthread_attr_t
 * int pthread_attr_init(pthread_attr_t *attr);
 * int pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
 * int pthread_attr_getdetachstate(pthread_attr_t* attr, int* detachstate);
 * int pthread_attr_destory(pthread_attr_t* attr);
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <memory.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void 
print(const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
}

void
showPthread(const char* title) {
    print("%s: 0x%lx\n", title, pthread_self());
}

void* 
pthread1(void *arg) {
    char buf[32];
    int cnt = 0;
    for(cnt = 4 * (long)arg; cnt;) {
        pthread_mutex_lock(&mtx);
        snprintf(buf, sizeof(buf)-1, "pthread-%ld, counter=%d", (long)arg, cnt--);
        showPthread(buf);
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    printf("pthread[%ld] ready to exit!\n", pthread_self());
    return arg;
}


int
main() {
    int s;
    int i, j;
    pthread_t pts[5];
    pthread_attr_t attr;
    void* retval;

    memset(pts, 0, sizeof(pts));
    if(pthread_attr_init(&attr)) {
        perror("pthread_attr_init");
        return 1;
    }

    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) {
        perror("pthread_attr_setdetach");
        return 1;
    }

    showPthread("Main pthread");
    /*! 这里需要注意的是，给pthread传递的参数
     * 如果指向的是同一块内存的话，可能会导致覆盖
     * 线程竞争*/
    for(i=0; i<sizeof(pts)/sizeof(pthread_t) -1 ; ++i) {
        s = pthread_create(&pts[i], NULL, pthread1, (void*)(i+1));
        if(s != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    assert(!pthread_create(&pts[4], &attr, pthread1, (void*)5));

    retval = NULL;
    /*! 如果join已经设置detach的线程会出错，段错误*/
    /*! 对于已经设置detach的线程，不可以再pthread_join*/
    for(i=0; i<sizeof(pts)/sizeof(pthread_t) -1; ++i) {
        s = pthread_join(pts[i], &retval); 
        if(s != 0) {
            perror("pthread_join");
            /*返回错误码,无效参数，有时候直接导致段错误*/
            print("s=%d, error=%s.\n",s, strerror(s));
            return 1;
        }
        print("pthread-%d [0x%lx]:finished\n", retval, pts[i]);
    }

    if(pthread_attr_destroy(&attr)) {
        perror("pthread_attr_destroy");
        return 1;
    }

    printf("main thread exit normally!\n");
    /*!提前终止主线程，detach的线程还是可以继续执行，detach的线程执行完自动释放资源
     * 不需要执行pthread_join操作*/
    pthread_exit(NULL);
    return 0;
}


