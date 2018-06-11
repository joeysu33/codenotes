#include <stdio.h>

int 
main() {
    extern void xyz(void) ; //函数声明，也可以写在上面
    xyz();

    return 0;
}
