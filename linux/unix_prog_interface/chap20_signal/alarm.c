/*!
 * sleep一般在linux上使用SIGALRM来实现
 * int sigsuspend(sigset_t *mask)
 * 所以要特别注意的是sleep和setitimer以及
 * alarm不要同时使用，容易出问题，因为底层
 * 都是使用sigsuspend来实现的。
 */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void sighandler(int sig) {
    /*!It's not saft in saync for printf , strerror */
    printf("Caught signal:%d, %s.\n", sig, strsignal(sig));
}

int
main(int argc, char *argv[]) {
    int i,j;
    long sec;
    char *endptr;
    struct sigaction sa;
    sigset_t mask, prevMask, mask2;

    if(argc != 2) {
        fprintf(stderr, "%s <sleep_time(seconds)>.\n", argv[0]);
        return 1;
    }

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGALRM);
    sa.sa_flags = 0;
    sa.sa_handler = sighandler;
    if(sigaction(SIGALRM, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }
    sec = strtol(argv[1], &endptr, 0);
    sigemptyset(&mask);
    sigemptyset(&prevMask);

    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    /*!一般情况下sigsuspend和sigprocmask联合使用*/
    if(sigprocmask(SIG_BLOCK, &mask, &prevMask) < 0) {
        perror("sigprocmask");
        return 1;
    }

    /*!开始sleep*/
    printf("Start to sleep %ld seconds...\n", sec);
    sigemptyset(&mask2);
    for(i=1; i<NSIG; ++i) {
        if(i != SIGALRM)
            sigaddset(&mask2, i);
    }

    /*!!!!!!!!!!!!!!!!!!!!!!!!*/
    alarm(sec);
    if(sigsuspend(&mask2) < 0 && errno != EINTR) {
        perror("sigsuspend");
        return 1;
    }
    /*!!!!!!!!!!!!!!!!!!!!!!!!*/

    printf("Finish!\n");
    if(sigprocmask(SIG_SETMASK, &prevMask, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }

    return 0;
}

