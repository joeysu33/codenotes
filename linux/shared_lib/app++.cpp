#include <iostream>
#include <cstdio>
extern "C"{
#include "testlib.h"
}

using namespace std;

int main() {
    fprintf(stdout, "add(10,20)=%d\n",add(10,20));
    return 0;
}
