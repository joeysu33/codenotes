/*!
 * 创建一个100M的文件
 * 1.特别需要注意的是open的mode参数，如果在创建文件的时候
 * mode参数是会生效的,如果创建文件，但是没有指定mode参数，
 * 情况就会很严重，系统会随机分配一个值。
 * 2.调用open和mkdir的时候mode的值会与当前umask进行操作
 *   mode & ~umask
 * 3.因为我的umask是0002，所以无法给others设置上写权限
 *  可以通过在shell中umask进行查看和修改
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../common/common.h"

int
main(int argc, char *argv[]) {
    int fd;
    char c;
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    if(argc != 2) {
        printf("%s filename\n", argv[0]);
        return 1;
    }

    printf("mode=%o, 0666=%o\n", mode, 0666);
    if((fd = open(argv[1], O_WRONLY|O_CREAT, mode)) == -1) err_exit("open");
    if(pwrite(fd, (void*)&c, 1, 100*1024*1024L - 1) == -1) err_exit("pwrite");
    close(fd);

    return 0;
}
