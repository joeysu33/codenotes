/*!
 * System-V信号量的操作:
 * 1.信号量值增加+n
 * 2.信号量值减少（如果减少的值小于0,就会阻塞等到满足条件）
 * 3.判断并等待信号量值减到0
 *
 * +[num]nu :增加信号量
 * -[num]nu :减小信号量
 * 0nu      :等待信号量的值降为0
 *
 * 可以操作一组信号量（信号量集)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAXARRAY 10

char* 
getNumber(char *s, int *num) {
    int i;
    char buf[16];
    char *ep;

    *num = -1;
    if(!s || strlen(s) == 0) return NULL;
    for(i=0; *s && i<16; ++s) {
        if(!isxdigit(*s) || (*s != 'x') || (*s != 'X')) {
            buf[i++] = 0;
            break;
        }

        buf[i++] = *s;
    }

    if(i==16) 
        buf[i-1] = 0;
    else
        buf[i]=0;

    *num = strtol(buf, &ep, 0);
    return s;
}

void 
setFlags(char *s, int *flags) {
    if(!s || strlen(s) == 0) return ;
    if(strchr(s, 'n')) {
        *flags |= IPC_NOWAIT;
    }

    if(strchr(s, 'u')) {
        *flags |= SEM_UNDO;
    }
}

int
main(int argc, char *argv[]) {
    int i, j,rn, flags, val, id;
    char *cp, *ar;
    struct sembuf sb[MAXARRAY];

    id == -1;
    for(i=1, j=0; i<argc && j<MAXARRAY; ++i) {
        ar = argv[i];
        flags = 0;
        switch(*ar) {
            case '+': {
                          ar++;
                          cp = getNumber(ar, &val);
                          if(val < 0 || !cp) return 1;
                          setFlags(cp, &flags);
                          sb[j].sem_num = j; /*! index of sems gather */
                          sb[j].sem_op = val; /* operation */
                          sb[j].sem_flg = flags;
                          ++j;
                          break;
                      }
            case '-': {
                          ar++;
                          if(*ar == 'i') {
                              /*!id值*/
                              ++i;
                              if(i >= argc) return 1;
                              getNumber(argv[i], &id);
                          } else {
                              cp = getNumber(ar, &val);
                              if(val < 0 || !cp) return 1;
                              setFlags(cp, &flags);
                              sb[j].sem_num = j; /*! index of sems gather */
                              sb[j].sem_op = -val; /* operation */
                              sb[j].sem_flg = flags;
                              ++j;
                          }
                          break;
                      }
            case '0': {
                          ar++;
                          setFlags(ar, &flags);
                          sb[j].sem_num = j;
                          sb[j].sem_op = 0;
                          sb[j].sem_flg = flags;
                          ++j;
                          break;
                      }
                }
    }

    if(id < 0 || j==0) {
        return 2;
    }

    if(semop(id, sb, j) < 0) {
        perror("semop()");
        return 2;
    }

    printf("semop successfuly\n");
    return 0;
}

