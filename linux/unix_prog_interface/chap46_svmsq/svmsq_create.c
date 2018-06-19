/*!
 * System-V msq-create
 * msgget
 * msgctl
 *
 * shmget
 * shmdt
 * shmat
 * shmop
 *
 * semget
 * semctl
 *
 * -c 加上IPC_CREAT标志
 * -f ftok
 * -p key直接使用IPC_PRIVATE
 * -x IPC_EXCL
 * -k 自己指定key值
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) {
    int i, j, id;
    int flg;
    int msgflg;
    key_t k;
    char *arg, *cp;

    msgflg = 0;
    for(i=1, flg=0; i<argc; ++i) {
        arg = argv[i];
        if(arg[0] != '-') continue;

        switch(arg[1]) {
            case 'c': msgflg |= IPC_CREAT; break;
            case 'f': {
                          if(i+1 >= argc) {
                              fprintf(stderr, "No file name\n");
                              exit(1);
                          }
                          k = ftok(argv[i+1], 1);
                          if(k < 0) perror("ftok()");
                          flg = 1;
                          break;
                      }
            case 'p': k = IPC_PRIVATE; flg =1 ;break; /* IPC_PRIVATE 0xffffffff */
            case 'x': msgflg |= IPC_EXCL; break;
            case 'k': {
                          if(i+1 >= argc) {
                              fprintf(stderr, "No key value\n");
                              exit(1);
                          }
                          k = strtol(argv[i+1], &cp, 0);
                          msgflg = IPC_CREAT | IPC_EXCL; /*!存在k必须指定IPC_CREAT */
                          flg = 1;
                          break;
                      }
        }

        if(flg) break;
    }

    if(!flg) {
        fprintf(stderr, "No key is set!\n");
        return 1;
    }

    /*!设置默认的permission*/
    msgflg |=  S_IRUSR | S_IWUSR;
    id = msgget(k, msgflg);
    if(id < 0) {
        perror("msgget()");
        return 1;
    }

    printf("MSQID is generated successfully:%d\n", id);
    return 0;
}

