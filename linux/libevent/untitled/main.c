#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

#include "event2/event-config.h"
#include "event2/event.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define EXIT(msg) \
    do {perror(msg); exit(1); }while(0)

void
show_evbase() {
    int i;
    const char **methods = event_get_supported_methods();
    printf("可用的方法: ");
    for(i=0; methods[i] ; ++i) {
        printf("%s, ", methods[i]);
    }
    printf("\n");
}

void
cb_client_rd(evutil_socket_t fd, short flag, void * arg) {
    (void)flag;
    (void)arg;
    if(flag != EV_READ) return ;
    char buffer[1024];
    int readed ;
    do {
        readed = read(fd, buffer, 1023);
        if(readed < 0) {
            EXIT("read ");
        } else if(readed == 0) break;

        buffer[readed] = 0;
        printf("%s", buffer);
    } while(readed > 0);
}

int
main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    int sfd;
    struct event *ev;
    struct event_base *eb = event_base_new();
    if(!eb) {
        EXIT("event_base_new ");
    }

    show_evbase();
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1) EXIT("socket ");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);

    if(connect(sfd, (const struct sockaddr*) &addr, sizeof(struct sockaddr)) < 0) {
        close(sfd);
        EXIT("connect ");
    }
    const char * request = "GET / HTTP/1.1\r\n";
    write(sfd, request, strlen(request));

    ev = event_new(eb, sfd, EV_READ, &cb_client_rd, NULL);
    event_add(ev, NULL);
    event_base_dispatch(eb);
    event_base_free(eb);
    close(sfd);

    return 0;
}
