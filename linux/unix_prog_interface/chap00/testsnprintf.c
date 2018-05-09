#include <stdio.h>

int main() {
    char buf[4];
    /*!snprintf和strncpy不同，strncpy最多会拷贝到size snprintf为size-1*/
    snprintf(buf, 4, "abcde");
    printf("buf=%s", buf);
    return 0;
}
