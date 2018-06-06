/* !
 * unix域上调用sendmsg来发送辅助信息
 * 辅助信息为文件描述符，通过这种手段
 * 能实现跨进程的描述符共享
 * 对于CMSG_XXX的操作，请参见
 * man cmsg
 *
 * 注意问题:
 * 1.recvmsg():Message too long
 * 解决方案，接收端的msghdr没有分配好空间
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/un.h> //sockaddr_un
#include <errno.h>
#include <fcntl.h>
#include "unix_sendmsg.h"

int
main() {
    struct sockaddr_un addr, caddr;
    int s, fd, c;
    int i,j;
    ssize_t readed;
    struct msghdr msg;
    struct cmsghdr *cmsg;
    struct iovec vec = {0}, *pvec;
    const char *str = "write into file ,from server!!!\r\n";
    char buf[32];
    socklen_t len;
    struct {
        struct cmsghdr cmsg;
        char d[sizeof(CMSG_SPACE(sizeof(int)))];
    } u;

    vec.iov_base = buf;
    vec.iov_len = sizeof(buf);
    memset(&msg, 0, sizeof(msg));

    /*!这个需要设置，否则会没有缓存接收数据,
     * 报错误 Message too long*/
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;

    /*!msg_control和contorllen的内存也需要提前分配好*/
    msg.msg_control = &u;
    msg.msg_controllen = sizeof(u);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, UNIX_PATH);

    unlink(UNIX_PATH);
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    if(s < 0) {
        perror("socket()");
        return EXIT_FAILURE;
    }

    if(bind(s,(const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind()");
        return EXIT_FAILURE;
    }

    if(listen(s, 15) < 0) {
        perror("listen()");
        return EXIT_FAILURE;
    }

    len = sizeof(caddr);
    c = accept(s, (struct sockaddr*)&caddr, &len);
    if(c < 0) {
        perror("accept()");
        return EXIT_FAILURE;
    }

    readed = recvmsg(c, &msg, 0);
    if(readed < 0) {
        perror("recvmsg()");
        return EXIT_FAILURE;
    }

    /*!可以读取的标志位仅仅有
     * MSG_OOB
     * MSG_EOR
     * MSG_CTRUNC
     * MSG_ERRQUEUE
     */
    printf("recvmsg recevied %ld bytes!\n", readed);
    printf("msg.msg_name=%s, msg.msg_namelen=%d, msg.msg_flags = %d. \n", (char*)msg.msg_name, msg.msg_namelen, msg.msg_flags);
    for(i=0; i<msg.msg_iovlen; ++i) {
        pvec = &msg.msg_iov[i];
        printf("vec[%d].iov_base=%s, vec[%d].iov_len=%ld.\n", i,(char*)pvec->iov_base, i,pvec->iov_len);
    }

    for(i=0, cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg), ++i) {
        fd = *(int*)CMSG_DATA(cmsg);
        printf("cmsg[%d].cmsg_level=%d, cmsg[%d].cmsg_type=%d cmsg[%d].cmsg_len=%ld fd=%d.\n",
                i, cmsg->cmsg_level, i, cmsg->cmsg_type, i, cmsg->cmsg_len, fd);
        j = write(fd, str, strlen(str));
        close(fd);
        assert(j == strlen(str));
    }

    printf("get cmsgcount=%d\n", i+1);
    close(s);
    return 0;
}

