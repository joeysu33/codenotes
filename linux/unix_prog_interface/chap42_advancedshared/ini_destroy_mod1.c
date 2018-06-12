#include <stdio.h>

/*!模块初始化函数*/
void __attribute__((constructor))
module_init() {
    printf("module_init()\n");
}

void __attribute__((destructor))
module_destroy() {
    printf("module_destroy()\n");
}


/*!模块卸载函数*/

void m1() {
    printf("mod1::m1() called.\n");
}
