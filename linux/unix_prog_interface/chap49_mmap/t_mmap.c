/*!
 * void* mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 * 本例子用来展示共享文件映射
 * 多个本例程执行来修改同一份内存数据(虚拟内存->同一份物理内存页)
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define MEM_SIZE 32

int
main(int argc, char *argv[]) {
    void *addr;
    char *file;
    char *str;
    int fd, i;

    if(argc != 3) {
        fprintf(stderr, "%s <string-name>\n", argv[0]);
        return 1;
    }

    file = argv[1];
    fd = open(file, O_RDWR, 0) ; //这里打开文件的mode属性和mmap的prot属性要一致,打开已经创建文件mode可以指定为0
    if(fd < 0) {
        fprintf(stderr, "%s open failed!\n", file);
        return 1;
    }

    str = argv[2];
    /*!映射一小部分文件内容*/
    addr = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap()");
        return 1;
    }
    printf("Current:%s\n", (char*)addr);

    /*!映射完成关闭文件描述符*/
    if(close(fd) < 0) {
        perror("close(fd)");
        return 1;
    }

    /*!字符串拷贝*/
    i = strlen(str);
    if(strlen(str) >= MEM_SIZE) {
        i = MEM_SIZE -1;
    }
    ((char*)addr)[i]=0;
    memset(addr, 0, MEM_SIZE);
    memcpy(addr,str,i);
    printf("Copy %s to memory\n", str);

    /*!同步到文件中*/
    if(msync(addr, MEM_SIZE, MS_SYNC) < 0) {
        perror("msync()");
        return 1;
    }

    if(munmap(addr, MEM_SIZE) < 0) {
        perror("munmap()");
        return 1;
    }
    return 0;
}


