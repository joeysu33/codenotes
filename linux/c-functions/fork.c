#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*!
 * fwrite和fread以及fgetc自带缓存
 * write,read,getc不带
 */
int main() {
    const char *hello="hello";
    const char *world="world";
    const char *welcome=",welcome";
    /*!open 是posix的函数，返回一个整型,
     * fopen是c函数,返回一个FILE* */
    FILE * f = fopen("test.txt", "w");
    if(!f) {
        perror("file");
        return -1;
    }
    /*!在fork的过程中会拷贝缓存区*/
    if(fwrite(hello, strlen(hello), 1, f) < 0) {
        perror("fwrite1");
        return -2;
    }
    /*!解决方案，在这个地方增加清空缓存区即可*/
    fflush(f);
    pid_t pid;
    pid=fork();
    if(pid<0) {
        perror("fork");
        return -3;
    }
    if(pid==0) {
        //child
        if(fwrite(world,strlen(world), 1, f) < 0) {
            perror("fwrite world");
            return -4;
        }
    } else {
        //parent
        sleep(1);
        if(fwrite(welcome, strlen(welcome), 1,f) < 0) {
            perror("fwrite welcome");
            return -5;
        }
    }

    printf("close file()\n");
    /*!所有的系统相关的资源句柄都需要按照新建的次数来进行释放
     * fopen对应fclose
     * open对应close
     * */
    fclose(f);
    return 0;
}




