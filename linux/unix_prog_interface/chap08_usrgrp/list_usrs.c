/*!
 * 列出passwd中的所有用户
 * entry 条目
 * setXXX 将database置于开始位置
 * getXXX 从当前位置开始获取
 * endXXX 结束数据库的当前位置
 *
 * abitratry 任意的，任性的
 * set password entry (setpwent)
 * get password entry (getpwent)
 * void setpwent(void);
 * void endpwent(void);
 * struct passwd* getpwent();
 *
 * void setgrent();
 * void endgrent();
 * struct group* getgrent();
 * 调用getpwent(或getgrent)自动迭代到下一个，如果在程序中多出需要使用到
 * getpwent，则需要调用endpwent(endgrent)来结束迭代，恢复到初始位置
 */

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

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
    struct passwd *pwd;
    int i=0;

    while((pwd = getpwent())) {
            show_passwd(pwd);
            if(i++==3) {
                break;
            }
    }

    printf("--------------------\n");
    i=0;
    while((pwd = getpwent())) {
            show_passwd(pwd);
            if(i++==3) {
                break;
            }
    }

    endpwent();
    printf("after endpwent()\n");
    while((pwd = getpwent())) {
            show_passwd(pwd);
    }

    return 0;
}


