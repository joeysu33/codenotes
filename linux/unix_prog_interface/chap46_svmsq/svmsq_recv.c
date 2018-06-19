
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "svmsq_msg.h"

/*!
 * msgget
 * msgrcv(id, buf, maxsize, mtype, msgflg); 
 * msgsize 在接收端表示的最大消息大小，只保存mtext的大小
 *
 * -i id
 * -t mtype
 * -n IPC_NOWAIT
 */

int 
main(int argc, char *argv[]) {
    int msgflg, i, j, checker, id, n;
    svmsq_msg2_t m;
    char *ar, *cp;

    msgflg = 0;
    for(i=1, checker=0; i<argc; ++i) {
        ar = argv[i];
        if(*ar != '-') continue;
        switch(*(++ar)) {
            case 'i': {
                          ++i;
                          if(i >= argc) {
                              fprintf(stderr, "No id");
                              return 1;
                          }
                          id = strtol(argv[i], &cp, 0);
                          ++checker;
                          break;
                      }
            case 't': {
                          ++i;
                          if(i >= argc) {
                              fprintf(stderr, "No mtype");
                              return 1;
                          }
                          /*!接收段mtype可以小于0,,作为优先级*/
                          m.mtype = strtol(argv[i], &cp, 0);
                          ++checker;
                          break;
                      }
            case 'n': {
                          msgflg = IPC_NOWAIT;
                          break;
                      }
        }
    }

    if(checker != 2) {
        fprintf(stderr, "Argument is not complete.\n");
        return 1;
    }

    memset(m.msg, 0, sizeof(m.msg));
    n = msgrcv(id, &m, MAXMSG, m.mtype, msgflg);
    if(n < 0) {
        perror("msgrcv");
        return 1;
    }

    printf("m.mtype=%ld, m.mtext=%s\n", m.mtype, m.msg);
    return 0;
}




