#include <iostream>

using namespace std;

//最大皇后数目
#define MAX_N 10000
//棋盘，一维数组
static int chess[MAX_N];

bool canPlace(const int step) {
    if(step < 1) return true;
    int j = chess[step];

    for(int i=0, k=0; i<step; ++i) {
        k = chess[i];
        if(k == j  ||
                k + i == j + step ||
                k - i  == j - step) {
            return false;
        }
    }

    return true;
}

void showChess(const int n) {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(chess[i] == j) printf("%2c", '@');
            else printf("%2c", '*');
        }
        printf("\n");
    }
    cout<<endl;
}

//递归实现N皇后
void placeQueen(int step, int *tot, const int n) {
    // 能走到第N步，说明0~N-1已经设置成功
    if(step == n) {
        showChess(n);
        *tot += 1;
        return ;
    }

    for(int i=0; i<n; ++i) {
        chess[step] =i;
        if(canPlace(step)) {
            placeQueen(step+1, tot, n);
        }
    }
}

//非递归实现回溯，N皇后问题
void placeQueenBT(int *tot, const int n) {
   int step = 0;
   *tot = 0;
   for(int i=0; i<n; ++i) chess[i] = 0;
   bool ok;
   do {
       ok = false;
       for(int i=chess[step]; i < n; ++i) {
           chess[step] = i;
           if(canPlace(step)) {
               ok = true;
               break;
           }
       }

       if(ok) {
           step++;
       } else {
           chess[step] = 0;
           --step;
           chess[step]++;
       }

       //到达回溯的终点
       if(chess[0] == n) break;

       //完成回溯
       if(step == n) {
           showChess(n);
           *tot += 1;
           //继续移动
           chess[--step]++;
       }
   } while(true);
}

int main()
{
    int tot = 0, n, cnt;
    do {
        cnt = scanf("%d", &n);
        if(cnt == 0 || n < 1 || n >= MAX_N) break;
        tot = 0;
        //placeQueen(0, &tot, n);
        placeQueenBT(&tot, n);
        printf("Queen(%d)=%d\n", n, tot);
    } while(true);

    return 0;
}

