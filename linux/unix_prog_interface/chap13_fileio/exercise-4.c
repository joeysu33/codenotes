/*!
 * 如下代码的的输出取决于输出重定向到终端还是文件
 * 1.默认终端输出，文件fd对应的是stdout,默认缓冲是_IOLBF(行缓冲)，
 * 而字符串s1含换行符会先输出, 所以先打印s1后打印s2
 * 2.重定向到文件之后，文件的默认缓冲是_IOFBF(全缓冲),因为printf是stdio的标准库
 * 会导致s2先输出，s1后输出
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int 
main(int argc, char *argv[]) {
    /*! 0:stdin 1:stdout 2:stderr */
    int fd = 1;
    /*! 如果去掉\n，因为stdout是行缓冲，则s2一定会先输出*/
    const char *s1 = "If I had more time,\n";
    const char *s2 = "I would have wirtten you a shorter letter. \n";
    /*! 基于行缓存，输出到文件的时候，被缓存，后输出*/
    //如果在这里限制没有缓存，则结果显示相同
    //setvbuf(stdout, NULL, _IONBF, 0);
    printf("%s",s1);
    /*! 直接输出 */
    write(fd, s2, strlen(s2));
    fprintf(stderr, "stdout=%08d.\n", (int)fileno(stdout));
    return 0;
}

