/*!
 * 函数指针
 * 系统调用signal的函数原型
 * void (*signal(int sig, void(*handler)(int))) (int);
 *
 * 等价于
 * typedef void (*handler_t)(int sig) ;
 * handler_t signal(int sig, handler_t handle);
 */

#include <stdio.h>
#include <stdlib.h>

typedef void (*handler_t)(int sig) ;

//void (*signal(int sig, void(*handler)(int))) (int) {
void (*signal(int sig, void (*handle)(int))) (int){
    handler_t h;
    printf("signal=%d\n", sig);
    return h;
}

/*!
 * 左边的int 作为返回函数的返回值
 * 最右边的(int x, int y) 作为返回值函数的参数
 * 第一部分：描述返回值 int
 * 第二部分描述函数: *getfunc(),特别注意如果返回一个函数指针则函数名前面有"*"
 * 第三部分描述返回函数的参数: (int x, int y)
 * 第一部分和第三部分组合成返回函数的原型
 *
 * 如果将第二部分改为*getfunc，则变成了后面携带的
 * 第三部分(int x, int y)，归类到getfunc上，成为
 * 该函数的参数
 */
int (*getfunc()) (int x, int y) {
    int (*p)(int, int);
    p = NULL;
    return p;
}

int getfunc2(int x, int y) {
    return (x+y);
}

int
main() {
    /*!函数声明必须用括号标识
     * int (*func) (int,int)
     * 否则会识别有误,认为是int*
     */
    int (*func)(int, int) ;
    int func2;
    signal(10, NULL);
    func = getfunc();
    func2 = getfunc2(10,20);
    printf("func=%p, func2=%d\n", func, func2);
    return 0;
}


