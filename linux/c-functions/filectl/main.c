/*!
  Linux 文件控制操作
  fnctl
  case1:对文件进行加锁操作
  case2:修改文件打开标志位
  case3:读取文件打开标志位
  attention:
  读取文件的访问标志位的时候O_ACCMODE
  accessMode = flags & O_ACCMODE;

  Linux的文件锁分为两种，建议锁和强制锁
  1.建议锁也就是本部分提到的文件锁，也可以调用flock来实现
     建议锁，系统不会在内核强制校验，需要用户自己来检测文件
     是否已经加锁
  2.强制锁由系统内核来进行管理，不需要通过用户来校验
  3.fork子进程的过程中，子进程不会继承锁，否则失去了锁的意义
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

static const char * filename="test_flag.dat";
static int pid=0;

void err_exit(const char *msg, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, 1024,msg, ap);
    va_end(ap);
    perror(msg);
    exit(1);
}

void lock_file() {
    char buf[10];
    int fd;
    struct flock l, lock;
    int lck = F_RDLCK;
    int openFlag = O_RDONLY;
    //指定锁的类型，位置，锁控制的长度
    //0表示直到文件末尾
    l.l_len=10;
    l.l_whence = SEEK_SET;
    l.l_start = 2;
    //类型只能是三个中的一个,锁住之后，其他的进程理论上不能进行访问
    //F_WRLCK排它锁, F_RDLCK共享锁
    l.l_type = lck; //锁的类型和文件的打开类型需要保持一致
    lock.l_type = lck;
    //l.l_pid 返回的进程ID

    fd = open(filename, openFlag, 0);
    if(fd < 0) err_exit("open");
    if(pid != 0) {
        lock.l_pid = pid;
        lock.l_type = lck;
        printf("lock.pid=0x%x\n", pid);
    }

    //加锁之前先进行测试
    if(fcntl(fd, F_GETLK, &lock) < 0) {
        close(fd);
        err_exit("fcntl");
    }

    printf("where=%d len=%d start=%ld type=%ld pid=0x%x\n", lock.l_whence,
            lock.l_len, lock.l_start, lock.l_type, lock.l_pid);

    if(fcntl(fd, F_SETLK, &l) < 0) {
        close(fd);
        err_exit("fcntl");
    }

    printf("lock.pid=0x%x pid=0x%x\n", l.l_pid, getpid());
    getchar();
    //可以读写
//    if(read(fd, buf, 2) < 0) {
//        close(fd);
//        err_exit("read");
//    }
//    //该地址自己可访问，其他进程无法访问
//    if(read(fd, buf, 2) < 0) {
//        perror("read errrrrrr");
//    }
//    if(lseek(fd, 2, SEEK_SET) < 0) {
//        err_exit("lseek");
//    }
////    该地址不能写入数据
//    if(write(fd, buf, 2) < 0) {
//       perror("write errrrrr");
//    }

    //自己不能在自己的进程中读取自己的锁状态
//    lock.l_type = F_RDLCK;
//    lock.l_len = 10;
//    lock.l_start = 2;
//    lock.l_whence = SEEK_SET;
//    lock.l_pid = l.l_pid;
//    if(fcntl(fd, F_GETLK, &lock) < 0) {
//        close(fd);
//        err_exit("fcntl");
//    }

//    printf("where=%d len=%d start=%ld type=%ld pid=0x%x\n", lock.l_whence,
//            lock.l_len, lock.l_start, lock.l_type, lock.l_pid);
    close(fd);
}

void file_flags() {
    int fd, mode, flag;
    char buffer[24];

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    //O_CREAT，当文件不存在的时候进行创建，存在的时候直接打开
    //O_CREAT 不属于fcntl控制，属于临时状态，不属于持久状态,参见O_CREAT的注释
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, mode);
    if(fd < 0) {
        err_exit("open");
    }

    snprintf(buffer, 24,"file content");
    if(write(fd, buffer, strlen(buffer)) < 0) {
        close(fd);
        err_exit("write:%d", 10);
    }

    flag = fcntl(fd, F_GETFL);
    if(flag < 0) {
        close(fd);
        err_exit("fcntl");
    }

    switch(flag & O_ACCMODE) {
    case O_RDONLY:  printf("readonly-");break;
    case O_WRONLY: printf("writeonly-");break;
    case O_RDWR: printf("readwrite-"); break;
    }
    if(flag & O_CREAT) printf("creat-");
    if(flag & O_APPEND) printf("append-");

    printf("\n");
    close(fd);
}

int main(int argc, char *argv[])
{
    char *nptr;
    (void)argc;
    (void)argv;
//    file_flags();
    if(argc == 2) {
        pid=strtol(argv[1], &nptr, 16);
    }
    pid=0x63a5;
    lock_file();

    return 0;
}
