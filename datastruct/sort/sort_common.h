#if !defined(_SORT_COMMON_INCLUDED_H)
#define _SORT_COMMON_INCLUDED_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned char bool;
#define true  1
#define false 0

void show(int *arr, int length);
void init(int *arr, int length);
void init_random(int *arr, int length);
void init_left_sorted(int *arr, int length);
void init_right_sorted(int *arr, int length);

#endif
