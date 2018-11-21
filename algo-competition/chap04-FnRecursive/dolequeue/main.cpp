/*!
  dole 救济金发放
  n(n<20)个人站成一圈，逆时针编号为1~n,有两个官员，A从1开始逆时针数，
  B从n开始顺时针数。在每一轮中，官员A数k个就停下来，官员B数m个就停下来。
  （可能两个官员停在同一个人身上）。接着被选中的人（可能一个人，也可能
  两个人）离开队伍

  分析：这种题规模下，而且和1~N，对应可以考虑直接跳过0索引进行存储，便于对应，以免出错
  输入n, k, m，输出离开队伍的数据
  例如n=10, k=4, m=3
  输出 4 8,9 5,3 1,2 6,10, 7 (每个输出占三列)
*/
#include <iostream>
#include <memory>

using namespace std;

#define N 100

static unsigned char dole[N];
static int n, k, m;

int main()
{
    do {
        if(scanf("%d%d%d", &n, &k, &m) != 3) return 0;
        if(n <= 0) break;
        for(int i=0; i<n; ++i) dole[i] = 0;

        int ia=0, ib=n-1;
        int left= n;
        while(left > 0) {
            for(int j=0; ; ia++) { //这里ia++会多执行一次
                ia %= n;
                if(dole[ia]) continue;
                ++j;
                if(j == k) break;
            }

            for(int j=0; ;--ib) {
                if(ib < 0) ib += n; //ib == -1
                if(dole[ib]) continue;
                ++j;
                if(j == m) break; //避免--ib多执行一次
            }

            if(ia == ib) {
                --left;
                printf("%-3d%s", ia+1, left ? "," : ""); //避免打印最后一个,
                dole[ia]=1;
            } else {
                left -= 2;
                printf("%-3d%-3d%s", ia+1, ib+1, left ? "," : ""); //避免打印最后一个,
                dole[ia]=dole[ib]=1;
            }
        }
        printf("\n");
    } while(true);

    return 0;
}
