/*!
 * 读取文件中的扩展属性(EA) Extend Attributes
 * 扩展属性书写格式 namespace.name
 * #include <sys/xattr.h>
 * 函数:
 * ssize_t getxattr(const char* pathname, const char* name, void *value, size_t size); size=0;返回EA值大小
 * ssize_t lgetxattr(const char *pathname, const char *name, void* value, size_t size);
 * ssize_t fgetxattr(int fd, const char *name, void* value, size_t size);
 *
 * ssize_t listxattr(const char* pathname, char *list, size_t size);
 * ssize_t llistxattr(const char* pathname, char *list, size_t size);
 * ssize_t flistxattr(int fd, char *list, size_t size);
 * 返回的是属性名称的字符串的合并长度（包含0字符)
 *
 * int removexattr(const char* pathname, const char* name);
 * ...
 *
 * return:
 * -1 error
 *  >=0 success
 */

#include <sys/xattr.h>

#include <stdio.h>
#include <string.h>

#include "../common/common.h"

#define XATTR_BUFFER_SIZE  10240
static char buffer[XATTR_BUFFER_SIZE];

int
main(int argc, char* argv[]) {
    int attrSize, i, j;
    char *p, *endp;
    char buf[1024];

    if(argc != 2) {
        printf("%s <filename>\n", argv[0]);
        return 1;
    }

    if((attrSize = listxattr(argv[1], buffer, sizeof(buffer))) < 0) {
        err_exit("listxattr ");
    }

    if(attrSize == 0) return 0;

    p = &buffer[0];
    endp = &buffer[0] + attrSize;
    printf("属性列表:\n");
    printf("attrSize=%d\n", attrSize);
    for(; p<endp; ) {
        printf("name:%s, ", p);
        j=getxattr(argv[1], p, buf, sizeof(buf));
        printf("value length=%d, ", j);
        if(j < 0) err_exit("getxattr ");
        if(j >= sizeof(buf))
            buf[1023]=0;
        else 
            buf[j]=0;
        printf("value:%s\n", buf);
        p += strlen(p)+1;
    }

    return 0;
}


