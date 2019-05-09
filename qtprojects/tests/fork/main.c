#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    for(int i=0; i<3; ++i)
    {
        if((pid = fork()) < 0) {
            exit(1);
        } else if(pid == 0) {
            printf("PID:0x%x,  PPID:0x%x\n", getpid(), getppid());
            return 0;
        }
    }
    printf("Hello World!\n");
    return 0;
}
