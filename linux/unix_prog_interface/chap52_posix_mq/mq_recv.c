/*!
 * posix message queue receive
 * -n name
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h> //posix message queue
#include <string.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int i, j, ok;
    char *name, *msg, *cp, *endp ,*buf;
    int prio;
    char opt;
    mqd_t mqd;
    struct mq_attr attr;

    ok = 0;
    prio = 0;
    for(i=1; i<argc; ++i) {
        cp = argv[i];
        if(*cp != '-') continue;
        opt = *(++cp);
        if(opt == 'n') {
             ++i;
             if(i>=argc) {
                 fprintf(stderr, "Invalid arguments\n");
                 return 1;
             }
             cp = argv[i];
             name = cp; ok++; 
        }
    }

    if(ok < 1) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    mqd = mq_open(name, O_RDONLY);
    if(mqd < 0) {
        perror("mq_open");
        return 1;
    }

    if(mq_getattr(mqd, &attr) < 0) {
        perror("mq_getattr");
        mq_close(mqd);
        return 1;
    }

    buf = (char*)malloc(attr.mq_msgsize);
    assert(buf);

    i = mq_receive(mqd, buf, attr.mq_msgsize, &prio);
    if(i< 0) {
        perror("mq_receive");
        mq_close(mqd);
        return 1;
    }

    printf("received: prio=%d, msg:\n%s", prio, buf);

    mq_close(mqd);
    return 0;
}

