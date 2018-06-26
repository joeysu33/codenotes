/*!
 * 使用mmap来进行数据拷贝
 *
 * 注意事项
 * 1.mmap的时候如果需要PROT_WRITE，有时会隐含PROT_READ，所以
 * 如果仅PROT_WRITE，出现权限不允许，需要加上PROT_READ
 * 2.mmap含PROT_READ和PROT_WRITE权限，则open必须是O_RDWR权限
 */

#include <fcntl.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int
main(int argc, char *argv[]) {
    int sfd, dfd, i, j;
    char *src, *dst;
    void *saddr, *daddr;
    struct stat st;
    int cst;

    if(argc != 3) {
        fprintf(stderr, "%s <srcfile> <destfile>\n", argv[0]);
        return 1;
    }

    /*! clear stat */
    cst = 0;
    src = argv[1];
    dst = argv[2];
    if(stat(src, &st) < 0) {
        perror("stat()");
        return 1;
    }

    if((sfd = open(src, O_RDONLY, 0)) < 0) {
        perror("open");
        return 1;
    }

    cst |= 0x1; /*文件打开成功，需要处理*/
    if((dfd = open(dst, O_RDWR | O_CREAT, 0660)) < 0) {
        perror("open");
        goto err;
    }
    cst |= 0x2; /*!文件打开成功，需要处理*/

    if(ftruncate(dfd, st.st_size) < 0) {
        perror("ftruncate");
        goto err;
    }

    /*! 文件映射内存只读 */
    saddr = mmap(NULL, st.st_size, PROT_READ , MAP_PRIVATE, sfd, 0);
    if(saddr == MAP_FAILED) {
        perror("mmap-read");
        goto err;
    }
    close(sfd);
    cst &= ~0x1; /*! 已经处理close，不再处理*/
    cst |= 0x4;  /*! mmap成功，需要处理 */
    
    /*! 文件映射内存只写 */
    daddr = mmap(NULL, st.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, dfd, 0); /*!如果要修改原文，这里必须是SHARED，保持一份数据*/
    if(daddr == MAP_FAILED) {
        perror("mmap-write");
        goto err;
    }
    close(dfd);
    cst &= ~0x2; /*! 已经处理了close,不再处理*/
    cst |= 0x8;  /*! mmap成功，需要处理 */

    /*!文件内容拷贝*/
    memcpy(daddr, saddr, st.st_size);
    if(msync(daddr, st.st_size, MS_SYNC) < 0) {
        perror("msync");
        goto err;
    }

    munmap(saddr, st.st_size);
    munmap(daddr, st.st_size);
    cst &= ~0x4;
    cst &= ~0x8;
    return 0;

err:
    if(cst & 0x1) {
        close(sfd);
    }
    if(cst & 0x2) {
        close(dfd);
    }
    if(cst & 0x4) {
        munmap(saddr, st.st_size);
    }
    if(cst & 0x8) {
        munmap(daddr, st.st_size);
    }

    return 1;
}

