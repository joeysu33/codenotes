/*!
 * 获取当前的文件系统详细信息
 * statvfs
 */

#include <stdio.h>
#include <sys/statvfs.h>
#include "../common/common.h"

void show_statusfs(struct statvfs *fs ) {
    printf("Filesystem block size:%lu\n"
            "Fragment size:%lu\n"
            /*
            "Size of fs in f_frsize units:%d\n"
            "Number of free blocks:%d\n"
            "Number of free blocks for unprivilege users:%d\n"
            "Number of inodes:%ld\n"
            "Number of free inodes:%ld\n"
            "Number of free inodes for unprivilge users:%d\n"
            */
            "Filesystem ID:%ld\n"
            "Mount flags:%ld\n"
            "Maxinum filename length:%ld\n",
            fs->f_bsize,
            fs->f_frsize,
            /*
            fs->f_blocks,
            fs->f_bfree,
            fs->f_bavail,

            fs->f_files,
            fs->f_ffree,
            fs->f_favail,
            */

            fs->f_fsid,
            fs->f_flag,
            fs->f_namemax
            );
}

int
main(int argc, char* argv[]) {
    struct statvfs sfs;

    if(argc != 2) {
        err_exit("wrong arguments: %s pathname ", argv[0]);
    }

    if(statvfs(argv[1], &sfs) == -1) {
        err_exit("statvfs ");
    }

    show_statusfs(&sfs);

    return 0;
}

