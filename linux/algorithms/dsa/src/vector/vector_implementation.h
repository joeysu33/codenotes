/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

/******************************************************************************************
 * 将vector各方法的实现部分，简洁地引入vector.h
 * 效果等同于将这些实现直接汇入vector.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "../_share/release.h"
#include "../_share/util.h"

#include "vector_bracket.h"
#include "vector_assignment.h"

#include "vector_constructor_by_copying.h"

#include "vector_expand.h"
#include "vector_shrink.h"

#include "vector_insert.h"
#include "vector_remove.h"
#include "vector_removeinterval.h"

#include "vector_disordered.h"
#include "vector_find.h"
#include "vector_search.h"
#include "vector_search_binary_c.h" //有a、b、c三种版本，c最完善
#include "vector_search_fibonaccian_b.h" //有a、b两种版本，b虽华丽，a更实用（但返回值有待与接口统一）

#include "vector_traverse.h"

#include "vector_unsort.h"
#include "vector_sort.h"
#include "vector_bubble.h"
#include "vector_bubblesort.h"
#include "vector_selectionsort.h"
#include "vector_merge.h"
#include "vector_mergesort.h"
#include "vector_partition_b.h" //有a、a1、b、b1、c共5个版本
#include "vector_quicksort.h"
#include "vector_heapsort.h"

#include "vector_uniquify.h" //或者vector_uniquify_slow.h
#include "vector_deduplicate.h"
