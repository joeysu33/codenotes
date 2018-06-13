/*!
 * 根据posix的接口来获取网络接口的索引和名称
 * 主要函数，获取所有的网络接口包含down掉的
 * 而ioctl(fd, SIOCGIFCONF, ...)仅获取up的接口
 * struct if_nameindex* if_nameindex();
 * void if_freenameindex(struct if_nameindex);
 * if_indextoname()
 * if_nametoindex()
 */

#include <net/if.h> //if_XXXX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main() {
    int n;
    struct if_nameindex *if_ni, *i;
    if_ni = if_nameindex();
    if(!if_ni) {
        fprintf(stderr, "if_nameindex() error!");
        return EXIT_FAILURE;
    }

    for(n=0, i = if_ni; !(i->if_index == 0 && i->if_name == NULL); ++i, ++n) {
        printf("if[%d]->if_index=%d if[%d]->if_name=%s\n",
                n,
                i->if_index,
                n,
                i->if_name);
    }

    if_freenameindex(if_ni);
    return EXIT_SUCCESS;
}
