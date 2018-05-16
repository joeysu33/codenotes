/*!
 * 回显参数和环境变量
 */
#define _GNU_SOURCE //support environ

#include <stdio.h>
#include <unistd.h> //environ

int main(int argc, char *argv[]) {
    int i;
    char * const *p = argv;

    for(i=0; *p; ++p) {
        printf("argv[%d]=%s\n", i++, *p);
    }

    p = environ;
    printf("environment:\n");
    for(i=0; *p; ++p) {
        printf("\t%s\n", *p);
    }

    return 0;
}
