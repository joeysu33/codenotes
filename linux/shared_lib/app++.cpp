#include <iostream>
#include <cstdio>

//必须要加上extern "C"，
//因为c++中是允许函数重载的，存在同名机制
//加上extern "C"之后就不会涉及到改名，这样不会链接错误
extern "C"{
#include "testlib.h"
}

using namespace std;

int main() {
    fprintf(stdout, "add(10,20)=%d\n",add(10,20));
    return 0;
}
