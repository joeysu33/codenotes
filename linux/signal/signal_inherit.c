/*!
 * 本测试程序测试
 * 1.是否子进程在执行exec之前是否 * 会继承信号处理
 * 答：会继承，因为在exec之前，子进程和父进程的
 * 内存页是相同的（修改之前)
 *
 * 2.掌握waitpid搞清楚进程退出的reason
 * 3.在SIGCHLD中调用 while( waitpid(-1, NULL, WNOHANG) > 0); 来清理僵尸进程(defunct)
 *
 * 定时器不会从父进程继承
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

volatile sig_atomic_t quitNums;

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    int status;
    int pid;
    char s[64];

    /*!Unsafe in async signalIO*/
    printf("pid=[%d],ppid=[%d]:Received signal:%d, name:%s, from pid=%d\n",
            getpid(),
            getppid(),
            sig,
            strsignal(sig),
            si->si_pid);

    /*!硬件错误直接退出*/
    if(sig == SIGILL || 
            sig == SIGBUS ||
            sig == SIGFPE ||
            sig == SIGSEGV) {
        exit(1);
    }

    if(sig == SIGCHLD) {
        /*!如果要观察stop和continue的话，需要WUNTRACED和WCONTINUED */
        while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
            //正常退出
            if(WIFEXITED(status)) {
                strcpy(s, "normal exit");
            } else if(WIFSTOPPED(status)) {
                strcpy(s, "stopped");
            } else if(WIFCONTINUED(status)) {
                strcpy(s, "continued");
            } else if(WIFSIGNALED(status)){
                /*!非原子操作，赋值是原子操作 */
                //*******这个数值是父进程的值*/
                quitNums += 1;
                snprintf(s, sizeof(s), "signaled coredump:(%s), signo:%d", WCOREDUMP(status) ? "coredump": "nocoredump", WTERMSIG(status));
            } else {
                strcpy(s, "unknown");
            }

            printf("status=%d, terminated, reason=%s\n", status, s);

        }
    } 

    if(sig == SIGQUIT) {
        /*! ********这个值是子进程收到的值*/
        quitNums += 1;
        printf("I want to quit! [%d]\n", getpid());
        _exit(0);
    }
}

void
showPidAndPPid(const char *s) {
    printf("%s: pid=%d, ppid=%d\n", s, getpid(), getppid());
}

int main() {
    struct sigaction sa;
    int i, j;
    pid_t pid;
    char buf[32];
    int count;

    if(setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        perror("setvbuf");
        return 1;
    }

    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; 
    sa.sa_sigaction = sigaction_handler;

    /*!Unbuntu 没有SIG32,33 */
    for(i=34; i<NSIG; ++i) {
        if(i == SIGKILL || i== SIGSTOP) continue;
        if(sigaction(i, &sa, NULL) < 0) {
            snprintf(buf, sizeof(buf), "sigaction:%d, NSIG=%d", i, NSIG);
            perror(buf);
        }
    }
    sigaction(SIGQUIT, &sa, NULL) ;
    sigaction(SIGCHLD, &sa, NULL) ;

    showPidAndPPid("Initialize");
    for(i=0; i<5; ++i) {
        pid = fork();
        if(pid < 0) {
            perror("fork");
            return 1;
        } else  if(pid == 0) {
            snprintf(buf, sizeof(buf), "child[%d]", i+1);
            showPidAndPPid(buf);

            for(;;) pause();
            /*!调用不到 */
            _exit(0);
        } else {
            /*! Do nothing*/
        }
    }

    //不能用quitNums，子进程和父进程有各自独立的数值
    /*!
    for(;; ) {
        sleep(2);
        if(quitNums == 5) exit(0);
    }*/

    sleep(120);

    return 0;
}

