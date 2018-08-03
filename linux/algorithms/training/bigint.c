/*!
 * 设计算法，计算超大整数之间的运算
 * INT_MAX -21 *10^9 ~ 21*10^9
 * 0000每隔4位作为一个数值,描述0-9 A B C D E
 * 但是这里仅使用10进制,满10进一位
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NMAX 100

typedef struct _Base{
    unsigned char m_low:4;
    unsigned char m_high:4;
} Base;

typedef struct _BigInt {
    Base m_d[NMAX]; // 在C语言中 struct { unsigned char m_a:4, m_b:4 ;}仅占一个字节空间
    char m_sign; //单独的符号位 0:表示正号，1:表示负号
    int m_len;   //实际存储所占的字节数, 从右往左的占位长度
} BigInt, *PBigInt;

typedef struct _UnsignedBigInt {
} UnsignedBigInt, UBigInt, *PUBigInt;

char *easyChar(PBigInt i) {
    if(!i) return NULL;
    if(i->m_len < 1) return NULL;
    char * r = (char*)malloc((NMAX+1) * sizeof(char)), *res = r; //signed
    int k;
    *r = 0;
    if(i->m_sign) { *(r++) = '-'; }
    int j;

    /*! 处理第一位 */
    j = NMAX-i->m_len;
    if(i->m_d[j].m_high != 0)
        *(r++) = i->m_d[j].m_high + '0';
    //低位一定不会为0
    *(r++) = i->m_d[j].m_low + '0';
    for(j++; j < NMAX; ++j) {
        *(r++) = i->m_d[j].m_high + '0';
        *(r++) = i->m_d[j].m_low + '0';
    }

    *r = 0;
    return res;
}

void
makeBigInt(const char *s, PBigInt i) {
    if(!s || !i) return ;
    int len = strlen(s) ;
    if(len < 1) return ;

    memset(i, 0, sizeof(BigInt));
    i->m_sign = (*s == '-') ? 1 : 0;
    i->m_len = 0;
    int j, k;
    const char *end = s;
    if(!i->m_sign) end--; //去掉符号位,是符号位，不用第一位
    s = s + len -1; //将s移动到最后位置

    //k表示数值的个数, k/2+1表示char的长度(相差1)
    for(j=NMAX, k=0; end != s && j >= 0; --s, k++) {
        //交替来设置i->m_d[j].m_low和i->m_d[j].m_high
        if(k % 2 == 0) {
            j--;
            i->m_d[j].m_low = *s - '0';
        } else {
            i->m_d[j].m_high =*s - '0';
        }
    }

    i->m_len = k / 2;
    if(k % 2 != 0) i->m_len++;

    /*! 解决-0 != 0的情况 */
    if(!i->m_len) i->m_sign = 0;
}

/*!
 * i1+i2,并将结果写入到i1中 */
PBigInt
add(PBigInt i1, PBigInt i2) {
    if(!i1 || !i2) return i1;
    int len1 = i1->m_len, len2 = i2->m_len;
    int j, k, l, t;
    //避免溢出len1 
    assert(len1 < NMAX -1);
    if(len1 < 1 || len2 < 1) return i1;

    /*!考虑符号????*/
    for(j=0, k=0, l=0; j>=len1 && k >= len2; ++l) {
        if(l % 2 == 0) {
            j++;
            k++;

            t = i1->m_d[NMAX - j].m_low + i2->m_d[NMAX -k].m_low;
            i1->m_d[NMAX -j].m_low  = t % 10; //计算结果
            i1->m_d[NMAX -j].m_high = t / 10; //发生进位
        } else {
            t = i1->m_d[NMAX -j].m_high + i2->m_d[NMAX -k].m_high;
            i1->m_d[NMAX -j].m_high = t % 10;   //计算结果
            i1->m_d[NMAX -j -1].m_low = t / 10; //发生进位
        }
    }

    return i1;
}

void
testBigInt() {
    const char *s[] = {
        "-310923019209109389280829830910290190290190290190290192",
        "84398598938982348902930920930203",
        "90320930921093029",
        "90392093",
        "11111111111111111111111111111111111111111111111",
        "-2222222222222222222222222222222222222222222222",
        "7777777777777777777777777777777777777777777777777777777777777"
    };

    int count = sizeof(s)/sizeof(char*), i;
    BigInt i1;
    char *ez;
    for(i=0; i<count; ++i) {
        makeBigInt(s[i], &i1);
        ez = easyChar(&i1);
        assert(ez);
        printf("i=%d\ns[%d]=%s, easyChar=%s\n", i, i, s[i],ez);
        assert(!strcmp(s[i], ez));
        free(ez);
    }
}

int
main(int argc, char *argv[]) {
    testBigInt();
    return 0;
}

