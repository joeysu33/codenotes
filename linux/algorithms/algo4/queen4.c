/*!
 * 四皇后问题,在4*4的网格中
 * 构建四个皇后，且互相不攻击
 * 同理，可以构建8皇后问题
 * 采用回溯法
 *
 * 回溯法的几个要素
 * 1.递归或堆栈来实现
 * 2.存在循环（每层循环的个数对应的是分支的个数)
 * 3.存在判断（剪枝），成立的继续深度递归，不成立的不再深度递归
 * 4.明确程序的入口和出口
 */ 

#include <stdio.h>
#include <assert.h>

#define N 10
//#define STEP

#if !defined(true)
#define true  1
#endif

#if !defined(false)
#define false 0
#endif

typedef unsigned char bool;


typedef struct _Position {
    int m_x;
    int m_y;
} Position, *PPosition;

static Position q[N];

bool conflict(Position *a, Position *b) {
    if(!a || !b) return false;
    if(a->m_x >= N || b->m_x >= N) {
        printf("Error ocurr!\n");
        return true;
    }
    if(a->m_x == b->m_x || a->m_y == b->m_y ||
            (a->m_x + a->m_y ==  b->m_x + b->m_y) ||
            (a->m_x - a->m_y ==  b->m_x - b->m_y))
        return true;
    //问题1:没有写入返回值
    return false;
}

void showPlace() {
    int i,j;
    char c;
    static int k = 0;
    printf("--------count:%d-----------\n", ++k);
    for(i=N-1; i>=0; --i) {
        for(j=0; j<N; ++j) {
            if(j == q[i].m_x) {
                c = '@';
            } else c = '*';
            printf("%-2c", c);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

#if defined(STEP)
    getchar();
#endif
}

bool canPlace(int queenIndex) {
    if(queenIndex >= N) return false;
    if(queenIndex <= 0) return true;

    Position *cur = &q[queenIndex];
    for(int i=queenIndex-1; i>=0; --i) {
        if(conflict(&q[i], cur)) return false;
    }
    return true;
}

int
main(int argc, char *argv[]) {
    int i, stk;

    for(i=0; i<N; ++i) {
        q[i].m_x = 0;
        q[i].m_y = i;
    }

    int cnt=0;
    bool ok = false;
    stk = 0;
    while(true) {
        if(stk == N) { showPlace(); cnt++; q[--stk].m_x++; }
        if(stk < 0) { break; }

        ok = false;
        for(q[stk].m_x; q[stk].m_x<N; q[stk].m_x++) {
            //step forward
            if(canPlace(stk)) {
                ok = true;
                break;
            } 
        }
        
        //step backward
        if(!ok) {
            //恢复上次的数据
            q[stk].m_x = 0;
            stk--;
            //将起始位置右移，如果溢出N则ok = false
            if(stk >= 0)
                q[stk].m_x++;
        } else {
            stk++;
        }
    }

    printf("count=%d\n", cnt);
    return 0;
}


