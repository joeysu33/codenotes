/*!
 * 创建Posix的消息队列
 * -n 消息队列的名称
 * -c 创建一个新的消息队列
 * -x 以独占方式来创建一个新的消息队列
 * 
 * mode = 0666
 */

#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int i, j, ok;
    int oflags, mode;
    char *ar, *name;
    mqd_t mqd;

    ok = 0;
    for(i=1; i<argc; ++i) {
       ar = argv[i];
       if(*ar != '-') continue;
       switch(*(ar+1)) {
           case 'n': {
                         i++;
                         if(i>=argc) {
                             fprintf(stderr, "Invalid arguments\n");
                             return 1;
                         }
                         ar = argv[i];
                         if(ar[0] != '/') {
                             fprintf(stderr, "Invalid mqueue name, start with \"/\"");
                             return 1;
                         }
                         name = ar;
                         ok++;
                         break;
                     }
           case 'c': oflags = O_CREAT; ok++; break;
           case 'x': oflags = O_CREAT | O_EXCL; ok++; break;
       }

       if(ok >= 2) break;
    }

    if(ok < 2) {
        fprintf(stderr, "Arguments is not completed!");
        return 1;
    }

    mqd = mq_open(name, oflags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,NULL);
    if(mqd < 0) {
        perror("mq_open");
        return 1;
    }

    printf("%s: posix message queue create successufly!\n", name);
    return 0;
}

