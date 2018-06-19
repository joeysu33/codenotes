/*!
 * -i msg的id值
 * -t msg的msgtype值
 * -m msg的msg
 * -n IPC_NOWAIT
 *
 * svmsq_send -i XXX -t 10 -m "XXX"
 * mtype 必须> 0
 *
 * msgget
 * msgctl
 * msgsnd
 *
 * msgsend的buf结构中第一个必须是long类型的mtype
 * 第二个必须是char[],直接存数据,可以是定长，也可以
 * 是变长,mtype必须>0
 *
 * struct msgbuf {
 *  long mtype;    //消息类型
 *  char mtext[1]; //消息内容
 * };
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>  //IPC
#include <sys/msg.h>  //msgget msgctl msgsnd msgrcv 
#include <sys/stat.h> //mkfifo fstat
#include <sys/wait.h> //wait waitpid
#include <unistd.h>
#include <stdlib.h> //strtol strtoul strtoll
#include <string.h>
#include <memory.h>
#include "svmsq_msg.h"

int 
main(int argc, char *argv[]) {
    int i,j, id, mtype, msgflg, n;
    char *cp, *ar, *msg;
    svmsq_msg2_t m;

    msgflg = 0;
    for(i=1, j=0; i<argc; ++i) {
        ar = argv[i];
        if(*ar != '-') continue;

        switch(ar[1]) {
            case 'i': {
                          if(i+1 >= argc) {
                              fprintf(stderr, "No id\n");
                              return 1;
                          }
                          id = strtol(argv[i+1], &cp, 0);
                          ++i; j++;
                          break;
                      }
            case 't': {
                          if(i+1 >= argc) {
                              fprintf(stderr, "No msgtype");
                              return 1;
                          }
                          mtype = strtol(argv[i+1], &cp, 0);
                          if(mtype <= 0) {
                              fprintf(stderr, "mtype < 0\n");
                              return 1;
                          }
                          ++i;j++;
                          break;
                      }
            case 'm': {
                          if(i+1 >= argc) {
                              fprintf(stderr, "No message");
                              return 1;
                          }
                          msg = argv[i+1];
                          if(strlen(msg) == 0) {
                              fprintf(stderr, "No msg");
                              return 1;
                          }
                          ++i;j++;
                          break;
                      }
            case 'n': {
                          msgflg = IPC_NOWAIT;
                          break;
                      }
        }
    }

    if(j != 3) {
        fprintf(stderr, "No complete infomartion!\n");
        return 1;
    }

    m.mtype = mtype;
    j = strlen(msg) > sizeof(m.msg) ? sizeof(m.msg) : strlen(msg) -1;
    memset(m.msg, 0, sizeof(m.msg));
    memcpy(m.msg, msg, j); //msgsz表示的是msgp中mtext的大小
    n = msgsnd(id, &m, j, msgflg);
    if(n<0) {
        perror("smgsnd()");
        return 1;
    }
    
    return 0;
}

