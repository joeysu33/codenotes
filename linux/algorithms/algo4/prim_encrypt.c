/*!
 * 使用素数来对一组向量进行加密，并还原
 * 设向量的维度为N
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 5

int 
isPrime(int x) {
    int i;
    for(i=2;i < x;i++) {
        if(x % i == 0) return  0;
    }

    return 1;
}

void
getPrime(int n[], int size) {
    int i, j;
    if(size < 1) return ;
    for(i=0, j=2; ;++j) {
        if(isPrime(j)) {
            n[i++]=j; if(i == size) break;
        }
    }
}

void
testPrimeEncrypt() {
    int i, j, index;
    int64_t u, k;
    int ai[N] = {3, 5, 8, 1, 6};
    int rai[N], xi[N];
    getPrime(xi, N);
    
    /*! xi[i]^(ai[i]+1) 进行求和运算 */
    for(i=0; i<N; ++i) {
        k= 1;
        for(j=0; j<=ai[i]; ++j) {
            k *= xi[i];
        }
        u += k;
    }

    /*!根据u的值来还原ai */
    i=0; index=0;
    while(u > 1) {
        for(j=0; j<N; ++j){
            if(u % xi[j]  == 0) {
                index++;
                u /= xi[j];
            } else 
                i++;
        }
    }
}

int 
main(int argc, char *argv[]) {
    testPrimeEncrypt();
    return 0;
}

