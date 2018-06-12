#include <stdio.h>
#include <unistd.h> //pipe pipe2
#include <sys/types.h>
#include <sys/stat.h> //mkfifo
#include <strings.h> //strcasecmp, strncasecmp
#include <string.h>

#define USE_POSIX 1
#define DATASIZE (100*1024*1024)
#define SENDBUF 512
#define RECVBUF 16

void block_read(int fd);
void block_write(int fd);

void
do_write(int fd) {
    block_write(fd);
}

void
block_write(int fd) {
    char buf[SENDBUF];
}

void
do_read(int fd) {
    block_read(fd);
}

void 
block_read(int fd) {
    char buf[RECVBUF];
}

void
do_pipe() {
    if(fork() < 0) {
    } else if(fork() == 0) {
        _exit(0);
    } 

}

void
do_fifo() {
}

void
do_socket() {
}

void
do_msgQueue() {
}

void
do_sharedMemory() {
}

int 
main(int argc, char *argv[]) {
    char *ipctype;
    void CALLFUNC (void); //函数声明
    typedef void (*callfunc_t) (); //函数类型声明
    callfunc_t func;

    if(argc != 2) {
        fprintf(stderr, "%s <ipc-type :pipe,fifo,socket,msg-queue,shared-memory>\n", argv[0]);
        return 1;
    }

    ipctype = argv[1];
    if(!strcasecmp(ipctype, "pipe")) {
        func = do_pipe;
    } else if(!strcasecmp(ipctype, "fifo")) {
        func = do_fifo;
    } else if(!strcasecmp(ipctype, "socket")) {
        func = do_socket;
    } else if(!strcasecmp(ipctype, "msgqueue")) {
        func = do_msgQueue;
    } else if(!strcasecmp(ipctype, "sharedmemory")) {
        func = do_sharedMemory;
    } else {
        fprintf(stderr, "No such ipc:%s.\n", argv[1]);
        return 1;
    }

    (*func)();

    return 0;
}

