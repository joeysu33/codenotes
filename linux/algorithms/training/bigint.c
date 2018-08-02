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
    j = NMAX-i->m_len-1;
    if(i->m_d[j].m_high != 0)
        *(r++) = i->m_d[j].m_high + '0';
    if(i->m_d[j].m_low != 0)
        *(r++) = i->m_d[j].m_low + '0';
    for(++j; j < NMAX; ++j) {
        *(r++) = i->m_d[j].m_high + '0';
        *(r++) = i->m_d[j].m_low + '0';
    }

    *r = 0;
    return res;
}

/*!
 * \brief bigInt2Char Has some bugs
 * \param i
 * \return
 */
char* bigInt2Char(PBigInt i) {
    if(!i) return NULL;
    if(i->m_len < 1) return NULL;

    assert(i->m_len * 2 < NMAX);
    char * r = (char*)malloc((NMAX+1) * sizeof(char)), *res = r; //signed
    Base * pb = &i->m_d[NMAX - i->m_len], *end = &i->m_d[NMAX-1];
    int j;

    *r = 0; //初始为空字符串
    end++; //退回到最右侧, 无效位置
    pb--; //向后退一步，从偶数序列开始访问
    if(i->m_sign) { *r = '-'; *(++r) = 0; }

    //从非0开始，偶数访问低位，奇数访问高位
    for(j=0; j<i->m_len * 2; ++j) {
        if(j % 2 == 0) {
            pb++;
            if(pb->m_low != 0) break;
        } else {
            if(pb->m_high != 0) break;
        }
    }

    while(*r) r++; //找到最末尾的位置，开始插入
    while(pb != end) {
        if(j % 2 == 0) {
            pb++;
            *(r++) = pb->m_low + '0';
        } else {
            *(r++) = pb->m_high + '0';
        }
        ++j;
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
    //if(k % 2 != 0) i->m_len++;

    /*! 解决-0 != 0的情况 */
    if(!i->m_len) i->m_sign = 0;
}

PBigInt
add(PBigInt i1, PBigInt i2) {
    PBigInt i = NULL;
    return i;
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
    char *pc = NULL, *ez;
    for(i=0; i<count; ++i) {
        makeBigInt(s[i], &i1);
        ez = easyChar(&i1);
        //pc = bigInt2Char(&i1);
        assert(ez);
        //assert(pc);
        printf("i=%d\ns[%d]=%s, pc=%s, easyChar=%s\n", i, i, s[i], pc, ez);
        assert(!strcmp(s[i], ez));
        //free(pc);
        free(ez);
    }
}

int
main(int argc, char *argv[]) {
    testBigInt();
    return 0;
}

