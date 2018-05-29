/*
 * getaddrinfo
 */

#include <stdio.h>
#include <netdb.h> //getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

void
showAddrInfo(struct addrinfo* ai) {
    char *socktype, *proto;
    if(!ai) return ;
    switch(ai->ai_socktype) {
        case SOCK_STREAM: socktype = "SOCK_STREAM";break;
        case SOCK_DGRAM: socktype = "SOCK_DGRAM"; break;
        case SOCK_RAW: socktype = "SOCK_RAW"; break;
        case SOCK_PACKET: socktype = "SOCK_PACKET"; break;
        default: socktype = "Unknown"; break;
    }

    switch(ai->ai_protocol) {
        case IPPROTO_TCP: proto = "TCP"; break;
        case IPPROTO_UDP: proto = "UDP"; break;
        case IPPROTO_IP:  proto = "IP"; break;
        default: proto = "Unknown"; break;
    }

    printf("flags:%d, family:%d,\
            socktype:%s, protocol:%s,\
            addrlen:%d, canonname:%s,\n",
            ai->ai_flags, ai->ai_family,
            socktype, proto,
            ai->ai_addrlen, ai->ai_canonname);

    showAddrInfo(ai->ai_next);
}

int
main(int argc, char *argv[]) {
    int n;
    char *endptr;
    struct addrinfo *ai;

    if(argc != 3) {
        fprintf(stderr, "%s <domain> <service>\n", argv[0]);
        return 1;
    }

    printf("domain:%s service:%s\n", argv[1], argv[2]);
    n = getaddrinfo(argv[1], argv[2],
            NULL, &ai);
    if(n) {
        fprintf(stderr,"getaddrinfo:%s.\n",gai_strerror(n));
        return 1;
    }

    showAddrInfo(ai);
    freeaddrinfo(ai);
    return 0;
}

