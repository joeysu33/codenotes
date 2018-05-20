/*!
 * posix thread的使用
 * posix thread的函数返回值，0是成功，正数是错误值
 *
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start)(void*), void* arg);
 * void pthread_exit(void *retval);
 * pthread_t pthread_self(void);
 * int pthread_equal(pthread_t t1, pthread_t t2); //如果t1和t2相等则返回非0，否则返回0
 * int pthread_detach(pthread_t thread) ; //线程分离，可以在创建的时候pthread_attr_setdetachstate()...
 * int pthread_join(pthread_t thread, void** retval) ;   //线程join，默认是PTHREAD_CREATE_JOINABLE，可以设置为PTHREAD_CREATE_DETACH
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

void
showPthread(const char* title) {
    printf("%s: 0x%lx\n", title, pthread_self());
}

void* 
pthread1(void *arg) {
    char buf[16];
    snprintf(buf, 10, "pthread-%ld", (long)arg);
    showPthread(buf);
    sleep(2);
    return arg;
}

void*
pthread2(void *arg) {
    return NULL;
}


int
main() {
    int s;
    int i, j;
    pthread_t pts[5];
    int retval;

    showPthread("Main pthread");
    /*! 这里需要注意的是，给pthread传递的参数
     * 如果指向的是同一块内存的话，可能会导致覆盖
     * 线程竞争*/
    for(i=0; i<sizeof(pts)/sizeof(pthread_t); ++i) {
        s = pthread_create(&pts[i], NULL, pthread1, (void*)(i+1));
        if(s != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for(i=0; i<sizeof(pts)/sizeof(pthread_t); ++i) {
        /*!这里要注意的是第二个参数是void**，
         * 这里直接给成void*,导致出错*/
        s = pthread_join(pts[i], (void*)&retval);
        if(s != 0) {
            perror("pthread_join");
            printf("s=%d.\n",s);
            return 1;
        }
        printf("pthread-%d [0x%lx]:finished\n", retval, pts[i]);
    }

    return 0;
}

