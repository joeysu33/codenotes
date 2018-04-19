/*!
 * struct {
 * char a[]; 不占空间
 * }
 * 保证对齐
 */

#include <stdlib.h>
#include <stdio.h>

/*!4个字节*/
typedef struct sta {
    int x:1;
    int y:3;
    int z:16;
    int pad:12;
    char arr[]; //char arr不占空间,仅仅指向sta的末尾，等价于sta+(arr前面所有的数据长度)
} sta_t, *sta_pt;

/*!16个字节，跟类型最大的对齐, char*占8个字节(64bit)*/
typedef struct stb {
    int x:1;
    int y:3;
    int z:16;
    int pad:12;
    char *arr; //arr占sizeof(char*)个字节
} stb_t, *stb_pt;

/*! 8个字节，跟类型最大的字节对齐*/
typedef struct stc {
    int x:1;
    int y:3;
    int z:16;
    int pad:12;
    int i1;
} stc_t, *stc_pt;

/*! 8+8+8+8=24*/
typedef struct std {
    int b1:1; //8
    char *ap1; //8
    double y; //8
    int b2:3; //b2,b3 8
    int b3:4;
} std_t, *std_pt;

/*! 8+8 = 16 */
typedef struct ste {
    int x;
    double z;
} ste_t, *ste_pt;

/*! 8+8+8 = 24 */
typedef struct stf {
    int x;
    double y;
    int z;
}stf_t, *stf_pt;

/*! 4+4+8=16 */
typedef struct stg {
    int x;
    int z;
    double y;
}stg_t, *stg_pt;

/*!
 * 大小就是0
 * C++不同，C++为了区别对象,struct null {}占1个字节
 */
typedef struct snull {
} snull_t;

/*
 * 这种写法编译不过去
 * 因为arr[]不占空间，仅是一个地址别名
 */
/*typedef struct snull2 {
    char arr[];
} snull2_t;
*/

int
main() {
    sta_t s;
    s.x=0;
    s.y=7;

    /*! 在构建一个结构体的时候，隐含给了1个字节的空间,
     * 按理说snull_t不占空间，问题是没有空间就不存在地址*/
    snull_t s1, s2;

    printf("sizeof(double) = %lu\n", sizeof(double));
    printf("sizeof(sta_t) = %lu\n", sizeof(struct sta));
    printf("sizeof(stb_t) = %lu\n", sizeof(struct stb));
    printf("sizeof(stc_t) = %lu\n", sizeof(struct stc));
    printf("sizeof(std_t) = %lu\n", sizeof(struct std));
    printf("sizeof(ste_t) = %lu\n", sizeof(struct ste));

    printf("sizeof(stf_t) = %lu\n", sizeof(struct stf));
    printf("sizeof(stg_t) = %lu\n", sizeof(struct stg));

    printf("siezof(snull_t) = %lu\n", sizeof(struct snull));
    //printf("sizeof(snull2_t) = %lu\n", sizeof(struct snull2));
    printf("s1=%p, s2=%p\n", &s1, &s2);
    *(char*)&s1 = 'a';
    *(char*)&s2 = 'b';
    printf("s1=%p, s2=%p, s1=%c s2=%c\n", &s1, &s2, *(char*)&s1, *(char*)&s2);

    *(char*)&s1 = 'c';
    *(char*)&s2 = 'd';
    printf("s1=%p, s2=%p, s1=%c s2=%c\n", &s1, &s2, *(char*)&s1, *(char*)&s2);

    return 0;
}


