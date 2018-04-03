/*!
 * 根据不同的buffer来拷贝100M的文件
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <sys/times.h>
#include "../common/common.h"

static long SC_CLK_TCK = 0;
static struct tms s_last_tms = {0};

void
showTimes(int bufsize) {
    if(!SC_CLK_TCK) {
        if((SC_CLK_TCK = sysconf(_SC_CLK_TCK)) == -1) err_exit("sysconf");
    }
    struct tms tms;
    if(times(&tms) == (clock_t)-1) err_exit("times");
    double utime = (tms.tms_utime - s_last_tms.tms_utime) *1.0 /SC_CLK_TCK;
    double stime = (tms.tms_stime - s_last_tms.tms_stime) *1.0 /SC_CLK_TCK;
    printf("bufsize=%4d real:%.2lfs user:%.2lfs system:%.2fs\n", 
            bufsize, 
            utime+stime,
            utime,
            stime);
    memcpy(&s_last_tms, &tms, sizeof(struct tms));
}

int
main(int argc, char *argv[]) {
    int fd, bufsize,fdw, sz;
    off_t filesize, count;
    ssize_t readed, written;
    char *buf;
    char filename[32];

    if(argc != 2) {
        printf("%s filename\n", argv[0]);
        return 1;
    }

    if((fd = open(argv[1], O_RDONLY)) == -1) err_exit("open-readony:%s ", argv[1]);
    filesize = lseek(fd, 0, SEEK_END);
    if(filesize == -1) {
        err_exit("lseek");
    }

    bufsize = 1;
    while(bufsize < 1025) {
        count = filesize;
        snprintf(filename, sizeof(filename), "target_buf_%d.dat", bufsize);
        if((fdw = open(filename, O_WRONLY | O_CREAT), 0660) == -1) err_exit("open_wronly:%s ", filename);
        buf = malloc(bufsize);
        while(count != 0) {
            if(count > bufsize) {
                sz = bufsize;
            } else {
                sz = count;
            }

            if( (readed = read(fd, buf, sz)) == -1) {
                close(fd);
                close(fdw);
                free(buf);
                err_exit("read");
            }

            if( (written = write(fdw, buf, sz)) == -1) {
                close(fd);
                close(fdw);
                free(buf);
                err_exit("write");
            }
            count -= sz;
        }

        showTimes(bufsize);
        free(buf);
        close(fdw);
        bufsize *= 2;
    }

    close(fd);
    return 0;
}

