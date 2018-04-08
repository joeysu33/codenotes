/*!
 * 基于文件流的IO，FILE*
 * C99标准提出了两项要求
 * 1.一个输出操作不能紧跟一个输入操作，必须在二者之间调用fflush函数或是一个文件定位函数
 *   fseek(), fsetpos(), rewind()
 * 2.一个输入操作不能紧跟一个输出操作，必须在二者之间调用一个文件定位函数
 * 根据glibc的源码，调用fseek和fsetpos, rewind会首先将文件的流数据写出，类似调用fflush来清空缓存
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../common/common.h"

int 
main(argc, argv)
    int argc;
    char *argv[];
{
    int n,n1;
    char buf[256], buf2[256];
    FILE *f ;

    /*!
     * w+ truncate, create if not exists
     * r+ read/write not create
     * r read only
     * w wirte only, create if not exists, truncate
     * a append
     * a+ append, create if not exists
     */
    f = fopen("aa.dat", "w+");
    if(!f) {
        err_exit("fopen ");
    }

    memset(buf, sizeof(buf), 0);
    memset(buf2, sizeof(buf2), 0);

    strcpy(buf, "xyz");
    n=strlen(buf);
    if(fwrite(buf, 1, n, f) != n) {
        err_exit("fwrite ");
    }
    printf("write:%s\n", buf);
    /*! 如果这里不调用清除缓存，则会导致读取不到,还需要考虑读取位置*/
    rewind(f);
    n1 = fread(buf2, 1, n, f); 
    if(n1 != n) {
        printf("readed=%d\n", n1);
        err_exit("fread ");
    }
    printf("read:%s\n", buf2);
    fclose(f);

    return 0;
}
