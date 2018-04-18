/*!
 * 首先调用，返回一个DIR* 目录流,并且默认总是指向开始，
 * 类似调用了rewinddir一样
 * DIR* opendir(const char *dirpath);
 * DIR* fopendir(int fd);
 *
 * 然后调用，将目录信息列出来，调用readdir会自动
 * 读取下一个目录流
 * struct dirent* readdir(DIR* dirp);
 *
 * telldir   指出当前目录在流中的位置 
 * rewinddir 将目录流恢复至初始位置
 * 都是用来操作DIR* 目录流的
 *
 * 最后关闭DIR* 目录流
 * closedir(DIR* dirp);
 */

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <sys/types.h>

#define PRINT(...) \
    do {printf(__VA_ARGS__); printf("\n");} while(0)

void showDirEntry(struct dirent* entry) {
    if(!entry) return ;
    PRINT("Inode=%ld", entry->d_ino);
    PRINT("Dir offset=%ld", entry->d_off);
    PRINT("Length of record=%u", entry->d_reclen);
    PRINT("File type=%u", entry->d_type);
    PRINT("Name=%s", entry->d_name);
    PRINT("--------------------");
}

int
main(int argc, char* argv[]) {
    DIR* dirp;
    struct dirent* entry;

    if(argc != 2) {
        PRINT("Invalid arguments %s <dirname>", argv[0]);
        return 1;
    }

    dirp = opendir(argv[1]);
    if(!dirp) {
        perror("opendir ");
        return 2;
    }

    do {
        entry = readdir(dirp);
        showDirEntry(entry);
    }while(entry);

    closedir(dirp);

    return 0;
}



