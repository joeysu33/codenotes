/*!
 * 给文件增加扩展属性
 * #include <sys/xattr.h>
 *
 * int setxattr(const char* pathname, const char* name, const void* value, size_t size, int flags);
 * int lsetxattr(const char* pathname, const char* name, const void* value, size_t size, int flags);
 * int fsetxattr(int fd, const char* name, const void* value, size_t size, int flags);
 *
 * flags:
 * XATTR_CREAT: 如果属性已经存在，则失败
 * XATTR_REPLACE: 如果属性不存在，则失败
 * 0: 默认值，已经存在，则覆盖，否则创建
 *
 * return:
 * -1 error
 *  0 success
 *
 *  max-name:255
 *  size:64kb
 */

#include <sys/xattr.h>

#include <stdio.h>
#include <string.h>
#include "../common/common.h"

/*!
 * 对于name有固定的四个命名空间:
 * user
 * trusted
 * system (ACL)
 * secuirity
 */
static const char* sc_name_x = "user.x";
static const char* sc_name_y = "user.y";
static const char* sc_val_x = "you can see this x.";
static const char* sc_val_y = "you can see this y.";

int
main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("argument error, %s <filename>\n", argv[0]);
        return 1;
    }

    if(setxattr(argv[1], sc_name_x, sc_val_x, strlen(sc_val_x), 0) < 0) {
        err_exit("setxattr ");
    }

    if(setxattr(argv[1], sc_name_y, sc_val_y, strlen(sc_val_y), 0) < 0) {
        err_exit("setxattr ");
    }

    return 0;
}

