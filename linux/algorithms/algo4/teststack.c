/*!
 * 测试stack数据结构
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define ETYPE int
#include "stack.h"


int
main(int argc, char *argv[]) {
    int i, j;
    Stack s1 = makeS(3), *s = &s1;

    assert(emptyS(s));
    pushS(s, 10);
    pushS(s, 20);
    pushS(s, -5);
    assert(fullS(s));

    assert(sizeS(s) == 3);
    i = popS(s);
    assert(i == -5);
    i = popS(s);
    assert(i == 20);

    pushS(s, 100);
    assert(sizeS(s) == 2);
    assert(topS(s) == 100);

    assert(popS(s) == 100);
    assert(popS(s) == 10);
    assert(sizeS(s) == 0);
    assert(emptyS(s));

    freeS(s);
    return 0;
}

