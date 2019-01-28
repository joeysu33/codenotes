#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <semaphore.h>
#include <assert.h>

void show(int pid, const char *title, const char c) {
    printf("PID=0x%x, %s:%c\n", pid, title, c);
}

void newChild(int pid, int parent) {
    printf("PID:0x%x,  PPID:0x%x\n", pid, parent);
}

static const char *s0 = "/ss0";
static const char *s1 = "/ss1";
static const char *s2 = "/ss2";
static const char *s3 = "/ss3";

int main()
{
    int pfd[2];
    int n = pipe(pfd);
    if(n < 0) return 1;

    //避免冲突
    sem_unlink(s0);
    sem_unlink(s1);
    sem_unlink(s2);
    sem_unlink(s3);

    sem_t * se0 = sem_open(s0, O_CREAT | O_EXCL, 0660, 0);
    sem_t * se1 = sem_open(s1, O_CREAT | O_EXCL, 0660, 0);
    sem_t * se2 = sem_open(s2, O_CREAT | O_EXCL, 0660, 0);
    sem_t * se3 = sem_open(s3, O_CREAT | O_EXCL, 0660, 0);

    if(!se0 || !se1 || !se2 || !se3) return 10;

    int pid;
    pid = fork();
    //error writing
    //if((pid = fork()) < 0) return 1;
    //导致fork之后的执行并没有进行分流,从而导致了这个问题
    assert(pid >= 0);
    if(pid == 0) {
        //child1
        close(pfd[1]);
        newChild(getpid(), getppid());
        sem_t *ss1 = sem_open(s1, 0);
        sem_t *ss2 = sem_open(s2, 0);
        assert(ss1 && ss2);
        sem_wait(ss1);
        char c;
        read(pfd[0], &c, 1);
        show(getpid(), "s1", c);
        sem_post(ss2);
        close(pfd[0]);
        sem_destroy(ss1);
        sem_destroy(ss2);
        return 0;
    }

    pid = fork();
    assert(pid >= 0);
    if(pid == 0) {
        //child2
        close(pfd[1]);
        newChild(getpid(), getppid());
        sem_t *ss2 = sem_open(s2, 0);
        sem_t *ss3 = sem_open(s3, 0);
        assert(ss2 && ss3);
        sem_wait(ss2);
        char c;
        read(pfd[0], &c, 1);
        show(getpid(), "s2", c);
        sem_post(ss3);
        close(pfd[0]);
        sem_destroy(ss2);
        sem_destroy(ss3);
        return 0;
    }

    pid = fork();
    assert(pid >= 0);
    if(pid == 0) {
        //child3
        close(pfd[1]);
        newChild(getpid(), getppid());
        sem_t *ss0 = sem_open(s0, 0);
        sem_t *ss3 = sem_open(s3, 0);
        assert(ss0 && ss3);
        sem_wait(ss3);
        char c;
        read(pfd[0], &c, 1);
        show(getpid(), "s3", c);
        sem_post(ss0);
        close(pfd[0]);
        sem_destroy(ss0);
        sem_destroy(ss3);
        return 0;
    }

    printf("start main!!!\n");
    close(pfd[0]);
    write(pfd[1], "xyz", 3);
    sem_post(se1);
    sem_wait(se0);

    printf("finish all!!!\n");
    close(pfd[1]);
    sem_destroy(se0);
    sem_destroy(se1);
    sem_destroy(se2);
    sem_destroy(se3);

    return 0;
}
