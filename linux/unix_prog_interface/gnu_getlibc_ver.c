#include <gnu/libc-version.h>
#include <stdio.h>

int main() {
    const char* ver = gnu_get_libc_version();
    printf("glibc-version:%s\n", ver);
    return 0;
}

