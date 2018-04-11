/*!
 * 宏定义变参 __VA_ARGS__
 * 变参取值
 * va_list
 * va_start
 * va_arg
 * va_end
 */

#include <stdio.h>

//特别需要注意的是__VA_ARGS__前面的两个#，是为了消除
//当showMsg只有一个参数的时候，会消去前面的逗号
#define showMsg(msg, ...) \
    printf(msg, ##__VA_ARGS__);

int 
main(int argc, char* argv[]) {
    showMsg("Hi");
    showMsg("there 's %s", "big mouse");
    return 0;
}

