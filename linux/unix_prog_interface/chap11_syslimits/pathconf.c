/*!
 * 运行时获取与文件相关的限制
 * pathconf(const char *pathname, int name);
 * fpathconf(int fd, int name);
 */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

static char s_filename[PATH_MAX];

void 
pathconf_print(const char *sname, int name) {
    long r;
    r = pathconf(s_filename, name);
    if(r == -1) {
        printf("no that name:%s\n", sname);
        return ;
    }

    printf("%s:%s = %ld\n",s_filename,sname, r);
}

#define PATHCONF(x) \
    do { pathconf_print(#x, x); } while(0)

int
main(int argc, char *argv[]) {
    int i;
    if(argc < 2) {
        printf("Argument is less, %s filename1 [filename2, [filename3]...]\n", argv[0]);
        return -1;
    }

    for(i=argc-1; i>=1; --i) {
        /*! may be src first "n" not have null-terminated */
        s_filename[PATH_MAX-1]=0;
        strncpy(s_filename, argv[i], PATH_MAX-1);
        PATHCONF(_PC_NAME_MAX);
        PATHCONF(_PC_PATH_MAX);
        PATHCONF(_PC_PIPE_BUF);
    }

    return 0;
}


