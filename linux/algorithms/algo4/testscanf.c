#include "common.h"

void
match(const char *cp1) {
    char c= 0, k=0;
    int j = 0;
    printf("cp1 = %s\n", cp1);
    sscanf(cp1, "%*[^a-zA-Z0-9]%c%*[^a-zA-Z0-9]%c%d", &c, &k, &j);
    printf("c=%c k=%c j=%d\n", c, k, j);
    printf("\n");
}

int 
main(int argc, char *argv[]) {
    const char *cp1 = " \ta b\t\t\t\t10000 ";
    const char *cp2 = "a b d\n";
    match(cp1);
    match(cp2);
    match("a b 100");
    return 0;
}
