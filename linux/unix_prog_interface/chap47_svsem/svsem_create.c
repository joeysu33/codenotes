/*!
 * 信号量创建
 * svsem_create 
 * -p IPC_PRIVATE
 * -k key
 * -f ftok
 */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int
main(int argc, char *argv[]) {
    int i, j,mode, cnt, flag, rn;
    key_t k;
    char *cp, *ar;

    mode = 0;
    flag = 0;
    cnt = 1; /*! 初始的信号量个数是1个 */
    for(i=1; i<argc; ++i) {
        ar = argv[i];
        if(*ar != '-') continue;
        switch(*(++ar)) {
            case 'p':{
                         k = IPC_PRIVATE;
                         mode = 1;
                         break;
                     }
            case 'k':{
                         ++i;
                         if(i >= argc) return 1;
                         k = strtol(argv[i], &cp, 0);
                         mode = 2;
                         flag |= IPC_CREAT;
                         break;
                     }
            case 'f':{
                         ++i;
                         if(i >= argc) return 1;
                         k = ftok(argv[i], 'f');
                         if(k < 0) {
                             perror("ftok()");
                             return 1;
                         }
                         flag |= IPC_CREAT;
                         mode = 3;
                         break;
                     }
            case 'n':{
                         ++i;
                         if(i >= argc) return 1;
                         cnt = strtol(argv[i], &cp, 0);
                         break;
                     }
            case 'g':{
                         ++i;
                         if(i>= argc) return 1;
                         /*!c:表示create x:表示exclude */
                         if(strchr(argv[i], 'c')) {
                             flag |= IPC_CREAT;
                         }
                         if(strchr(argv[i], 'x')) {
                             flag |= IPC_EXCL;
                         }
                         break;
                     }
        }
    }

    /*! cnt must > 0 */
    if(!mode || cnt<=0 ) return 1;

    /*!设置默认的权限flags*/
    flag |= S_IRUSR | S_IWUSR;

    rn = semget(k, cnt, flag);
    if(rn < 0) {
        if(errno == EEXIST) {
            printf("ID is created!\n");
            return 0;
        }

        perror("semget()");
        return 1;
    } 

    printf("key=%d, id=%d\n", k, rn);
    return 0;
}

