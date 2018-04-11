/*!
 * 文件属性
 * stat
 * lstat，和stat相同，如果是一个链接，则返回链接的属性
 * fstat，和stat相同，fstat针对文件描述符来调用
 */

#include <sys/stat.h> //support struct stat
#include <sys/types.h>

#include <stdlib.h> //support EXIT_SUCCESS EXIT_FAILURE
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h> //support va_list

#include "../common/common.h"

//dev_t     st_dev;         /* ID of device containing file */
//ino_t     st_ino;         /* inode number */
//mode_t    st_mode;        /* protection */
//nlink_t   st_nlink;       /* number of hard links */
//uid_t     st_uid;         /* user ID of owner */
//gid_t     st_gid;         /* group ID of owner */
//dev_t     st_rdev;        /* device ID (if special file) */
//off_t     st_size;        /* total size, in bytes */
//blksize_t st_blksize;     /* blocksize for filesystem I/O */
//blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
//
///* Since Linux 2.6, the kernel supports nanosecond
//precision for the following timestamp fields.
//For the details before Linux 2.6, see NOTES. */
//
//struct timespec st_atim;  /* time of last access */
//struct timespec st_mtim;  /* time of last modification */
//struct timespec st_ctim;  /* time of last status change */


void 
show_line(const char *msg, ...) {
    va_list va;
    va_start(va, msg);
    vprintf(msg, va);
    printf("\n");
}

void
show_stat(struct stat *s) {
    show_line("ID of device containing file: %lu", s->st_dev);
    show_line("inode number :%lu", s->st_ino);
    show_line("mode:%x", s->st_mode);
    show_line("number of hard links:%d", s->st_nlink);
    show_line("user id of owner:%d", s->st_uid);
    show_line("group id of owner:%d", s->st_gid);
}


int
main(int argc, char *argv[]) {
    struct stat s;
    if (argc != 2) {
        err_exit("Wrong cmdline, %s <filename> or <linkfilename>", argv[0]);
    }

    if(lstat(argv[1],&s) == -1) {
        return EXIT_FAILURE;
    }
    show_stat(&s);

    return EXIT_SUCCESS;
}
