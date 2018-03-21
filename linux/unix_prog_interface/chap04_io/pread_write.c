/*
 * 带seek功能的read/write,保证了lseek和read/write的原子性操作
 * int pread(int fd, void* buf, size_t n, off_t offset);
 *  -fd 文件描述符
 *  -buf 读取数据的缓存
 *  -n 读取数据的字节大小
 *  -offset 读取数据开始的偏移位置（从文件起始位置开始)
 * int pwrite(int fd, void*buf, size_t n , off_t offset);
 */

#include "../common/common.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i,j, fd, rdlen, cnt;
    int oflags=0; //None read:1 write:2 rdwr:3
    //int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int mode=0666;
    off_t oft;
    char *filename, *endptr;
    char buf[64];
    if(argc < 3) err_exit("Too less arguments, %s filename [r|w]d", argv[0]);
    filename = argv[1];
    oft = strtol(argv[2],&endptr, 0);
    if(oft <= 0) err_exit("Invalid argument offset");
    if(strlen(argv[2]) < 2) { err_exit("Invalid arguments."); }
    if(tolower(argv[3][0]) == 'r') {
        oflags = O_RDONLY;
        rdlen = strtol(&argv[3][1], &endptr, 0);
        if(rdlen < 0 || rdlen > 64) err_exit("Invalid read length");
    } else {
        oflags = O_WRONLY | O_CREAT;
        if(strlen(&argv[3][1]) > 63) { err_exit("Too long to write!!"); }
        snprintf(buf, 64, "%s", &argv[3][1]);
    }

    //如果不设置mode,那么文件的属性则全部不可用-------
    fd = open(filename, oflags, mode);
    if(fd < 0) err_exit("open failed");
    cnt=0;
    i=0;
    //O_RDONLY 0
    if(oflags == O_RDONLY) {
        while(cnt != rdlen) {
            if((i=pread(fd, buf+i, rdlen-cnt, oft)) < 0) { err_exit("pread"); }
            cnt += i;
        }
        printf("offset:%ld readNum:%d\n", oft, rdlen);
        for(i=0; i<rdlen;++i) {
            printf("%x ",buf[i]);
        }
        printf("\n");
    } else {
        j = strlen(buf);
        while(cnt != j) {
            if((i=pwrite(fd, buf+i,j-cnt, oft)) < 0) err_exit("pwrite");
            cnt += i;
        }
        printf("offset:%ld writeNum:%d\n", oft, j);
        printf("%s", buf);
    }
    close(fd);
    return 0;
}

