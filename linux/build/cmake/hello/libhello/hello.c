#include "hello.h"

int add(int a, int b) {
    return (a+b);
}

int getIsDefinedBuild() {
#if defined(LIBHELLO_BUILD)
    return 1;
#else
    return 0;
#endif
}

