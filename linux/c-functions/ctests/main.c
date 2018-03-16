#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

//#include <gnu/stubs.h>
//#include <gnu/libc-version.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    int flags;
    flags = O_RDONLY | O_WRONLY | O_RDWR | O_ACCMODE;
    printf("o_access_mode=%d\n", 007);

    printf("Hello World!\n");
    return 0;
}

