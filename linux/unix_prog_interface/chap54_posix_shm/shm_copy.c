/*!
 * 指定共享内存名称，将指定的字符串拷贝进去
 * 由于posix的共享内存段是基于文件，可以使用
 * ftruncate来修改大小,而system-v和mmap不可以
 * 还可以使用fstat来查看共享内存段(文件）的权限
 * 
 * 直接使用close来关闭文件描述符
 * PROT的写权限，默认隐含读 PROT_WRITE <=> PROT_WRITE | PROT_READ
 * 否则权限失败
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <memory.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    int fd ,mode, oflags, size;
    char *name;
    void *addr;

    if(argc != 3) {
        return 1;
    }

    name = argv[1];
    oflags = O_RDWR;
    mode = 0; /*!仅创建的时候需要设置, 打开不用*/

    fd = shm_open(name, oflags, mode);
    if(fd < 0) {
        perror("shm_open");
        return 1;
    }

    /*!首先设置fd的文件大小，然后再映射到内存*/
    size = strlen(argv[2]) + 1;
    if(ftruncate(fd, size) < 0) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    /*!prot和文件的保持一致*/
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap()");
        close(fd);
        return 1;
    }

    strcpy(addr, argv[2]);
    munmap(addr, size);
    close(fd);
    printf("copy success:%s, size=%d\n", argv[1], size);

    return 0;
}

