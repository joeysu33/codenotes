/*!
 * 设计算法，计算超大整数之间的运算
 * INT_MAX -21 *10^9 ~ 21*10^9
 * 0000每隔4位作为一个数值,描述0-9 A B C D E
 * 但是这里仅使用10进制,满10进一位
 * !1 == 0
 * !0 == 1
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
    char m_sign;    //单独的符号位 0:表示正号，1:表示负号
    int m_len;      //实际存储所占的字节数, 从右往左的占位长度,可以将len修改为half-char所占的个数，这样很精确
} BigInt, *PBigInt;

char *bigInt2Char(PBigInt i) {
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
 * i1+i2,并将结果写入到i1中 , i1和i2的符号相同,
 * 计算失败返回NULL*/
PBigInt
add2(PBigInt i1, PBigInt i2) {
    if(!i1 || !i2) return NULL;
    if(i1->m_sign != i2->m_sign)  return NULL;
    int len1 = i1->m_len, len2 = i2->m_len, len;
    int j, k, l, t;
    //避免溢出len1
    assert(len1 < NMAX -1);
    if(len1 < 1 || len2 < 1) return NULL;

    /*! 将计算长度对齐*/
    len = len1 > len2 ? len1 : len2;
    for(j=0, k=0, l=0; j<=len; ++l) {
        if(l % 2 == 0) {
            j++;
            k++;

            t = i1->m_d[NMAX - j].m_low + i2->m_d[NMAX -k].m_low;
            i1->m_d[NMAX -j].m_low  = t % 10; //计算结果
            i1->m_d[NMAX -j].m_high += t / 10; //发生进位
        } else {
            t = i1->m_d[NMAX -j].m_high + i2->m_d[NMAX -k].m_high;
            i1->m_d[NMAX -j].m_high = t % 10;   //计算结果
            i1->m_d[NMAX -j -1].m_low += t / 10; //发生进位
        }
    }

    return i1;
}

/*! i1-i2,并将结果写入到i1中, i1和i2符号位不同,
 * 且保证i1 > 0, i2 < 0
 * 计算失败返回NULL*/
PBigInt
sub2(PBigInt i1, PBigInt i2) {
    PBigInt i, j;
    int m, n, t, l, borrow;
    if(!i1 || !i2) return NULL;
    if(i1->m_sign == i2->m_sign) return NULL;
    int len1 = i1->m_len, len2 = i2->m_len, len;
    if(len1 < 1 || len2 < 1) return NULL;

    i = i1; j = i2;
//    char *cp1, *cp2, *cp3;
//    cp1 = bigInt2Char(i1);
//    cp2 = bigInt2Char(i2);
//    printf("\ti1(%s) - i2(%s) =", cp1, cp2);
    /*! 将计算长度对齐 */
    len = len1 > len2 ? len1 : len2;
    borrow = 0; //记录上次是否有发生借位
    for(m=n=l=0; m <= len; ++l) {
        if(l % 2 == 0) {
            m++;
            n++;

            t = i->m_d[NMAX - m].m_low - j->m_d[NMAX -n].m_low - borrow;
            if(t >= 0) {
                i->m_d[NMAX -m].m_low = t;
                borrow = 0;
            } else {
                i->m_d[NMAX -m].m_low = t + 10; //从高位来借一位，如果高位为0呢,之前设计为无符号的就好了@^@
                borrow = 1;
            }
        } else {
            t = i->m_d[NMAX - m].m_high - j->m_d[NMAX -n].m_high- borrow;
            if(t >= 0) {
                i->m_d[NMAX -m].m_high = t;
                borrow = 0;
            } else {
                i->m_d[NMAX -m].m_high = t + 10; //从高位来借一位，如果高位为0呢,之前设计为无符号的就好了@^@
                borrow = 1;
            }
        }
    }

    /*! 最高位发生借位，revert符号位 */
    if(borrow) i->m_sign = !i->m_sign;
//    cp3 = bigInt2Char(i1);
//    printf("%s\n",cp3);
//    free(cp1);free(cp2);free(cp3);

    return i1;
}

PBigInt
add(PBigInt i1, PBigInt i2) {
    if(!i1 || !i2) return NULL;
    /*! 符号位相同 */
    if(i1->m_sign == i2->m_sign) return add2(i1, i2);
//    /*! 符号位不同 */
//    if(i1->m_sign) {
//        BigInt in1, in2;
//        in1 = *i1, in2 = *i2;
//        sub2(&in2, &in1);
//        *i1 = in2;
//        return i1;
//    }

    return sub2(i1, i2);
}

PBigInt
sub(PBigInt i1, PBigInt i2) {
    if(!i1 || !i2) return NULL;

    i2->m_sign = !i2->m_sign; // !0 = 1; !1 = 0;
    return add(i1, i2);
}

void
testBigInt() {
    const char *s[] = {
        "-310923019209109389280829830910290190290190290190290192",
        "84398598938982348902930920930203",
        "-90320930921093029",
        "-90392093",
        "11111111111111111111111111111111111111111111111",
        "-2222222222222222222222222222222222222222222222",
        "7777777777777777777777777777777777777777777777777777777777777",
        "898490000000001",
        "-1000000001",
    };

    int count = sizeof(s)/sizeof(char*), i;
    BigInt i1;
    char *ez;
    /* for(i=0; i<count; ++i) {
        makeBigInt(s[i], &i1);
        ez = bigInt2Char(&i1);
        assert(ez);
        printf("i=%d\ns[%d]=%s, bigInt2Char=%s\n", i, i, s[i],ez);
        assert(!strcmp(s[i], ez));
        free(ez);
    } */

    printf("\n\n");
    BigInt i2, i3, i4;
    char *cp1, *cp2;
    for(i=0; i<count-1; ++i) {
        makeBigInt(s[i], &i2);
        makeBigInt(s[i], &i4);
        makeBigInt(s[i+1], &i3);

        add(&i2, &i3); //结果存储到i2
        sub(&i4, &i3); //结果存储到i4
        cp1 = bigInt2Char(&i2);
        cp2 = bigInt2Char(&i4);
        assert(cp1); assert(cp2);

        //add
        printf("====>i=%d, s[%d]=%s, s[%d]=%s\nadd(s[%d], s[%d]) = %s\n", i,
                i, s[i],
                i+1, s[i+1],
                i, i+1,
                cp1);
        free(cp1);
        printf("\n");

        //sub
        printf("====>i=%d, s[%d]=%s, s[%d]=%s\nsub(s[%d], s[%d]) = %s\n", i,
                i, s[i],
                i+1, s[i+1],
                i, i+1,
                cp2);
        free(cp2);
        printf("\n");
    }
}

int
main(int argc, char *argv[]) {
    testBigInt();
    return 0;
}

