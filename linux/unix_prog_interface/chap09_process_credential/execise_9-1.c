/*!
 * 习题9-1
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/fsuid.h>
#include "../common/common.h"

void showid(const char *desc) {
    //0:real 1:effective 2:saved 3:fs
    uid_t uid[4];
    gid_t gid[4];

    uid[3] = setfsuid(-1);
    gid[3] = setfsgid(-1);

    if(desc) printf("===%s\n", desc);
    if(getresuid(&uid[0], &uid[1], &uid[2]) == -1) err_exit("getresuid");
    if(getresgid(&gid[0], &gid[1], &gid[2]) == -1) err_exit("getresgid");
    printf("%-8s %8s %8s %8s %8s\n", "Name", "real", "effec", "saved", "fs");
    printf("%-8s %8d %8d %8d %8d\n", "UID", uid[0], uid[1], uid[2], uid[3]);
    printf("%-8s %8d %8d %8d %8d\n", "GID", gid[0], gid[1], gid[2], gid[3]);
}

void line(const char *words) {
    printf("%s\n", words);
}

int main() {
    showid("初始化ID");
    
    /*! operator A */
    if(setuid(1001) == -1) err_exit("setuid(1001);");
    showid("a:调用setuid(1001);");

    /*! operator B */
    if(setreuid(-1, 1001) == -1) err_exit("setreuid");
    showid("b:调用setreuid(-1, 1001);");

    /*! operator C*/
    if(seteuid(1001) == -1) err_exit("seteuid");
    showid("c:调用seteuid(1001);");

    /*! operator D*/
    if(setresuid(-1, 2000, 2000) == -1) err_exit("setresuid");
    showid("d:调用setresuid(-1, 2000, 2000)");

    return 0;
}

