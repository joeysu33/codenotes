/*!
 * sault :瀑布
 *
 * 执行进程替换函数，如果调用失败，则会执行该函数的下一条语句，否则继续执行
 * void execve(const char* pathname, const char *argv[], const char *env);
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    /*!最后的NULL作为结束符，非常非常重要，对argv也是一样的 */
    /*! char* const 不是const char* */
    char* const env[] = { "GREET=sault", "BYE=xxoo", NULL }; 
    if(argc < 2) {
        fprintf(stderr,"%s <executable-file> [exec-args]args].\n", argv[0]);
        return 1;
    }

    /*!这里要注意的是argv[0]也就是可执行文件的名称是要包含的
     * 否则被执行程序读取不到*/
    execve(argv[1], &argv[1], env);
    perror("execve");
    return 1;
}

