/*!
 * 截断文件
 * (1)int truncate(const char* filename, off_t length);
 * (2)int ftruncate(int fd, off_t length);
 * 错误均返回-1,(1)如果length大于文件长度则形成空洞文件
 * (2)根据不一样的Linux标准可能形成空洞文件，可能返回错误
 * (2)要求文件具有写入权限
 */
#include "../common/common.h"
#include <stdlib.h> //strtol
#include <unistd.h> //truncate

int main(int argc, char *argv[]) {
    if(argc != 3) err_exit("usage: %s filename",argv[0]);
    char *endptr = argv[2];
    long len=strtol(argv[2], &endptr,0);
    if(endptr == argv[2]) err_exit("err argument");
    if(truncate(argv[1], len) < 0) err_exit("truncate");
    return 0;
}
