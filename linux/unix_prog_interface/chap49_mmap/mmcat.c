/*!
 * 对一个文件进行文件内存映射
 * 内存映射包含:
 * 1.文件内存映射
 * 2.匿名内存映射
 * 内存映射和POSIX的共享内存很亲密，都用的同一个头文件，同一套机制
 *
 * void* mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 * void* addr 自己指定映射地址，一般为NULL,系统分配，需要对齐页大小
 * size_t length 内存的大小
 * int prot 内存地址的保护权限 PROT_NONE, 区域无法访问(可以恶意让进程的存储分配但不可用,关联了物理存储), 或者PROT_READ|PROT_WRITE|PROT_EXEC,PROT_NONE,
 * int flags MAP_PRIVATE, MAP_SHARED, MAP_ANONYMOUS .....
 *
 * 最后两个参数是文件映射使用
 * int fd :文件描述符
 * offset_t offset :文件映射开始的偏移，必须是页大小的整数倍，一般是4K(4096b)
 *
 * int munmap(void* addr, size_t length);
 *
 * 注意事项
 * 1.调用mmap之后，如果文件不在使用可以直接调用close关闭文件描述符
 * 2.如果调用了mmap之后，但是并不访问内存映像，内存映像有可能不会更新（发生访问，引发系统中断
 *   才会将数据加入存储），所以如果对文件有变更，最好是在变更后再映射，避免
 *   出现映射和磁盘文件变更不匹配的情况。
 * 3.文件内存映射，如果对内存进行SHARED编辑，最好在munmap之前调用msync来同步数据到磁盘上。
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h> //STDIN_FILENO, STDOUT_FILENO

#include <sys/mman.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int i, j, fd,rn, wn;
    struct stat st;
    char *d;
    const size_t bufsize = 1024;
    size_t fsize;

    if(argc != 2) {
        fprintf(stderr, "%s <filename>\n", argv[0]);
        return 1;
    }

    rn = stat(argv[1], &st);
    if(rn < 0) {
        if(errno == ENOENT) {
            fprintf(stderr, "%s is not exists!\n", argv[1]);
            return 1;
        }

        perror("stat()");
        return 1;
    }

    /*!文件已经存在不需要设置permissoin, 创建的时候需要指定permission-mask*/
    fd = open(argv[1], O_RDONLY , 0);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    /*!创建文件映射，私有|可读*/
    d = (char*)mmap(NULL, st.st_size, 
            PROT_READ, MAP_PRIVATE, fd /*fd*/, 0/*fd offset*/);
    
    /*! MAP_FAILED (void*)-1 */
    if(d == MAP_FAILED) {
        perror("mmap()");
        close(fd);
        return 1;
    }

    /*
    for(fsize = 0 ; fsize < st.st_size; ) {
        wn = st.st_size - fsize;
        wn = wn > bufsize ? bufsize : wn;

        wn = write(STDOUT_FILENO, d+fsize, wn);
        fsize += wn;
    }*/

    for(fsize = st.st_size; fsize; ) {
        wn = fsize > bufsize ? bufsize : fsize;
        wn = write(STDOUT_FILENO, d+(st.st_size - fsize), wn);
        fsize -= wn;
    }


    if(munmap(d, st.st_size) < 0) {
        perror("munmap()");
        close(fd);
        return 1;
    }

    return 0;
}

