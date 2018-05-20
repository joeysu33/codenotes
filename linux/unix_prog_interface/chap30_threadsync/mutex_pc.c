/*!
 * 使用mutex实现生产者和消费者
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
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
        if(res < maxres) res++;
        showRes("after product");
        pthread_mutex_unlock(&mtx);
    }
}

void* 
consumer(void *arg) {
    for(;;) {
        pthread_mutex_lock(&mtx);
        showRes("before consume");
        if(res > 0) res--;
        showRes("before consume");
        pthread_mutex_unlock(&mtx);
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


