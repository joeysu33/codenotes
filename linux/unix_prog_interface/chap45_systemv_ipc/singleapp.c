/*!
 * 使用System信号量(id)来构建一个单体应用程序
 * SystemV的信号量和消息队列的生命周期都是长期的（除非系统关闭，非引用计数),
 * -----获取使用XXXctl函数IPC_RMID来删除----
 * 共享内存的声明周期和引用计数有关系
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h> //open O_ S_I
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define FILEPATH "/tmp/singleapp.sem"
#define handle_error(s) \
    do { perror(s); exit(EXIT_FAILURE); } while(0)

int main(int argc, char *argv[]) {
    int fd;
    struct stat sb;
    key_t k;
    int semid;

    if(stat(FILEPATH, &sb) < 0) {
        fd = open(FILEPATH, 
                O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if(fd < 0) {
            handle_error("open");
        }
        close(fd);
    }

    k = ftok(FILEPATH, 1);
    semid = semget(k, 1, 
                IPC_CREAT | IPC_EXCL | 
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) ;
    printf("k=0x%x\nsemid=%d\n", k,semid);
    if (semid < 0) {
        if(errno == EEXIST) {
            printf("Instance is existd!\n");
            return 0;
        } else {
            handle_error("semget");
        }
    }

    printf("New instance created!\n");
    sleep(10);
    return 0;
}


