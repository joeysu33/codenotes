/*!
 * pthread stack details
 *
 * int pthread_attr_getstack(const pthread_attr_t* attr, void** stackaddr, size_t *stacksize);
 * pthread_attr_getstackaddr
 * pthread_attr_getstacksize
 *
 * int pthread_attr_setstack(pthread_attr_t* attr, void*stackaddr, size_t* stacksize);
 * pthread_attr_setstackaddr
 * pthread_attr_setstacksize
 */

#define _GNU_SOURCE /*! pthread_getattr_np is not posix interface*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void
errExit(int errNum) {
    char buf[128], errbuf[128];
    strerror_r(errNum, errbuf, sizeof(errbuf));
    snprintf(buf, sizeof(buf), "errNum:%d, errors:%s.\n", errNum, errbuf);
    fprintf(stderr,"%s",buf);
    exit(1);
}

void
showThreadStack(pthread_attr_t *attr) {
    int s;
    void *stackaddr;
    size_t stacksize;

    pthread_mutex_lock(&mtx);
    s = pthread_attr_getstack(attr, &stackaddr, &stacksize);
    if(s) {
        pthread_mutex_unlock(&mtx);
        errExit(s);
    }
    printf("thread[%ld] :stackaddr:%p, stacksize:%ld.\n", pthread_self(), stackaddr, stacksize);
    pthread_mutex_unlock(&mtx);
}

void*
threadFunc(void* arg) {
    int s;
    pthread_attr_t attr;
    s = pthread_getattr_np(pthread_self(), &attr);
    if(s) errExit(s);
    showThreadStack(&attr);

    return NULL;
}

int 
main() {
    int s;
    pthread_t tid;
    pthread_attr_t attr;

    printf("main-thread:%ld\n", pthread_self());
    s = pthread_create(&tid, NULL, threadFunc, NULL);
    if(s) errExit(s);

    s = pthread_getattr_np(pthread_self(), &attr);
    if(s) errExit(s);
    showThreadStack(&attr);

    s = pthread_join(tid, NULL);
    if(s) errExit(s);

    printf("Exit normally!\n");
    return 0;
}



