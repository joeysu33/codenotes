/*!
 * 基于Karp Rabin的字符串搜索算法
 * 通过指定一个基数
 * 二进制 2, 10进制10，ASCII字符128或256
 * 来将一个字符串转换成一个散列数值(HashCode)
 * ,并随着Text的移动来更新HashCode值。
 *
 * R:基数值
 * m:pat的长度
 * n:text的长度
 * nindex:text的索引值
 * M :取一个合式的素数做模运算，这里不存在空间复杂度
 * k:当前Text滑动的索引值
 * 
 * MAD算法 Multipy Add /Mode, 计算hash值的三要素
 * hashcode的计算 hashcode += (hashcode * R) + digit(T, nindex) / M;
 *
 * 在移动的过程中还需要剔除掉最高位之前的值R^(m-1) * digit(T, k-1);
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef int64_t HashCode;

#define R 128
#define M 541

int
digit(const char *s, int index) ;

/*!
 * 准备乘数，也就是滑动过程中
 * 更新HashCode的时候对最高位执行
 * hashcode -= dm * T(k-1);
 */
HashCode
prepareDM(const char *p) {
    int i, m;
    HashCode dm ;

    if(!p) return (int64_t)-1;
    m = strlen(p);
    for(i=1, dm=1; i < m; ++i) {
        /*! 做模运算了是否可以恢复??? */
        dm = (dm * R) % M;
    }

    return dm;
}

// 子串指纹快速更新算法
//void updateHash ( HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm ) {
//   hashT = ( hashT - DIGIT ( T, k - 1 ) * Dm ) % M; //在前一指纹基础上，去除首位T[k - 1]
//   hashT = ( hashT * R + DIGIT ( T, k + m - 1 ) ) % M; //添加末位T[k + m - 1]
//   if ( 0 > hashT ) hashT += M; //确保散列码落在合法区间内
//}
/*!
 * 要注意的是k要保证不会越界,小心k是加完以后的还是加之前的
 */
void
updateHashCode(HashCode *hashcode, const char *t, int k, int m,HashCode dm) {
    *hashcode = (*hashcode     - digit(t, k-1) *dm ) % M;
    *hashcode = (*hashcode * R + digit(t, m+k-1)) % M;
    if( *hashcode < 0) *hashcode += M;
}

/*!
 * 可能存在冲突，进行逐一比对
 */
int
strCMP(const char *t, const char *p, int k) {
    const char *pp;
    for(pp = t+k; *p; ) {
        if(*(p++) != *(pp++)) return -1;
    }

    return 0;
}

/*!
 * 取出对应字符所对应的进制数据
 */
int
digit(const char *s, int index) {
    return (*(s+index) - 'A'); //这里的'A',如果是ascii的话根据实际情况进行设置
}

void
showProgress(const char *t, const char *p, int k) {
    int i, j, m, n;
    m = strlen(p);
    n = strlen(t);

    //索引
    for(i=0; i<n; ++i) printf("%4d ", i);
    printf("\n");
    //值
    for(i=0; i<n; ++i) printf("%4c ", t[i]);
    printf("\n");
    //匹配位置
    for(i=0; i<k; ++i) printf("%4c ", ' ');
    printf("%4c ", '|');
    printf("\n");
    //模式字符串
    for(i=0; i<k; ++i) printf("%4c ", ' ');
    for(; *p ;++p ) printf("%4c ", *p);
    printf("\n");
}

/*!
 * Karp-Rabin主算法
 */
int
KarpRabin(const char *t, const char *p) {
    HashCode thash, phash, dm;
    int i, j, k, m, n;

    m = strlen(p);
    n = strlen(t);
    /*!计算初始t中前m个字符的hash值
     * 计算初始p中的hash值
     * MAD:Hash值的生成算法 ((hashcode * a) + b) % c
     * a <==> R
     * b <==> digit(T, index)
     * c <==> M
     */
    thash = phash = 0;
    if(m > n) return -1; /*! n必须大于m */

    dm = prepareDM(p);
    for(i=0; i<m; ++i) {
        thash = ((thash * R) + digit(t, i)) % M;
        phash = ((phash * R) + digit(p, i)) % M;
    }
    /*!thash和phash有溢出风险，最好回归到M以内*/
    if(thash < 0) thash += M;
    if(phash < 0) phash += M;

    for(k=0, j=n-m;k <= j ;) {
        if(thash == phash) {
            if(strCMP(t, p, k) == 0) return k;
        }

        //showProgress(t, p, k);
        k++; //k已经滑动
        updateHashCode(&thash, t, k, m, dm);
    }

    return -1;
}

#define FIND(t, p) \
    do{\
        int i=KarpRabin(#t, #p);\
        if(i<0) {\
            printf("Not Found:"#p"\n");\
        }else {\
            printf("Found it, in %d, %s\n",i, #p);\
        }\
    }while(0)

int
main(int argc, char *argv[]) {
    FIND(ofjoewjfojwfoewjofjwofejojojfowfjojfeohhnbvxzjb, nbvxz);
    FIND(4939fhas9df9h9fe2hj9fjjasofdosaf994293849, 42938);
    FIND(893489rufhfh9hf9h29fh9jsf9284nbvcbxcv, 4039409304jjjf);
    FIND(094jf999324hf998hdsaf78921r-=a=fjsofdjof, =fjsofdjof);
    FIND(094jf999324hf998hdsaf78921r-=a=fjsofdjof, 094);

    return 0;
}



