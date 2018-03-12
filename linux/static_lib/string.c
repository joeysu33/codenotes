#include <stdio.h>

int StrLen(const char *s) {
    int n=0;
    if(!s) return 0;
    while(*(s++) != 0) {
        n++;
    }
    return n;
}
