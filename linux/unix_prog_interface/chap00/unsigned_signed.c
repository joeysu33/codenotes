/*!
 * 1.unsigned的数值和signed的数值进行比较，则按照unsigend的方式来进行比较
 *   signed i=10; unsigned j=-10; i<j
 * 2.double和unsigned比较
 *   double i=10; unsigned j=-10; i<j;
 * 3.float和double一定都是有符号的数值
 */
#include <stdio.h>


#define PRINT(...) \
    do {printf(__VA_ARGS__); printf("\n"); }while(0)

int 
main() {
    double i=10;
    unsigned j=-10;
    if(i > j) {
        PRINT("i>j");
    } else {
        PRINT("i<=j");
    }
    return 0;
}

