#include <stdio.h>
#include <assert.h>

#define N 5
static int s1[N];
static int s2, s3;

int
main(int argc, char *argv[]) {
    s1[N] = 5;
    assert(s2 == 5);

    s1[N+1] = 66;
    assert(s3 == 66);

    return 0;
}
