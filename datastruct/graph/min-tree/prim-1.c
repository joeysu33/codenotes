/*!
 * 普里姆算法(Prim)
 * 又称为“加点法”，每次迭代选择代价最小的边对应的点，加入到最小生成树中。
 * 算法从某一个顶点s开始，逐渐长大覆盖整个连通网的所有顶点。
 * 1.图的所有顶点集合V；初始令集合u={s},v=V-u
 * 2.在两个集合u，v能够组成的边中，选择一条代价最小的边（u0,v0),加入到最小生成树中，
 *   并把v0并入到集合u中。
 * 3.重复上述步骤，直到最小生成树有n-1条边或者n个顶点为止
 *
 * 使用稀疏矩阵来描述无向图
 */

