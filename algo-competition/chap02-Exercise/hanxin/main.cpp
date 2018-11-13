/*
 * 韩信点兵,先后三人一排， 五人一排，七人一排地变换队形，
 * 每组数据包含3个非负数，根据
 * 三人一排 尾数 a
 * 五人一排 尾数 b
 * 七人一排 尾数 c
 * a<3 b<5 c<7
 *
 * 输入:
 * 2 1 6
 * 2 1 3
 * 输出:
 * Case 1:41
 * Case 2:No answer
 *
 * 已知总人数>=10,不超过100, <=100
 */
#include <iostream>

using namespace std;

int main()
{
    int a, b, c, cnt, no;
    no = 0;
    bool ok ;
    do {
       cnt = scanf("%d%d%d", &a, &b, &c);
       if(cnt != 3) break;
       if(a >= 3 || b>=5 || c>=7) break;

       ok = false;
       for(int i=10; i<=100; i++) {
           if(i % 3 == a &&
                   i % 5 == b &&
                   i % 7 == c) {
               printf("Case %d:%d\n", ++no, i);
               ok = true;
               break;
           }
       }

       if(!ok) printf("No anwser.\n");
    } while(true);
    return 0;
}
