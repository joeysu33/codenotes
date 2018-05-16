/*!
 * 使用条件等待实现生产者和消费者
 * pthread_cond_t
 * pthread_condattr_t
 *
 * int pthread_cond_signal(pthread_cond_t* cond);
 * int pthread_cond_boardcast(pthread_cond_t* cond);
 * int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);
 * int pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex, const struct timespec* ts);
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
static long long res;
static const int maxres = 10;

void
showRes(const char *s) {
    printf("%s:res=%lli\n", s,res);
}


void*
product(void *arg) {
    for(;;) {
        pthread_mutex_lock(&mtx);
        showRes("before product");
        /*!while语句判断条件是否成立*/
        while(res == maxres) {
            pthread_cond_wait(&cond, &mtx);
        }
        res++;
        showRes("after product");
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond);
    }
}

void* 
consumer(void *arg) {
    for(;;) {
        pthread_mutex_lock(&mtx);
        showRes("before consume");
        /*!while语句判断条件是否成立*/
        while(res == 0) pthread_cond_wait(&cond, &mtx);
        res--;
        showRes("after consume");
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond);
    }
}

void
showError(int s, const char* title){
    char buf[128];
    if(strerror_r(s, buf, sizeof(buf))) {
        perror("strerror");
        exit(1);
    }

    pthread_mutex_lock(&mtx2);
    printf("%s: %s.\n", title, buf);
    pthread_mutex_unlock(&mtx2);
}

typedef void* (*THREAD_FUNC)(void*);

int
main() {
    pthread_t tid[2];
    THREAD_FUNC tf[2] = { product, consumer };
    int i, j, s;

    for(i=0; i<2; ++i) {
        s = pthread_create(&tid[i], NULL, tf[i], NULL);
        if(s) {
            showError(s, "pthread_create");
        }
    }

    for(i=0; i<2; ++i) pthread_join(tid[i], NULL);
    return 0;
}


