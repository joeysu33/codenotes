/*!
 * 进栈和出栈顺序
 * 问：有1,2,3...n个数，出栈的顺序有多少种, 并输出所有顺序
 * 这里可以用到卡特兰数
 * Catalan = (2n)!/(n+1)!n!
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100
#define STEP

static int inStk[MAX_NUM], outStk[MAX_NUM];
static int inTop, outTop;

typedef enum _StkOper {
    NotOutStack,
    OutStack,
    MaxOper,
} StkOper;

void
showStk(int *stk, int top) {
    if(!stk || top < 0) return ;

    printf("[ ");
    for(int i=0; i<=top; ++i)
        printf("%-2d, ", stk[i]);
    printf(" >\n");
}

void
showOutStk() {
    showStk(outStk, outTop);
}

void
showInStk() {
    showStk(inStk, inTop);
}

void
showStkAll() {
    printf("in:");
    showInStk();
    printf("out:");
    showOutStk();
    fflush(stdout);

#if defined(STEP)
    getchar();
#endif
}

void
dumpInStk() {
    while(inTop >= 0) {
        outStk[++outTop] = inStk[inTop--];
    }
}

int
inStkEmpty() {
    return inTop == -1;
}

int
outStkEmpty() {
    return outTop == -1;
}

void
dumpInStk1() {
    if(inStkEmpty()) return ;
    outStk[++outTop] = inStk[inTop--];
}

void
emptyInStk() {
    inTop = -1;
}

void
emptyOutStk() {
    outTop = -1;
}

/*
//递归算法
void
catalan(int *nums, int cnt) {
    //递归基
    if(cnt == 0) {
        dumpInStk();
        showOutStk();
    }

    if(cnt <= 0) return ;

    //每个元素有两种操作方式，入栈，出栈
    inStk[++inTop] = nums[0];

    //不出栈递归
    catalan(nums+1, cnt-1);

    
    //出栈递归
    dumpInStk1();
    catalan(nums+1, cnt-1);
}
*/

//递归算法
void
catalan(int *nums, int cnt, const int number, int in, int out) {
   if(cnt == 0 && out == number) {
        showOutStk();
        return ;
   } 
   if(cnt < 0) return ;

   showStkAll();

   //case1.nums -> in
   inStk[in] = nums[0];
   catalan(nums+1, cnt-1, number, in+1, out);

   //case2.in -> out
   outStk[out] = inStk[in];
   catalan(nums, cnt, number, in - 1, out+1 );

   //不出栈递归, 这里数据不应该一直增加
   //inTop = number-cnt; 
   //inStk[inTop] = nums[0];
   //catalan(nums+1, cnt-1, number);
   
   //出栈递归
   //outStk[++outTop] = inStk[inTop--];
   //catalan(nums+1, cnt-1, number);
   //inStk[++inTop] = outStk[outTop--];
}

/*!
 * 非递归算法, 回溯法, 层数等于cnt,
 * 每层的处理有多种方式
 * 1.从nums -> instack
 * 2.从instack -> outstack (1~N)
 * 3.1和2是互斥的
 * 4.退出条件?
*/

typedef enum _StateOperType {
   SOT_ToInStk,
   SOT_ToOutStk,
   SOT_None,
} StateOperType;

typedef struct  _StateOper {
    StateOperType otype;
    int outStkCnt;
} StateOper;

typedef struct _State {
    int inStack[MAX_NUM];
    int outStack[MAX_NUM];
    int inS, outS, inputCnt;
    int *input;
    StateOper oper;
} State;

void
catalan2(int *nums, int cnt) {
    State s;

    //栈内数据个数，栈顶inS -1, 或outS-1
    //s.inS + s.outS + inputCnt == cnt
    s.inS = s.outS = 0;
    s.input = nums;
    s.inputCnt = cnt;

    s.oper.otype = SOT_ToInStk;
    s.oper.outStkCnt = 0;

    do {
        if(s.inputCnt == cnt && s.oper.otype == SOT_None) break;
        switch(s.oper.otype) {
            case SOT_ToInStk: {
                                  break;
                              }
            case SOT_ToOutStk: {
                                   break;
                               }
        }
    } while(1);
}

int
main(int argc, char *argv[]) {
    int num, nums[MAX_NUM];
    do {
        scanf("%d", &num);
        if(num <= 0 || num >= MAX_NUM) break;
        for(int i=0; i<num; ++i) {
            scanf("%d", &nums[i]);
        }

        inTop = outTop = -1;
        catalan(nums, num, num,0, 0);
    } while(1);
    return 0;
}




