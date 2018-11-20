/*!
  计算分子的质量
  分子式包含4种原子，原子量C, H, O, N分别是
  12.01 1.008 16.00 14.01 g/mol。例如C6H5OH的分子量是94.108g/mol
*/
#include <iostream>
#include <ctype.h>
#include <cstdlib>

using namespace std;

#define MAX_LEN 1000

double molarMass(const char *s) {
    if(!s) return 0;
    int chon[4];
    char buf[16];
    double mass[] = {12.01, 1.008, 16.0, 14.01};
    memset(chon, 0, sizeof(chon));

    int i;
    char *cp;
    for(; *s; ) {
        switch(*s) {
        case 'C': i=0; break;
        case 'H': i=1; break;
        case 'O': i=2; break;
        case 'N': i=3; break;
        }

        int k=0;
        const char *j;
        for(j=s+1; *j && isdigit(*j) && k<16; ++j) buf[k++]=*j;

        if(k == 0) {
            chon[i]++;
            s++;
        } else {
            buf[k] = 0;
            chon[i] += strtol(buf, &cp, 0);
            s = j;
        }
    }

    double rMass = 0;
    for(int j=0; j<4; ++j) {
        rMass += chon[j] * mass[j];
    }

    return rMass;
}

int main()
{
    char str[MAX_LEN];
    scanf("%s", str);
    printf("%lf", molarMass(str));

    return 0;
}
