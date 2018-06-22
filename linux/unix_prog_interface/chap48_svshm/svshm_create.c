/*!
 * 创建共享内存段
 * shmget
 * shmat //打开共享内存段
 * shmdt //detach共享内存段
 * shmctl
 *
 * shmctl(id, IPC_RMID,....) //删除共享内存段
 * 
 * int shmget(key_t k, size_t size, int shmflg);
 * key_t k键值
 * size_t 共享内存大小
 * shmflg 标志位
 *
 * options:
 * -k key值
 * -f 文件名称
 * -s 共享内存大小
 *
 * -g 标志位 IPC_CREAT, IPC_EXCL (默认创建)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int
main(int argc, char *argv[]) {
    int i, j;
    key_t k;
    char *ar, *cp;

    for(i=1; i<argc; ++i) {
        ar = argv[i];
        if(*ar != '-')
            continue;
        ar++;
        switch(*ar) {
            case 'k': {
                          break;
                      }
            case 'f': {
                          break;
                      }
            case 's': {
                          break;
                      }
        }
    }

    return 0;
}

