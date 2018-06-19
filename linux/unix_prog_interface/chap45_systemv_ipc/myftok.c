/*!
 * key_t ftok(const char *pathname, int proj); //key_t 32位值
 *
 * 自己来实现一个ftok 
 * ftok的组成: proj的低8位，文件所属文件系统的最低8位，inode值号的最低16位
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h> //strtol
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h> //key_t

key_t myftok(int proj, struct stat *st) {
    /*! struct进行位运算，先写的数据结构在低位，后写的在高位
     *  正确的数值应该是proj|dev|inod
     */
    struct {
        int inod:16;
        int dev:8;
        int proj:8;
    }k;

    k.proj = proj & 0xFF;
    k.dev = st->st_dev & 0xFF;
    k.inod = st->st_ino & 0xFFFF;

    key_t r;
    memcpy(&r, &k, 4);
    return r;
}

int 
main(int argc, char *argv[]) {
    struct stat st;
    int proj;
    key_t k1, k2;
    char *cp, *pathname;

    if(argc != 3) {
        fprintf(stderr, "%s <pathname> <proj(int)>\n", argv[0]);
        return 1;
    }

    proj = strtol(argv[2],&cp, 0);
    if(proj < 0 || proj > 255) {
        fprintf(stderr, "proj is invalid\n");
        return 1;
    }

    pathname = argv[1];
    if(stat(pathname, &st) < 0) {
        perror("fstat");
        return 1;
    }

    k1 = ftok(pathname, proj);
    k2 = myftok(proj, &st);

    printf("pathaname=%s, proj=0x%x ,inode=0x%lx, dev=0x%lx,\
            proj_l8=0x%x, dev_l8=0x%lx,inode_l16=0x%lx,\
            k1=0x%x, k2=0x%x\n",pathname, proj,st.st_ino, st.st_dev,
            proj & 0xFF, st.st_dev & 0xFF, st.st_ino & 0xFFFF, k1, k2);
    assert(k1 == k2);

    return 0;
}

