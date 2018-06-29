/*!
 * 查看posix mq的属性
 * -n name
 */

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>

void
showMQ(struct mq_attr *attr) {
    if(!attr) return ;
    printf("flags=%#lo, \
            maxmsg=%ld,\
            max-msgsize=%ld,\
            cur-msgs=%ld\n",
            attr->mq_flags, attr->mq_maxmsg, 
            attr->mq_msgsize, attr->mq_curmsgs);
}

int
main(int argc, char *argv[]) {
    int i,j;
    char *name, *cp;
    mqd_t mqd;
    struct mq_attr attr;

    for(i=1, name= NULL; i<argc; ++i) {
        cp = argv[i];
        if(*cp != '-') continue;
        if(*(++cp) == 'n') {
            name = argv[i+1]; /*may be name is NULL*/
            break;
        }
    }

    if(!name) {
        fprintf(stderr, "%s <mq_name>\n", argv[0]);
        return 1;
    }

    mqd = mq_open(name, O_RDONLY);
    if(mqd < 0) {
        perror("mq_open");
        return 1;
    }

    if(mq_getattr(mqd, &attr) < 0) {
        perror("mq_getattr");
        mq_close(mqd); /*!仅关闭描述符，不关闭消息队列,关闭消息队列mq_unlink*/
        return 1;
    }
    showMQ(&attr);
    mq_close(mqd);

    return 0;
}

