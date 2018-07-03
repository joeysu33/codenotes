/*!
 * 无命名信号量
 * int sem_init(sem_t *sem, int shared, unsigned int value);
 * int sem_destroy(sem_t *sem);
 *
 * sem_post (+1)
 * sem_wait (-1)
 */

#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define NUMS 2
#define handle_error(rn, m) \
    do { if(rn) { errno = rn; perror(#m); exit(1); }  } while(0)

#define BUFSIZE 26
#define SUMSIZE 1024

static char buffer[BUFSIZE];
static sem_t s1, s2;
static unsigned int ind1, ind2; //=>ind1 = 0, ind2=0

void*
product(void *arg) {
    char c;
    for(;;) {
        sem_wait(&s1);
        c = ind1 % 26 + 'a';
        buffer[ind1 % BUFSIZE] = c;
        ++ind1;
        printf("[%c]", c);
        sem_post(&s2);
        if(ind1 == SUMSIZE) break;
    }
}

void*
consumer(void *arg) {
    char c;
    for(;;) {
        sem_wait(&s2);
        c = buffer[ind2 % BUFSIZE];
        ++ind2;
        printf("%c:", c); 
        sem_post(&s1);
        if(ind2 == SUMSIZE) break;
    }
}

void
init() {
    sem_init(&s1, 0, BUFSIZE); //productor
    sem_init(&s2, 0, 0); //=> consumer
}

void
clear() {
    sem_destroy(&s1);
    sem_destroy(&s2);
}

int
main(int argc, char *argv[]) {
    typedef void* (*PTHREAD_FUNC) (void*);
    PTHREAD_FUNC pf[NUMS] = { product, consumer };
    pthread_t t[NUMS];
    int i,j, rn;
    void *v;
    
    init();
    for(i=0; i<NUMS; ++i) {
        rn = pthread_create(&t[i], NULL, pf[i], NULL);
        handle_error(rn, pthread_create);
    }

    for(i=0; i<NUMS; ++i) {
        rn = pthread_join(t[i], &v);
        handle_error(rn, pthread_join);
    }

    clear();
    return 0;
}

