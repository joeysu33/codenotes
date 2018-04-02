/*!
 * 获取系统的参数配置，限制
 */

#include <unistd.h>
#include <stdio.h>
#include "../common/common.h"

void 
sysconf_print(const char*sname, int name) {
    long r = sysconf(name);
    if(r == -1) {
        fprintf(stderr,"sysconf: %s\n", sname);
        return ;
    }

    printf("%s = %ld\n", sname, r);
}

#define SYSPRINT(x) \
    do{\
        sysconf_print(#x, x); \
    }while(0)

int 
main(int argc, char *argv[]) {
    SYSPRINT(_SC_ARG_MAX);
    SYSPRINT(_SC_LOGIN_NAME_MAX);
    SYSPRINT(_SC_NGROUPS_MAX);
    SYSPRINT(_SC_OPEN_MAX);
    SYSPRINT(_SC_PAGESIZE);
    SYSPRINT(_SC_RTSIG_MAX);
    SYSPRINT(100000);
    SYSPRINT(100001);

    return 0;
}

