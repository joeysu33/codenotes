/*!
 * popen的使用
 * 通过管道与shell命令进行通信
 * 
 * #include <stdio.h>
 * FILE* popen(const char* command, const char *cmd);
 * int pclose(FILE *stream);
 *
 * 这里特别特别需要注意的是fread和fwrite的用法
 * fread返回值的用法描述的是已经读取数据单元的个数,如果按照字节的话，
 * 那么第二个参数一定是1，这样返回值是字节数，如果第二个参数大于1，则
 * 表示有几个第二个参数大小的数据被返回。不建议将第二个参数设置成>1的值，
 * 如果将第二个参数设置为10,读取的数据有5个字节，则返回0，其实已经读取了5个字节
 */

#include <stdio.h> //popen
#include <unistd.h> //pipe
#include <string.h>
#include <stdlib.h>

static const char *cmd = "find .. -type f -iname \"*.c\"";
//static const char *cmd = "/bin/echo abc";
//static const char *cmd = "ls ../*.c";
#define handle_error(s) \
    do { perror(s); exit(EXIT_FAILURE); }while(0)

void
testSystem() {
    system(cmd);
}

int 
main() {
    FILE *fp;
    int nr;
    char buf[64];
    char pathbuf[256];
    char *cp;

    //testSystem();
    //return 0;

    setbuf(stdout, NULL);
    cp = getcwd(pathbuf, sizeof(pathbuf));
    if(!cp) handle_error("getcwd");
    printf("cwd:%s\n", cp);

    fp = popen(cmd, "r");
    if(!fp) handle_error("popen");
    for(;;) {
        /*
         * 或者可以使用fgets来读取字符串
        cp = fgets(buf,sizeof(buf), fp);
        if(!cp) {
            break;
        } 
        printf("read-str:%s\n", buf);
        fputs(buf, stdout);
        */

        /*! 之前将fread写成了
         *fread(buf, sizeof(buf)-1, 1,fp);
         *导致读取出来的数据全部错误
         使用fread(buf, sizeof(buf)-1, 1,fp)和
         fread(buf, 1, sizeof(buf)-1, fp)不同的地方
         在与返回值，返回值描述的是数据的个数，表示
         读取了几个这样的数据
        */
        nr = fread(buf, 1, sizeof(buf)-1, fp);
        if(nr <= 0) {
            fprintf(stdout,"nr=%d, exit for!\n", nr);
            break;
        } else {
            fwrite(buf, 1, nr, stdout);
        }
    }

    /*!关闭文件描述符，并且等待子进程结束waitpid*/
    pclose(fp);
    return 0;
}
