/*!
 * 带多组buf的read/write
 * scatter and gather io
 * 分散输入，集中输出
 * #include <sys/uio.h>
 * #include <unistd.h>
 * int readv(int fd,const struct iovec *vec, int iovcnt);
 * int writev(int fd, const struct iovec *vec, int iovcnt);
 * int preadv(int fd, const struct iovec* vec, int iovcnt, off_t offset);
 * int pwritev(int fd, const struct iovec* vec, int iovcnt, offt_t offset);
 * 注意事项:这种方式的返回值，如果-1则说明写入或读取失败
 * 如果>0，则说明已经写入的字节数（特别注意），不一定能一次写完
 * 如果一次写不完，需要重新计算iovec，重新确定数组元素的个数以及位置,多次定位
 * struct iovec (io vector)
 */
#include "../common/common.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> //memset
#include <sys/uio.h> //struct iovec
#include <malloc.h>

typedef struct _sa_t {
    int m_a, m_b, m_c;
} sa_t;

#define N (1*1024*1024*1024)
#define IOV_CNT 3

int main(int argc, char* argv[]) {
    //char buf[N] = "xyaz";
    char *buf = malloc(N);
    sprintf(buf, "%s", "xykk");
    buf[4]=0;
    sprintf(buf+N-5, "%s", "ABCD");
    buf[N-1]=0;
    //xyaz.....ABCDS
    sa_t st = {100,200,300};
    double k=23.90321232;
    const char *filename= "scatter_gather_io.dat";
    int i,index,fd, flags=O_RDWR | O_CREAT;
    int mode= S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    ssize_t sz; //nReaded/nWritten bytes
    unsigned long len;

    struct iovec vec[IOV_CNT];
    vec[0].iov_base = buf;
    vec[0].iov_len = N;
    vec[1].iov_base = &st;
    vec[1].iov_len = sizeof(st);
    vec[2].iov_base = &k;
    vec[2].iov_len = sizeof(k);

    len=0;
    for(i=0;i<IOV_CNT;++i) len += vec[i].iov_len;

    fd = open(filename, flags, mode);
    if(fd < 0) {
        free(buf);
        err_exit("open");
    }
    sz=0;
    index=0;
    while(1) {
        sz=writev(fd, &vec[index], IOV_CNT);
        if(sz < 0) {
            free(buf);
            close(fd);
            err_exit("writev error!!!");
        }
        //大于或等于当前的，切换到下一个iovec
        printf("writev write bytes:%ld\n", sz);
        while(sz >= vec[index].iov_len && index < IOV_CNT) {
            sz -= vec[index].iov_len;
            index++;
        }
        if(index == IOV_CNT) { 
            break; 
        } else {
            //重新设置base和len以及index
            vec[index].iov_len -= sz;
            vec[index].iov_base = (char*)vec[index].iov_base + sz;
        }
    }

    //清除原来的数据
    memset(buf, 0, N);
    memset(&st, 0, sizeof(st));
    memset(&k, 0, sizeof(k));

    //移动到开始进行读取
    lseek(fd, 0, SEEK_SET);
    vec[0].iov_len=N;
    vec[1].iov_len=sizeof(st);
    vec[2].iov_len=sizeof(k);
    index=0;
    while(1) {
        sz=readv(fd, &vec[index], IOV_CNT);
        if(sz < 0) {
            close(fd);
            free(buf);
            err_exit("readv");
        }
        printf("readv read bytes:%ld\n", sz);
        while(sz >= vec[index].iov_len && index < IOV_CNT) {
            sz -= vec[index].iov_len;
            index++;
        }
        if(index == IOV_CNT) {
            break;
        } else {
            //重新设置iov_base iov_len和index
            vec[index].iov_len -= sz;
            vec[index].iov_base = (char*)vec[index].iov_base +sz;
        }
    }
    printf("buffer:0~4:%s, N-5~N-1:%s\n", &buf[0], &buf[N-5]);
    printf("st.a=%d st.b=%d st.c=%d\n", st.m_a, st.m_b, st.m_c);
    printf("k=%lf\n", k);
    close(fd);
    free(buf);

    return 0;
}
 
