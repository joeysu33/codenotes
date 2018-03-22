/*!
 * 获取linux系统用户和组的信息
 * 分别通过用户名称和用户ID来获取passwd*
 * getpasswordname
 * getpassworduid
 * struct passwd* getpwnam(const char* name);
 * struct passwd* getpwuid(uid_t uid);
 *
 * struct group* getgrnam(const char* name);
 * struct group* getgruid(uid_t uid);
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <stdlib.h> //strtol
#include <pwd.h> //getpwnam getpwuid
#include <errno.h>
#include "../common/common.h"

void show_passwd(struct passwd* pw) {
    char buf[1024];
    if(!pw) return ;
    snprintf(buf, 1024, "name:%s, passwd:%s, uid:%d,\
            gid:%d, pw_gecos:%s, pw_dir:%s, pw_shell:%s",
            pw->pw_name, pw->pw_passwd, pw->pw_uid,
            pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell);
    printf("%s\n", buf);
}

int main(int argc, char *argv[]) {
    int errno ;
    char *endptr;
    long uid=0;
    struct passwd *pw;
    unsigned char flag=0;

    if(argc != 2 ) {
        printf("%s [uid|uname]\n", argv[0]);
        return 1;
    }

    errno=0;
    uid = strtol(argv[1], &endptr, 0);
    if(endptr == argv[1] || errno != 0 ) {
        flag=1;
    }

    /*! 0:username 1:uid*/
    if(flag == 1) {
        pw = getpwnam(argv[1]);
    }
    else {
        pw = getpwuid(uid);
    }

    if(!pw) {
        printf("No pwd found!\n");
        return 2;
    }

    show_passwd(pw);
    return 0;
}

