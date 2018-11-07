/*!
 * 采用递归的解法来求N皇后问题
 */
#include <stdio.h>

#define N 4

void showPlace(int *stk, int top) {
    int i, j;
    char c;
    for(i=top; i>=0; --i) {
        for(j=0; j<N;++j){
            if(stk[i] == j) c = '@';
            else c = '*';
            printf("%-2c", c);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
}

int hasConflict(int *stk, int top) {
    int i, j,k;
    //只有一个元素，不存在冲突
    if(top == 0) return 0;

    int newval = stk[top];
    j = top;
    for(i=0; i<=top-1; ++i) {
        //不肯能出现在同一行 i==j可以忽略
        if(i == j || stk[i] == newval ||
                (i + stk[i] == j + newval) ||
                (i - stk[i] == j - newval)) {
            return 1;
        }
    }

    return 0;
}

//给皇后找一个合适的位置
int placeQueue(int *stk, int top, int* solveCnt) {
    int i;
    if(!stk || !solveCnt) return 1;

    if(!hasConflict(stk, top) && (top == N-1)) {
        showPlace(stk, top);
        solveCnt++;
        return 0;
    }

    for(i=0; i<N; ++i) {
        stk[top+1]++;
        if(!placeQueue(stk, top+1, solveCnt)) return 0; 
    }

    return 1;
}

int
main(int argc, char *argv[]) {
    int stk[N], top, cnt, i;
    top = -1;
    cnt = 0;

    for(i=0; i<N; ++i) {
        stk[i] = 0;
    }
    
    showPlace(stk, 3);
    for(int i=0; i<N; ++i) {
        stk[i] = i;
        //入栈第一个皇后
        placeQueue(stk, 0, &cnt);
    }

    return 0;
}



