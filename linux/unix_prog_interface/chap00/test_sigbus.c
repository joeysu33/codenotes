/*!
 * 测试SIGBUS信号的产生
 * 1.SIGBUS会在mmap映射文件的时候，指定一个超出文件大小的映射size，
 *   且该大小超出页大小的整数倍的时候，会发出SIGBUS信号
 *   例如文件大小为a ,页大小为b (一般是4k)， 分配的大小为c ,c = b*(m+1)
 *   m = a/b;如果不是整数倍m+1
 *   SIGBUS信号产生区域最后一个页大小区域
 */

#define _GNU_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>

static const char *testfile = "./300b.txt";

/*!
 * x86_64 Ubuntu下对非对齐部分写入不会触发SIGBUS信号
 */
int
memNonAlignBus(int argc, char *argv[]) {
    char *p1;
    struct {
        short x;
        char y;
        int z; /*! 这里的z一定是偶地址*/
        char k; 
    } st1;

    printf("sizeof(st1)=%ld\n", sizeof(st1));
    assert(sizeof(st1) == 12);
    p1 = &st1.y;

    st1.y='a';
    *p1 = 'F'; //写入到y
    printf("st1.y=%c\n", st1.y);
    p1++;
    *p1 = 'X'; //写入到y+1的地址，该地址是未对齐部分
    printf("st1.y=%c\n", st1.y);

    return 0;
}

/*!对于SIGBUS,默认退出程序，并core dump */
void
sigac_handler(int sig, siginfo_t *sa, void* ucontext) {
    psiginfo(sa, "received signals:");
    /*!这个信号错误无法继续，只能退出和SIGSEGV, SIGFPE等类似*/
    exit(1);
}

int
memBus(int argc, char *argv[]) {
    int fd, i, j;
    void *addr;
    char *p1, *p2;
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigac_handler;
    if(sigaction(SIGBUS, &sa, NULL)) {
        perror("sigaction()");
        return 1;
    }
    fd = open(testfile, O_RDWR, 0);
    if(fd < 0) {
        perror("open()");
        return 1;
    }

    /*!
     * --------|------|------------
     *   |
     *   300   4096   8192
     *
     *   4096-8192产生SIGBUS信号
     *   8192- 产生SIGSEGV,访问非法地址
     *   mmap映射大小为300b的文件时，至少使用一个分页4096,但是文件实际有效可用区域为0-299
     */
    addr = mmap(NULL, 4096*2, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(addr < 0) {
        perror("mmap()");
        return 1;
    }

    /*!映射完成，关闭文件*/
    if(close(fd) < 0) {
        perror("close()");
        return 1;
    }

    p1 = (char*)addr+300;  //可以访问，但是不会写入到文件
    p2 = (char*)addr+4096; //SIGBUS

    *p1 = 'X';
    printf("*p1 = 'X'\n");
    *p2 = 'F';
    printf("*p2 = 'F'\n");

    strcpy(addr, "abcd-test-efg");
    if(msync(addr,4096*2, MS_SYNC) < 0) {
        perror("msync()");
        return 1;
    }

    if(munmap(addr,4096*2) < 0) {
        perror("munmap()");
        return 1;
    }

    return 0;
}

int
main(int argc, char *argv[]) {
    return memBus(argc, argv);
    //return memNonAlignBus(argc, argv);
}

