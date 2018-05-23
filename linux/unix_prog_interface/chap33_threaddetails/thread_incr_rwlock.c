/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
*
* pthread_rwlock_t 读写锁
* int pthread_rwlock_init(pthread_rwlock_t* rwlock, 
\*************************************************************************/

/* Supplementary program for Chapter 33 */

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static volatile int glob = 0;
static pthread_rwlock_t rwlock;

#define errExitEN(err,what) \
    do { errno = err; perror(what); exit(EXIT_FAILURE); }while(0)

static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j, s;

    for (j = 0; j < loops; j++) {
        s = pthread_rwlock_wrlock(&rwlock);
        if (s != 0)
            errExitEN(s, "pthread_rwlock_wrlock");

        loc = glob;
        loc++;
        glob = loc;

        s = pthread_rwlock_unlock(&rwlock);
        if (s != 0)
            errExitEN(s, "pthread_rwlock_unlock");
    }

    return NULL;
}

int
main(int argc, char *argv[])
{
    char *endptr;
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? strtol(argv[1], &endptr, 0) : 10000000;

    s = pthread_rwlock_init(&rwlock, 0);
    if (s != 0)
        errExitEN(s, "pthread_rwlock_init");

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}
