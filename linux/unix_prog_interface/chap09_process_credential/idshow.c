/*!
 * chap09 进程凭证(process credential)
 * 获取进程的ID信息，信息结果参照/proc/进程ID/status中的
 * User Group行信息
 *
 * User: rid (实际的UID) eid(有效用户ID) sid(设置ID) fid(文件ID)
 * Group: rid (实际的GID) eid(有效的GID) sid(设置组ID） fid(文件的组ID)
 * 其中非特权用户仅能设置User和Group中的某一个选项值，但是特权用户对这个
 * 可以任意进行操作
 *
 * man credentials
 * getuid() 获取用户的真实ID
 * setuid() 设置用户的真实ID(非特权:多选一, 特权:任意)
 */

/*! 打开_GNU的高级功能 ,才能调用setresuid getresuid setresgid getresgid*/
#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <sys/fsuid.h>
#include "../common/common.h"

int main() {
    uid_t r_uid, e_uid, s_uid;
    gid_t r_gid, e_gid, s_gid;
    uid_t f_uid;
    gid_t f_gid;
    size_t size;
    gid_t *supplymentary_gid;
    int i;

    /*! setfsuid和setfsgid总是返回上一次的fs的id，没有getfsuid/getfsgia函数*/
    f_uid = setfsuid(-1);
    f_gid = setfsgid(-1);
    if(getresuid(&r_uid, &e_uid, &s_uid) == -1) err_exit("getresuid");
    if(getresgid(&r_gid, &e_gid, &s_gid) == -1) err_exit("getresgid");

    printf("r_uid=%d ,e_uid=%d ,s_uid=%d, f_uid=%d\n", r_uid, e_uid, s_uid, f_uid);
    printf("r_gid=%d ,e_gid=%d ,s_gid=%d, s_gid=%d\n", r_gid, e_gid, s_gid, f_gid);

    /*!获取辅助组*/
    size = getgroups(0, NULL);
    if(size == -1) err_exit("getgroups");
    supplymentary_gid = malloc(sizeof(gid_t) * size);
    if(!supplymentary_gid) err_exit("malloc");

    if(getgroups(size, supplymentary_gid) == -1) {
        free(supplymentary_gid);
        err_exit("getgroups");
    }

    printf("supplymentatry gids: ");
    for(i=0; i<size; ++i) {
        printf("%d, ", supplymentary_gid[i]);
    }
    printf("\n");

    free(supplymentary_gid);
    return 0;
}


