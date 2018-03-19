/*!
 * Linux创建临时文件
 * 1.根据模板来创建文件,
 * 其中最后6个字符必须是XXXXXX，这6个字符将会被替换
 * template不能是常量字符串，必须可以进行修改,打开时使用O_EXCL
 * mkstemp需要手动调用unlink
 * #include <stdlib.h>
 * int mkstemp(char *template); 
 * 2.自动创建临时文件，标准C函数，打开时，使用标识符O_EXCL
 * tmpfile函数在调用的时候就已经调用了unlink，保证文件能自动删除
 * #include <stdio.h>
 * FILE *tmpfile(void)
 * 上述两种创建临时文件的方法能保证打开独占
 */

/*!使用program_invocation_name,
 * program_invocation_short_name
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //PATH_MAX
#include <unistd.h> //readlink

/*!program_invocation_name,
 * program_invocation_short_name
 * 来自这个头文件
 */
#include <errno.h>

extern char **environ;
/*! 来自<limits.h> */
static char buffer[PATH_MAX];

char* get_filename_by_fd(int fd) {
    char link[PATH_MAX];
    ssize_t n;
    if(fd < 0) return 0;
    snprintf(link, PATH_MAX,"/proc/self/fd/%d", fd);
    n=readlink(link, buffer, sizeof(buffer)-1);
    if(n < 0) {
        perror("readlink ");
        return NULL;
    }
    buffer[n+1]=0;
    return buffer;
}

/*!打开GNU C的各种功能选项，例如program_invocation_name,应用程序全名称
 * program_invocation_short_name，仅应用程序文件名
 */
void program_name() {
    printf("program-name%s\nprogram short name:%s\n",program_invocation_name, 
            program_invocation_short_name);
}

void env() {
    if(environ == NULL) return;
    char **ep = environ;
    printf("=======environment======\n");
    while(*ep != NULL) {
        printf("%s\n", *ep);
        ep++;
    }
    printf("========================\n");
}


void test_tmpfile() {
    FILE * f = tmpfile();
    if(!f) return ;
    int fd = fileno(f);
    /*!打印出来的文件名称信息，显示文件已经删除，因为在tmpfile中就已经调用了unlink*/
    printf("tmpfile:%s \n", get_filename_by_fd(fd));
    /*!在调用fclose之后会自动删除*/
    fclose(f);
}

void test_mkstemp() {
    char buf[] = "/tmp/testfile_XXXXXX";
    int fd = mkstemp(buf);
    if(fd<0) {
        perror("mkstemp ");
    }
    unlink(buf);
    /*!如果在unlink之后调用的话，文件名后面会显示文件已经(delete) */
    printf("mkstempfile:%s\n", get_filename_by_fd(fd));
    /*!在调用close之后文件会自动删除*/
    if(close(fd) < 0) {
        perror("close ");
    }
}

int main(int arg, char *argv[]) {
    /*!printf可以打印空指针,显示(null) */
    //printf("%s", (char*)0);
    //program_name();
    //env();
    test_tmpfile();
    test_mkstemp();
    return 0;
}




