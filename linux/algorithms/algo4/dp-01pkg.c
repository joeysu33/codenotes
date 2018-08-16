/*!
 * DP算法(Dynamic Planning|Programming)主要是将问题转换成DAG
 * (Directed Acylic Graph)有向无环图。并辅以存储来缓存子问题
 * 的结果来达到动态规划的效果
 *
 * 01背包问题，有m种的物品，每个物品仅一个，每个物品的重量是w[i], 价值是p[i],
 * 现在背包的容量是C，问应该如何选择物品能达到最大价值(总体最优)。
 * 状态转换方程
 * f[i][j] = max { f[i-1][j], f[i-1][j-w[i]] + p[i] };
 * f[i][j] 表示第i种物品加入后，剩余重量j
 * f[i-1][j] 表示如果不放入第i种物品，则最大价值
 * f[i-1][j-w[i]] + p[i] 表示放入第i种物品，则最大价值
 */

#include "common.h"

int
main(int argc, char *argv[]) {
    return 0;
}
