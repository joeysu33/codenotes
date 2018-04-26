/*!
 * struct 聚合strct的size
 * 计算重点
 * 1.除char之外的类型，例如short int long等，起始地址都是偶地址
 * 2.关于该数据结构中（包含子数据结构类型），最大的类型地址对齐（最大一般是8个字节)
 */
#include <stdio.h>

//sizeof(st_b) == 16
struct st_b {
    int sb_x;
    double sb_y;
};

/*!
 * 16+24 = 40
 */
struct st_a {
    struct st_b sa_b;
    int  sa_i;
    char sa_c1:1;
    double sa_d;
    char sa_c2:7;
};

/*! 24 bytes*/
struct st_b1 {
    int sb_x;
    double sb_y;
    double sb_z;
};

struct st_c {
    //struct st_b1 sa_b;
    double sa_d1;
    short sa_i;
    char sa_c1;
    int  sa_i1;
    char sa_c2;
};

struct st_d {
    short sd_1;
    char sd_2;
    char sd_3;
    int sd_4;
};

/*!
 * 12个字节
 * char a 占1个字节
 * short a1占2个字节从偶数地址开始对齐
 * char a2 占1个字节
 * int b 占4个字节从偶数地址开始对齐
 */
struct st_e {
    char a;
    short a1;
    char a2;
    int  b;
};


int
main() {
    struct st_c stc;

    printf("sizeof(st_b)=%ld\n", sizeof(struct st_b));
    printf("sizeof(st_b1)=%ld\n", sizeof(struct st_b1));
    printf("sizeof(st_a)=%ld\n", sizeof(struct st_a));
    printf("sizeof(st_c)=%ld\n", sizeof(struct st_c));
    printf("sizeof(st_d)=%ld\n", sizeof(struct st_d));
    printf("sizeof(st_e)=%ld\n", sizeof(struct st_e));

    printf("&st_c=%p &st_c-endptr=%p\n", &stc, (char*)&stc + sizeof(stc));
    printf("&st_c.sa_d1=%p\n", &stc.sa_d1);
    printf("&st_c.sa_i=%p\n", &stc.sa_i);
    printf("&st_c.sa_c1=%p\n", &stc.sa_c1);
    printf("&st_c.sa_i1=%p\n", &stc.sa_i1);
    printf("&st_c.sa_c2=%p\n", &stc.sa_c2);

    return 0;
}



