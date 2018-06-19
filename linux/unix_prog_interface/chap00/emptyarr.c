/*!
 * 对于LinuxC中大量类似用法的说明
 * 例如
 * struct mymsg {
 *  long type;
 *  char mtext[]; //这里写成char mtext[]和char*的区别在于,char 
 * }
 *
 * 两者之间的区别:
 * 1.mtext[]不占空间，而char*占sizeof(cha*)空间
 * 2.而mtext已经能描述type之后的地址了，所以在数据结构上节省内存开销
 * 3.如果是char*的话，需要给指针重新分配空间，并且指向该地址，而mtext[]不用
 */
#include <stdio.h>
#include <memory.h>

typedef struct st1 {
    int a;
    char mtext[];
} st1_t;

typedef struct st2 {
    int a;
    char *mtext;
} st2_t;


int 
main() {
    char buf[32];
    st1_t *s1;
    st2_t *s2;

    printf("sizeof(st1_t) = %ld, sizeof(st2_t) = %ld.\n",
            sizeof(st1_t), sizeof(st2_t));

    
    s1 = (st1_t*)buf;
    s1->a = 10;
    strcpy(s1->mtext, "aabbccdd");
    printf("s1->a=%d, s1->mtext=%s.\n", s1->a, s1->mtext);

    s2 = (st2_t*)buf;
    s2->a = 10;
    strcpy(s2->mtext, "kkjjjj"); //这么写是错误的，因为s2->mtext指向的是一个指针，地址不会顺延
    printf("s2->a=%d, s2->mtext=%s.\n", s2->a, s2->mtext);

    return 0;
}
