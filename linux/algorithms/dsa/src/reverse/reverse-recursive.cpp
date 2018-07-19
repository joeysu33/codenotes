/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/*DSA*/#include "../_share/util.h"
/*DSA*/#include "../UniPrint/print_int_array.h"

void reverse ( int* A, int lo, int hi ) { //数组倒置（多递归基递归版）
   if ( lo < hi ) {
      swap ( A[lo], A[hi] ); //交换A[lo]和A[hi]
      reverse ( A, lo + 1, hi - 1 ); //递归倒置A(lo, hi)
   } //else隐含了两种递归基
} //O(hi - lo + 1)