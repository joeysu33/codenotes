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

void
showPthread(const char* title) {
    printf("%s: 0x%lx\n", title, pthread_self());
}

int
main() {
    int s;
    void *retval;

    showPthread("Main pthread");
    /*!pthread_join自身会导致死锁，貌似目前操作系统自身可以检测出来*/
    /*! EDEADLOCK = 35 */
    s = pthread_join(pthread_self(), &retval);
    if(s) {
        printf("pthread_join:s=%d,%s.\n",s,strerror(s));
        return 1;
    }
    return 0;
}


