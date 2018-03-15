#include <stdio.h>

typedef struct _time_t {
    unsigned char sec;
    unsigned char hour;
    unsigned char min;
} time_t;

int main() {
    /*! c99的写法*/
    time_t t1= {.sec=10, .hour=20, .min=30};
    time_t t2= {10,20,30};
    return 0;
}
