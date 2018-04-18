/*!
 * 验证printf的缓存
 * linux下的缓存方式
 *
 * 终端（标准输出） ：行缓存
 * 块设备           ：块缓存
 * 标准出错         ：无缓存
 *
 * ./printf > tmp
 * ./printf 2> tmp
 * ./printf >tmp 2>&1 错误输出和标准输出均重定向
 *
 * 重定向操作
 * cmd > file 把 stdout 重定向到 file 文件中;
 *  
 *cmd >> file 把 stdout 重定向到 file 文件中(追加);
 *cmd 1> fiel 把 stdout 重定向到 file 文件中;
 *cmd > file 2>&1 把 stdout 和 stderr 一起重定向到 file 文件中;
 *cmd 2> file 把 stderr 重定向到 file 文件中;
 *cmd 2>> file 把 stderr 重定向到 file 文件中(追加);
 *cmd >> file 2>&1 把 stderr 和 stderr 一起重定向到 file 文件中(追加);
 *cmd < file >file2 cmd 命令以 file 文件作为 stdin，以 file2 文件作为 stdout;
 *cat <>file 以读写的方式打开 file;
 *cmd < file cmd 命令以 file 文件作为 stdin;
 *cmd << delimiter Here document，从 stdin 中读入，直至遇到 delimiter 分界符。
 */

#include <stdio.h>
#include <unistd.h>

int
main( int argc, char *argv[]) {
    /*! 0: stdin 1:stdout 2: stderr */
    int fd=1;

    pid_t pid;
    /*! printf输出的时候带换行符，所以强制输出，但是经过管道输出到文件则会缓存
     * 导致printf输出的内容会缓存一份,改成fprintf(stderr,)则没问题*/
    fprintf(stderr,"pid=%d ppid=%d\n", getpid(), getppid());

    pid = fork();
    if(pid == 0) {
        fprintf(stderr,"pid=%d ppid=%d\n", getpid(), getppid());
    }

    return 0;
}

