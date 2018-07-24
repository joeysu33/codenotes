/*!
 * 校验kr中的指纹算法的正确性,主要是针对指纹的更新算法
 * hash值的计算MAD (Multipy Add Mod)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef int64_t HashCode;
#define M 7919
#define R 256
#define DIGIT(s, i) (s[i]-'A') //如果不对该起始值，也就是'0'做限制很有可能会产生负值
#define SIZE 5

HashCode
hash2(const char *s, int len) {
    int i;
    HashCode hc = 0;
    for(i=0; i<len; ++i) {
        hc = ((hc *R) + DIGIT(s, i)) % M;
    }

    if(hc < 0) hc += M;
    return hc;
}

HashCode
hash(const char *s) {
    int i, j;
    if(!s) return -1;
    j = strlen(s);

    return hash2(s, j);
}

void
updateHash(HashCode *hc, const char *s, int k, int m, HashCode dm) {
    *hc = (*hc - DIGIT(s, k) *dm ) % M;
    *hc = (*hc * R + DIGIT(s, k+m)) % M;
    if( *hc < 0) *hc += M;
}

/*!
 * dm = R^(m-1)
 */
HashCode
makeDM(int j) {
    int i;
    HashCode hc;
    for(i=1, hc=1; i<j; ++i) hc *= R;
    return hc;
}

void
testHash(const char *s) {
    int i, j, k;
    HashCode hc, dm, h2;
    if(!s) return ;
    k = strlen(s);
    if(k < SIZE) return ;

    k-=SIZE;
    dm = makeDM(SIZE);
    hc = hash2(s, SIZE); //初始的hash值

    for(i=0; i<=k;) {
        /*!更新的hash值和直接计算的hash值必须相等 */
        updateHash(&hc, s, i, SIZE, dm);
        ++i;
        h2 = hash2(s+i, SIZE);
        if(hc != h2) {
            printf("hc=%ld, h2=%ld\n", hc, h2);
        }
        assert(hc == h2);
    }
}

int
main(int argc, char *argv[]) {
    testHash("jfei9f298e92jf9j9jw9eijfafndu92hfdsfu82782u3ihiijfdj9i092839ehfe9afhe9d928f9he8h9ehf298hf8hy28f7g82guadbhcjbjxzbjbvcjbxzjvhuhbvubud yfuiywefh8whfhwjifojewf9jf93j9fj93jf9jsjfjjfajdsf");
    return 0;
}


