/*!
 * 使用
 * void (*sa_action)(int sig, siginfo_t* info, void* ucontext);
 * 来替代 void (*sa_handler) (int sig)
 * siginfo_t可以描述更多的信息
 *
 * typedef struct siginfo
 * {
 *  si_signo,
 *  si_code, //描述信号发生的原因码
 * } siginfo_t;
 *
 * 本例用来演示使用sigaction来获取某个信号发生的原因
 * 本例以硬件信号SIGFPE，浮点异常来进行测试
 * 产生浮点异常的原因有很多种，参见Linux编程手册 P364
 * SIGFPE:
 * FPE_FLTDIV 浮点除0
 * FPE_FLTINV 无效的浮点操作
 * FPE_FLTOVF 浮点溢出
 * FPE_FLTRES 浮点结果不精确
 * FPE_FLTUND 浮点下溢
 * FPE_INTDIV 整型除以0
 * FPE_SUB    下标超出范围
 */

#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h> //strsignal

void 
handler(int sig, siginfo_t* si, void* ucontext) {
    char *s;
    /*! Unsafe in async SignalIO */
    printf("Receive signal:%d, %s\n", si->si_signo, strsignal(si->si_signo));
    switch(si->si_code) {
        case FPE_FLTDIV: {
                             s = "FPE_FLTDIV";
                             break;
                         } 
        case FPE_INTDIV: {
                             s = "FPE_INTDIV";
                             break;
                         }
        default: {
                     s = "other";
                     break;
                 }
    }
    /*!Unsafe in async sigIO */
    printf("code=%d, %s\n", si->si_code, s);
    /*!Unsafe in async sigIO */
    /*! 仅对硬件生成信号有效 */
    printf("address: 0x%p\n", si->si_addr);
    exit(1);
}

int
main() {
    int i;
    double d;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = handler;

    /*!
     * 其中SIGKILL和SIGSTOP是不允许安装信号处理器的
     */
    if(sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction ");
        return 1;
    }

    /*捕捉硬件错误的信号，例如SIGILL, SIGBUS, SIGFPE, SIGSEGV,会导致接下来的行为不确定，
     * 一般的做法就是退出程序 exit, _exit, abort, raise, kill等*/
    i = 1/0;  //递归调用handler


    //浮点数除以0，结果是inf (无穷大)，整型除以0，会发异常信号
    /*d=0;
    printf("d=%lf\n", d);
    d = 1.0/0;
    printf("d=%lf\n", d);
    */

    return 0;
}

