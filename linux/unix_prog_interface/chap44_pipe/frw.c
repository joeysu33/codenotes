/*!
 * fread 返回读取数据块的个数
 * fwrite 返回写入数据块的个数
 * fopen 打开文件
 * fputs 输出字符串
 * fgets 读入字符串
 * ...
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define handle_error(s) \
    do { perror(s); exit(EXIT_FAILURE); }while(0)

void
test_fread() {
    FILE *fp;
    int n;
    char buf[32];

    /*! +文件不存在的时候创建, truncated*/
    fp = fopen("test.dat", "w+");
    if(!fp)  handle_error("fopen");
    buf[0]=0;
    buf[1]=1;
    buf[2]=2;
    n = fwrite(buf, 3, 1, fp);
    assert(n == 1);

    /*!移动文件指针到开始位置*/
    rewind(fp);
    memset(buf, 0, sizeof(buf));
    /*!正好读取一个块大小*/
    n = fread(buf, 3, 1, fp);
    printf("Read %d block\n", n);
    assert(n == 1);

    /******特别注意，因为读取的块字节不够，所以这个地方返回0, 其实已经读到文件尾*****/
    /******建议采用fread(buf, 1, bytes-count, fp)
     * fwrite(buf, 1, bytes-count, fp)
     * 来读写，直接返回字节数目，这样容易直到具体读取的字节数目
     */

    /*!移动文件指针到开始位置*/
    rewind(fp);
    memset(buf, 0, sizeof(buf));
    /*!正好读取一个块大小*/
    n = fread(buf, 4, 1, fp);
    printf("Read %d block\n", n);
    assert(n == 0);

    printf("ftell(tp)=%li\n", ftell(fp));
}

int
main() {
    test_fread();
    return 0;
}
