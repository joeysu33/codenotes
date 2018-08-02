#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static volatile sig_atomic_t handler = 0;

void
sigact(int sig) {
    if(sig == SIGALRM) {
        handler = 1;
    }
}

int
main(int argc, char *argv[]) {
    alarm(4);

    while(handler);
    printf("handled!\n");

    return 0;
}
