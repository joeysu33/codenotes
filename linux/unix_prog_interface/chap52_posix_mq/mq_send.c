/*!
 * posix message queue
 * -n name
 * -m message
 * -p prio
 */

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h> //posix message queue
#include <string.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int i, j, ok;
    char *name, *msg, *cp, *endp;
    int prio;
    char opt;
    mqd_t mqd;

    ok = 0;
    prio = 0;
    for(i=1; i<argc; ++i) {
        cp = argv[i];
        if(*cp != '-') continue;
        opt = *(++cp);
        if(opt == 'n' ||
                opt == 'm' ||
                opt == 'p') {
             ++i;
             if(i>=argc) {
                 fprintf(stderr, "Invalid arguments\n");
                 return 1;
             }
             cp = argv[i];
             switch(opt) {
                 case 'n': name = cp; ok++; break;
                 case 'm': msg = cp; ok++; break;
                 case 'p': prio = strtol(cp, &endp, 0); break;
             }
        }
    }

    if(ok < 2) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    mqd = mq_open(name, O_WRONLY);
    if(mqd < 0) {
        perror("mq_open");
        return 1;
    }

    i = mq_send(mqd, msg, strlen(msg)+1, prio);
    if(i< 0) {
        perror("mq_send");
        mq_close(mqd);
        return 1;
    }

    mq_close(mqd);
    return 0;
}

