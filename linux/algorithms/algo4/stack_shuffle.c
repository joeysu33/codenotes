/*!
 * 栈混洗
 * 使用卡特兰公式可以得到栈混洗的个数
 * Catalan(n) = (2n)!/(n! * (n+1)!)
 *
 * 遍历所有的栈序列，并构建校验栈来校验
 * 序列是否满足条件，大部分都满足，所以
 * 暴力遍历法的效率还可以
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STAK_NUM 1024
//#define STEP

static int input[MAX_STAK_NUM], 
           stack[MAX_STAK_NUM], 
           out[MAX_STAK_NUM]; 
static int rcount, pcount;

/*!
 * 判断一个序列是否是栈序列
 */
int
isStackOrder(const int count) {
    int i, j, k;
    i=j=0;
    k= -1;

    //将out的对比完成
    while(j < count) {
        if(i < count && input[i] == out[j]) {
            ++i;
            ++j;
        } else if(k>=0 && out[j] == stack[k]){
            ++j;
            --k;
        } else {
            stack[++k] = input[i];
            ++i;
        }
    }

    return (k == -1);
}

void
showOut(const int count) {
    for(int i=0; i<count; ++i) {
        printf("%-2d", out[i]);
    }
    printf("\n");
    fflush(stdout);

#if defined(STEP)
    getchar();
#endif
}

/*!
 * 回溯法遍历所有的input序列到out*/
void
permutation(const int count) {
    if(count < 1) return ;

    //使用回溯法来遍历所有子序列,tag表示每次的取值位置 input[(*tag)]
    //回溯过程中，如果发现上层的tag值已经使用，则不能再次使用
    unsigned char *tag = (char*)malloc(sizeof(char) * count);
    for(int i=0; i<count; ++i) *(tag+i) = 0;
    int level = 0; //处理到第几层数据
    int i, j, k, ok;
    for(; *tag < count; ) {
        if(level == count) {
            //输出一组排列
            for(int m=0; m<count; ++m) {
                out[m] = input[*(tag+m)];
            }
            pcount++;
            if(isStackOrder(count)) {
                showOut(count);
                rcount++;
            }
            --level;
            if(level >= 0)
                *(tag+level) += 1; //step
            continue; //tag的数值增加，校验是否已经超出限制
        }
        
        i = *(tag+level);
        //指定一个不冲突的数值给i
        for(j=i; j<count; ++j) {
            ok = 1;
            for(k=0; k<level;++k) {
                if(*(tag+k) == j) {
                    ok = 0;
                    break;
                }
            }

            if(ok) { *(tag+level) = j; break;}
        }

        //进行回溯
        if(i >= count || !ok) {
            *(tag+level) = 0;
            level--;
            if(level >= 0)
                *(tag+level) += 1; //step
        } else {
            level++;
        }

    } ;
    free(tag);
}


int
main(int argc, char *argv[]) {
    int n ;
    do {
        scanf("%d", &n);
        if(n < 1 || n>= MAX_STAK_NUM) break;

        for(int i=0; i<n; ++i) input[i] = i+1;
        pcount = rcount = 0;
        permutation(n);
        printf("pcount=%d rcount=%d percent=%.2lf\n", pcount, rcount, rcount*1.0/pcount);
    } while(1);

    return 0;
}

