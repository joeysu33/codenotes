/*!
  卡塔兰数
  Catalan(n) = C(2n,n)/n!
                       = (2n)! / (n+1)! *n!

    卡塔兰数解决的问题
    1.堆栈混洗个数
 */
#include <iostream>
#include <stdint.h>
#include <cstdio>

using namespace std;

typedef int64_t Int64;

Int64 factorial(int n) {
    if(n <= 1) return 1;
    return (Int64)n * factorial(n-1);
}

Int64 factorial2(int n) {
    if(n < 1) return 1;
    Int64 r = 1;
    while(n) {
        r *= n--;
    }
    return r;
}

Int64 catalan(int n) {
    return factorial2(2*n) /(factorial2(n+1) * factorial2(n));
}

int main()
{
    int n, i;
    do {
        i = scanf("%d", &n);
        if(n < 0 || n>100) break;
        printf("%ld\n", catalan(n));
    } while(i);

    return 0;
}
