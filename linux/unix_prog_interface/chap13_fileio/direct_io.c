/*!
 * 直接对硬盘进行IO操作
 * 不仅读取的位置要对齐，而且内存的缓冲也要做到对齐，
 * 获取磁盘上的对齐大小调用blockdev --getss /dev/sda9
 * 获取当前文件系统: df -h
 * O_DIRECT
 */

//特殊用途
#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include "../common/common.h"

int
main(int argc, char *argv[]) {
    int i;
    int fd;
    char *buffer;
    char *endptr;
    off_t offset;
    long readBytes;
    long bufSize;
    long readSize;

    if(argc < 3) {
        err_exit("Too less argument :%s filename read-bytes [offset, [read-num]]", argv[0]);
    }
    readBytes = strtol(argv[2], &endptr, 0);
    if(readBytes < 0 ) err_exit("Invalid readBytes! ");
    offset = 0;
    if(argc > 3 ) {
        offset = strtol(argv[3], &endptr, 0);
    }

    bufSize = 512;
    if(argc > 4 ) {
        bufSize = strtol(argv[4], &endptr, 0);
    }
    if(bufSize < 0) {
        bufSize = 512;
    }
    //buffer = malloc(bufSize);
    //读取的buffer需要内存对齐
    buffer = memalign(512, bufSize);
    printf("buffer=%p\n", buffer);
    char *tbuf = malloc(512);
    printf("tbuf=%p\n", tbuf);
    free(tbuf);

    if(!buffer) {
        err_exit("malloc ");
    }

    /*!以直接IO的方式打开读写 O_DIRECT建议和O_SYNC一起使用*/
    fd = open(argv[1], O_RDONLY | O_DIRECT);
    if(fd == -1) {
        free(buffer);
        err_exit("open failed:%s ", argv[1]);
    }

    if(lseek(fd, offset, SEEK_SET) == -1) {
        free(buffer);
        close(fd);
        err_exit("lseek ");
    }

    printf("off=%ld file=%s bufSize=%ld readSize=%ld\n", offset, argv[0], bufSize, readBytes);
    while(readBytes) {
        if(readBytes > bufSize) {
            readSize = bufSize;
        } else {
            readSize = readBytes;
        }

        if(read(fd, buffer, readSize) == -1) {
            free(buffer);
            close(fd);
            err_exit("read ");
        }

        readBytes -= readSize;
    }

    free(buffer);
    close(fd);

    return 0;
}



