/*!
 * exit和_exit的区别
 * 1.exit调用_exit
 * 2.exit会先清空缓冲在调用_exit
 *
 * 通过输出的结果可以很清楚的看出
 * 调用exit会输出结果，但是调用_exit不会输出
 */

#include <stdio.h>
#include <stdlib.h> //exit 库API
#include <stdint.h>
#include <unistd.h> //_exit 系统级API

int main(int argc, char *arv[]) {
    uint8_t i;
    if(argc  > 1) {
        printf("Use _exit() to exit!\n");
    } else {
        printf("Use exit() to exit!\n");
    }

    /*!因为printf默认是行缓冲，所以暂时不会输出*/
    printf("aabb");
    printf("kkjj");

    /*!调用exit退出*/
    if(argc > 1) {
        _exit(0);
    } else {
        exit(0);
    }

    return 0;
}

