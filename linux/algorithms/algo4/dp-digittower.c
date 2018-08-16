/*!
 * DP算法：数塔问题, DP算法只能得到一个最优解
 * 使用数字来构建一座塔，要求从顶层走到底层，每一步
 * 只能走到相邻的节点，则经过的节点的数字之和最大(小)是多少？
 *
 *                 8
 *                / \
 *               12  15
 *              /  \/ \
 *             10  6   8
 *            / \ / \ / \
 *           2  18   9   5
 *          / \ / \ / \ / \
 *         19  7  10   4  16
 *
 *
 * 个数 2^5 -1 = 31个数值
 * 塔的高度不超过100层, 其中第i行有i个元素
 * 如果单纯从树遍历到叶子节点的话，可以求解出最佳值，问题是
 * 2^100次方就很吓人了...?????????^@^
 * 
 * DP问题的解题思路（算法导论）
 * 1.刻画一个最优解的结构特征
 * 2.递归的定义最优解的值。
 * 3.计算最优解的值，通常采用自底向上的方法。
 * 4.利用计算出的信息构造一个最优解
 *
 * 解题思路
 * 1.最优解的特征：各节点的最大数字之和最大
 * 2.节点的最优解等于该节点的值，加上其两个节点的最大值
 * 3.自底向上的求解(非常重要）
 * 4.要不断缩小问题域的规模
 *
 * |-------------------------------------------------------|
 * 如果自顶向下的话，随着节点数的增多，问题的规模不断扩大  |
 * 而自底向上的话，问题规模在逐步缩小，最底层的最大值很容易|
 * 确定。                                                  |
 * |-------------------------------------------------------|
 *
 * 状态转义方程，从最后一层开始，逐渐缩小
 * f[i][j] = f[i+1][j-1] + f[i+1][j];
 *
 */

#include "common.h"

#define NMAX 120 //i不超过100
#define NVAL 16

int
main(int argc, char *argv[]) {
    int i, j, k, n, a[NMAX][NMAX], b[NMAX][NMAX], st; //a表示原始数据，b表示更新后的统计值

    printf("Enter levels of numbers:");
    fflush(stdout);
    scanf("%d", &n);

    if(n < 1) return 1; 

    for(i=0; i<n; ++i) 
        for(j=0; j<n; ++j)
            a[i][j] = b[i][j] = -1;

    //一行表示一个数据
    i=0; //数据所在的行索引
    j=0; //数据所在的列索引
    k=0; //数据
    st = 0; //找到第一个有效数据后开始工作
    char c, *cp, val[NVAL];

    while( (c = fgetc(stdin)) != EOF) {
        if(isdigit(c)) {
            st = 1;
            val[k++] = c;
            if(j > NVAL-1) { printf("So long number!\n");assert(false); exit(1); }
        } else if(c == '\n' && st > 0) {
            val[k] = 0;
            a[i][j] = b[i][j] = strtol(val, &cp, 0);
            assert(a[i][j] > 0);
            k=0;
            i++;
            j=0;
        } else if(isblank(c) && st > 0) {
            val[k] = 0;
            a[i][j] = b[i][j] = strtol(val, &cp, 0);
            assert(a[i][j] > 0);
            j++;
            k=0; //重新开始计数
        } else {
            //忽略掉
        }
    }

    for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j) 
            printf("%-4d ", a[i][j]);
        printf("\n");
    }

    //从倒数第二行开始进行计算
    int q[NMAX], qc = 0, levlMax = -INT_MAX, idx[2];
    for(i=n-2; i>=0; --i) {
        //一旦遇到小于0则停止计算
        for(j=0; j<n && b[i][j] >= 0; ++j) {
            k = b[i+1][j] > b[i+1][j+1] ? j : j+1;
            b[i][j] += b[i+1][k];

            //找出下层的最大值的索引位置
            /*if(levlMax < b[i+1][k]) {
                idx = k;
                levlMax = a[i+1][k];
            }*/ //不是局部最优
        }

        //stk[++top] = levlMax;
    }

    //从置好的表中可以得到寻走顺序
    for(i=0; i<n; ++i) {
        levlMax = -INT_MAX;
        idx[0] = idx[1] = -1;
        for(j=0; j<n && b[i][j] >= 0; ++j) {
            if(b[i][j] > levlMax) {
                idx[0] = i;
                idx[1] = j;
                levlMax = b[i][j];
            }
        }
        q[qc++] = a[idx[0]][idx[1]];
    }

    printf("Result:");
    for(i = 0; i < qc; ) {
        printf("%-4d ", q[i++]);
    }
    printf("\n");
    printf("Maximum value of digit tower =%d\n", b[0][0]);

    return 0;
}



