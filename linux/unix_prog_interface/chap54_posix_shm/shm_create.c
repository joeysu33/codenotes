/*!
 * 创建一个Posix的共享内存
 * argv[0] /shm-name
 * 创建成功之后/dev/shm下会创建一个对应的共享内存文件对象
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int
main(int argc, char *argv[]) {
    char *name ;
    int oflags, mode;
    if(argc != 2) {
        return 1;
    }
    name = argv[1];
    oflags = O_CREAT | O_EXCL | O_RDWR;
    mode = 0666; //& umask

    if(shm_open(name, oflags, mode) < 0) {
        perror("shm_open");
        return 1;
    }

    printf("create posix shm %s success!\n", argv[1]);

    return 0;
}
