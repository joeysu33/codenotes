/* !
 * unix域上调用sendmsg来发送辅助信息
 * 辅助信息为文件描述符，通过这种手段
 * 能实现跨进程的描述符共享,相当于在被传递进程中又多了一个
 * 该描述符的引用
 * 对于CMSG_XXX的操作，请参见
 * man cmsg
 *
 * 注意问题，
 * 1.客户端不要上来unlink,你这TM直接把文件给删掉了，还
 * 连接啥啊
 * 2.报错sendmsg:Transport endpoint is already connected,
 * 报这个错误的原因在于，已经connect了就不需要再指定目的地址了
 * 和使用tcp但调用sendto是一样的。
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
    struct sockaddr_un addr;
    int s, fd;
    int i,j;
    struct msghdr msg;
    struct iovec vec;
    char buf[32] = {0};
    const char *str = "write into file ,from client!!!\n";
    union {
        struct cmsghdr cmsg;
        char d[CMSG_SPACE(sizeof(int))]; //使用CMSG_SPACE来获取占用空间大小（含填充)
    } cmsg;

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, UNIX_PATH);

    s = socket(AF_UNIX, SOCK_STREAM, 0);
    if(s < 0) {
        perror("socket()");
        return EXIT_FAILURE;
    }

    if(connect(s, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return EXIT_FAILURE;
    }

    fd = open(OPEN_FILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    printf("client:fd=%d.\n", fd);
    j = write(fd, str, strlen(str));
    assert(j == strlen(str));

    cmsg.cmsg.cmsg_len = CMSG_LEN(sizeof(int)); //使用CMSG_LEN来获取len
    cmsg.cmsg.cmsg_level = SOL_SOCKET;
    cmsg.cmsg.cmsg_type = SCM_RIGHTS;  //发送文件描述符
    *(int*)CMSG_DATA(&cmsg.cmsg) = fd;

    strcpy(buf, "Hello Unix Server!!!");
    vec.iov_base = buf;
    vec.iov_len = sizeof(buf);

    memset(&msg, 0, sizeof(msg));
    //msg.msg_name = &addr; //如果已经连接可以不需要设置
    //msg.msg_namelen = sizeof(addr);
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);
    msg.msg_flags = 0;

    if(sendmsg(s, &msg, 0) < 0) {
        perror("sendmsg");
        return EXIT_FAILURE;
    }
    printf("flags = %d\n", 0);

    close(s);
    close(fd);
    return 0;
}

