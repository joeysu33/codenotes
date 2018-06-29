/*!
 * unlink mq
 */

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

/*!
 * argv的最后一个一定是一个空指针
 */

int
main(int argc, char *argv[]) {
    int i,j;
    char *cp, *name;

    name = NULL;
    for(i=1; i<argc; ++i) {
        cp = argv[i];
        if(*cp != '-') continue;
        if(*(cp+1) == 'n') {
            name = argv[i+1];
            break;
        }
    }

    if(!name) {
        fprintf(stderr, "Invalid arguments, %s <mq-name>\n", argv[0]);
        return 1;
    }

    if(mq_unlink(name) < 0) {
        perror("mq_unlink");
        return 1;
    }

    printf("mq_unlink %s successfuly!\n", name);
    return 0;
}
