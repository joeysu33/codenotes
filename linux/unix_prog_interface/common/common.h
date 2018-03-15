#if !defined(_COMMON_INCLUDED_H)
#define _COMMON_INCLUDED_H

#include <stdio.h>

#if !defined(bool)
#define bool unsigned char
#endif

#if !defined(true)
#define true 1
#endif 

#if !defined(false)
#define false 0
#endif

#if !defined(MAX_PATH)
#define MAX_PATH 254
#endif

void err_exit(const char* msg,...);

#endif 
