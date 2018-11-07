/*!
 * 四皇后问题,在4*4的网格中
 * 构建四个皇后，且互相不攻击
 * 同理，可以构建8皇后问题
 * 采用回溯法
 */ 

#include <stdio.h>

#define N 8

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
    for(i=N-1; i>=0; --i) {
        for(j=0; j<N; ++j) {
            if(j == q[i].m_x) {
                c = '@';
            } else c = '*';
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
    //getchar();
}

int
main(int argc, char *argv[]) {
    int i, j,k, stk;

    for(i=0; i<N; ++i) {
        q[i].m_x = 0;
        q[i].m_y = i;
    }

    //入栈第一个皇后
    stk = 0; //当前位置
    showPlace();

    bool s2 = false, s1 = false;
    int cnt=0;
    while(true){
        i = stk+1; //下一个要放的棋子

        s1 = true;
        for(; q[i].m_x<N && q[stk].m_x<N; ++q[i].m_x) {
            s1 = false;
            for(k=0; k<=stk; ++k) {
                if(conflict(&q[i], &q[k])) {
                    s1 = true;
                    break;
                }
            }
            if(!s1) break;
        }

        if(s1) {
            //回溯到上一个位置，出栈
            q[i].m_x = 0;
            //逐步一直进行回溯,直到q[stk].m_x != N-1,但是不能回溯到根上
            //问题2:没有设置终止条件 stk != 0
            /*while(q[stk].m_x == N-1 && stk != 0) {
                q[stk].m_x = 0;

                stk--;
                if(stk < 0) {
                    s2 = 1; //栈空,Error
                    break;
                } 
            } */

            //问题3:增加终止条件
            if(stk == 0 && q[stk].m_x == N-1) { s2 = 0; printf("finished"); break; }

            //对于已经发生移动的皇后，需要重新进行调整校验
            q[stk].m_x++;
            if(stk > 0) stk--; 
        } else {
            //满足条件的皇后布局
            if(i == N-1) {
                printf("-----case:%d-------\n", ++cnt);
                showPlace();
                q[i].m_x++;
            } else {
                stk++;
            }
        }
    }

    if(s2) 
        printf("Not Found!\n");

    return 0;
}






