/*
 * 深入测试和学习io的打开标志位
 * O_RDONLY O_WRONLY O_RDWR
 */

#include "../common/common.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> //tolower isalpha isprint

static const char *filename="ioflags.dat";

int main(int argc, char *argv[]) {
    int fd,i;
    ssize_t n;
    int oflags = O_RDONLY;
    char buf[64];
    /*!mode在创建的时候，必须要指定，默认打开的时候可以不指定*/
    fd = open(filename, oflags, 0);
    if(fd < 0) err_exit("open:%s", filename);
    //??????n没有初始化，变量使用之前始终要考虑到初始化的问题
    //while(n){..错误写法
    while(1) {
        n = read(fd, buf, 64);
        //n==0 feof
        if(n < 0) {
            close(fd);
            err_exit("read");
        } else if(n==0) break;
        for(i=0; i<n; ++i) {
            if(isprint(buf[i])) {
                printf("%c",buf[i]);
            } else {
                printf("!");
            }
        }
        //printf("\n");
    }
    close(fd);
    return 0;
}
