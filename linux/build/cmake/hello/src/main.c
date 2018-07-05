#include <stdio.h>
#include <stdlib.h>
#include "hello.h"

int
main(int argc, char *argv[]) {
    printf("10+20=%d\n", add(10,20));
    printf("defined(LIBHELLO_BUILD)=%d\n", getIsDefinedBuild());

    return 0;
}
