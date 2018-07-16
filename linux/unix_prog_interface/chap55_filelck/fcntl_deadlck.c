/*!
 * fcntl死锁的情况
 * fcntl可以对死锁进行检测,flock不行
 * fork子进程的情况:
 * 1.fcntl中子进程不继承记录锁
 * 2.flock会继承记录锁
 *
 * 注意事项:
 * sem_t在父子进程间的通信，不能直接使用全局的sem_t
 * 要在父子进程间使用共享的sem
 * 1.开辟共享内存
 *   a.posix的共享内存 shm_open
 *   b.mmap映射内存
 *   c.system-v的共享内存
 * 2.在同样的共享内存区域(相对位置)，访问同一个sem_t对象
 */

#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>

static int fd;
static struct flock flk1, flk2;
static const char *sharedfile= "tmpfile";
static const char *sn1 = "/s1", *sn2 = "/s2";
static sem_t *s1, *s2; /*! 设置一个共享命名信号量,作为互斥量，辅助proc1和proc2之间设置锁的同步 */

void
signalProcess(int sig) {
    int st;
    if(sig == SIGCHLD) {
        /*!It's unsafe, using stdio in async call */
        printf("Received SIGCHILD.\n");
        while(waitpid(-1, &st, WNOHANG) > 0) ;
        exit(0);
    }
}

void
initFlock() {
    flk1.l_type = F_WRLCK;
    flk1.l_whence = SEEK_SET;
    flk1.l_start = 0;
    flk1.l_len = 10;

    flk2.l_type = F_WRLCK;
    flk2.l_whence = SEEK_SET;
    flk2.l_start = 20;
    flk2.l_len = 10;
}

/*!
 * 这里如果有外部命令关闭进程（父进程或子进程），
 * 存在其他死锁的风险，最后是关联信号，如果子进程
 * 被关闭，父进程直接退出*/

void 
initSem() {
    /*!子进程能否执行*/
    sem_unlink(sn1);
    sem_unlink(sn2);

    s1 = sem_open(sn1, O_CREAT | O_EXCL, 0660, 1);
    if(s1 == SEM_FAILED) {
        perror("sem_init");
        exit(1);
    }

    /*!父进程能否执行*/
    s2 = sem_open(sn2, O_CREAT | O_EXCL, 0660, 0);
    if(s2 == SEM_FAILED) {
        perror("sem_init");
        exit(1);
    }
}

void
init() {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    initFlock();
    fd = open(sharedfile, O_RDWR, 0); //file must be here.
    if(fd < 0) {
        perror("open");
        exit(1);
    }
    initSem();
}

void
clear() {
    close(fd);
    sem_close(s1);
    sem_close(s2);
    sem_unlink(sn1);
    sem_unlink(sn2);
}

/*!
 * 基本执行流程
 * 孩子进程先执行，锁住flk1，之后通知父进程
 * 开始执行，父进程锁住flk2,并等待flk1
 */

/*!child process*/
void
runProc1() {
    s1 = sem_open(sn1, 0);
    s2 = sem_open(sn2, 0);
    if(s1 == SEM_FAILED || s2 == SEM_FAILED) {
        perror("sem_open");
        _exit(1);
    }

    if(sem_wait(s1) < 0) {
        perror("sem_wait_proc1");
        _exit(1);
    }

    printf("Child process exec...\n");
    /*!等待（阻塞)获取文件锁*/
    if(fcntl(fd, F_SETLKW, &flk1) < 0) {
        perror("fcntl");
        exit(1);
    }
    printf("Child process get flk1\n");
    sleep(2);
    if(sem_post(s2) < 0) {
        perror("sem_post_proc1");
        _exit(1);
    }

    /*!重新等待s1，与father同步*/
    if(sem_wait(s1) < 0) {
        perror("sem_wait_proc1");
        _exit(1);
    }
    printf("Child process ready to get flk2...\n");
    if(fcntl(fd, F_SETLKW, &flk2) < 0) {
        if(errno == EDEADLK) {
            printf("Child process deadlock ocurr!\n");
        } else {
            perror("fcntl_proc1");
            _exit(1);
        }
    }

    printf("Child process exit!!!\n");
    sem_close(s1);
    sem_close(s2);
    _exit(0);
}

/*!father process*/
void
runProc2() {
    if(sem_wait(s2) < 0) {
        perror("sem_wait_proc2");
        exit(1);
    }

    printf("Father process exec...\n");
    if(fcntl(fd, F_SETLKW, &flk2) < 0) {
        perror("fcntl_proc2");
        exit(1);
    }

    printf("Father process get flk2..\n");
    printf("Father process ready to get flk1 ...\n");
    if(sem_post(s1) < 0) {
        perror("sem_post_proc2");
        exit(1);
    }

    /*!说明阻塞在这里了...*/
    if(fcntl(fd, F_SETLKW, &flk1) < 0) {
        if(errno == EDEADLK) {
            printf("Father process deadlock ocurr!\n");
        } else {
            perror("fcntl_proc2");
            exit(1);
        }
    }
}

int
main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    init();
    pid = fork();
    if(pid < 0) {
        perror("fork()");
        return 1;
    }

    if(pid == 0) {
        runProc1();
    } 

    runProc2();
    clear();

    return 0;
}

