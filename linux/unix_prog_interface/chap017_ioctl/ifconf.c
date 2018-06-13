/*!
 * 使用ioctl来获取当前网络接口的配置
 * 获取接口的相关信息
 * 标志位
 * 索引
 * 广播地址
 * MTU等
 *
 * ioctl(fd, SIOCGIFCONF, XXX)
 * struct ifconf {
 *  lint ifc_len;
 *  union {
 *      caddr_t ifcu_buf;
 *      struct ifreq *ifcu_req;
 *  };
 * };
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

/*!应该要释放malloc的内存，例子暂时省略*/
#define handle_error(s) \
    do { perror(s); exit(EXIT_FAILURE); } while(0)

int
getIfCount() {
    int n;
    struct if_nameindex *ni;
    ni = if_nameindex();
    if(!ni) {
        handle_error("if_nameindex()");
    }

    for(n=0; !(ni->if_name == NULL && ni->if_index == 0) ; ni++,n++) ;
    return n;
}


int
main(int argc, char*argv[]) {
    int sfd;
    int i,cnt,n;
    char *d;
    struct ifreq *ifr;
    struct ifconf ifc;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) handle_error("socket()");

    cnt = getIfCount();
    printf("if count:%d.\n", cnt);
    n = sizeof(struct ifreq) * cnt;
    d = malloc(n);
    if(!d) handle_error("malloc");

    /*!给整个ifconf分配好内存*/
    ifc.ifc_buf = d;
    /*!表示struct ifreq的缓冲长度*/
    ifc.ifc_len = n;

    /*!SIOCGIFCONF仅能获取up的网络接口，down掉的就不行*/
    i = ioctl(sfd, SIOCGIFCONF, &ifc);
    if(i < 0) handle_error("ioctl");

    for(ifr = ifc.ifc_req, i=0; i<cnt; ++i,++ifr) {
        printf("ifr[%d].name=%s\n", i, ifr->ifr_name);
    }

    free(ifc.ifc_buf);
    return 0;
}



