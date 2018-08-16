#if !defined(_COMMON_INCLUDED_H)
#define _COMMON_INCLUDED_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <memory.h>

typedef unsigned char bool;

#if !defined(true)
#define true 1
#endif

#if !defined(false)
#define false 0
#endif

int cmax(int a, int b) { return  a > b ? a : b; }
int cmin(int a, int b) { return  a < b ? a : b; }


#endif //_COMMON_INCLUDED_H
