#include "common.h"
#include <stdlib.h>
#include <stdarg.h>

void err_exit(const char* msg,...) {
    fflush(stderr);

    /*! ----- varargs------*/
    va_list ap;
    va_start(ap, msg);
    vfprintf(stderr,msg, ap);
    va_end(ap);
    /*! ----- varargs------*/

    perror(msg);
    fflush(stderr);
    exit(-1);
}

