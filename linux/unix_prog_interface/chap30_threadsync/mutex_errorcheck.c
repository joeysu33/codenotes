/*!
 * 互斥变量
 * 1.类型:
 * pthread_mutex_t
 * pthread_mutexattr_t
 * 2.函数:
 * int pthread_mutex_init(pthread_mutex_t* mtx, pthread_mutexattr_t *attr);
 * int pthread_mutex_destory(pthread_mutex_t* mtx);
 * int pthread_mutexattr_XXXX()
 * 2.1 pthread_mutexattr操作
 * init
 * destory
 * gettype (PTHREAD_MUTEX_NORMAL, PTHREAD_MUTEX_ERRORCHECK, PTHREAD_MUTEX_RECURSIVE)，其中PTHREAD_MUTEX_ERRORCHECK用来检测错误
 * settype
 * 2.2 pthread_mutex操作
 * init
 * destroy
 * lock
 * trylock
 * unlock
 *
 * 互斥变量使用的几个原则
 * 1.不要给没有加锁的mutex解锁
 * 2.不要给已经加锁的mutex加锁
 * 3.在递归调用中必须使用PTHREAD_MUTEX_RECURSIVE，(互斥量中会增加引用计数)
 * 4.多个互斥量的使用，需要保持层次一致性，避免死锁
 * 5.可以使用PTHREAD_MUTEX_ERRORCHECK来检测死锁
 * 6.PTHREAD_MUTEX_INITAILIZER 只能初始化静态pthread_mutex_t，不可初始化栈或堆上的
 *   使用PTHREAD_MUTEX_INITILAIZER初始化的可以不用释放内存
 * 7.pthread_mutex_t和pthread_mutexattr_t的生命周期要相同,(不确定是否必须)，建议相同
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static pthread_mutex_t mtx1 ;
static pthread_mutexattr_t mtxattr;

void
showMutexAttrType(int kind, const char* title) {
    char *s ;
    char buf[16];
    switch(kind) {
        case PTHREAD_MUTEX_NORMAL: s = "normal"; break;
        case PTHREAD_MUTEX_ERRORCHECK: s = "errorcheck"; break;
        case PTHREAD_MUTEX_RECURSIVE: s = "recursive"; break;
        default: snprintf(buf, sizeof(buf), "unknow:%d", kind); s = buf;
    }

    printf("%s: %s\n", title, s);
}

void
showMutexAttr(pthread_mutexattr_t* mtxattr, const char* title) {
    int kind;
    if(pthread_mutexattr_gettype(mtxattr, &kind)){
        perror("pthread_mutexattr_gettype");
        return ;
    }
    showMutexAttrType(kind, title);
}

int
main() {
    int s;
    if(pthread_mutexattr_init(&mtxattr)) {
        perror("pthread_mutexattr_init");
        return 1;
    }
    
    showMutexAttr(&mtxattr,"default-mutex");
    if(pthread_mutexattr_settype(&mtxattr, PTHREAD_MUTEX_ERRORCHECK)) {
        perror("pthread_mutexattr_settype");
        return 1;
    }
    showMutexAttr(&mtxattr,"errorcheck-mutex");
    if(pthread_mutex_init(&mtx1, &mtxattr)) {
        perror("pthread_mutex_init");
        return 1;
    }

    if(pthread_mutex_lock(&mtx1) ) {
        perror("pthread_mutex_lock");
        return 1;
    }
    /*!死锁*/
    s = pthread_mutex_lock(&mtx1);
    if(s) {
        printf("pthread_mutex_lock:s=%d,%s.\n", s,strerror(s));
        return 1;
    }
    printf("never show this!\n");
    return 0;
}


