/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

/******************************************************************************************
 * 将List各方法的实现部分，简洁地引入List.h
 * 效果等同于将这些实现直接汇入List.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "../_share/release.h"
#include "../_share/util.h"

#include "listnode.h"

#include "list_bracket.h"

#include "list_initialize.h"
#include "list_copynodes.h"
#include "list_constructor_by_copying.h"
#include "list_destructor.h"

#include "list_disordered.h"

#include "list_find.h"
#include "list_search.h"

#include "list_insert.h"
#include "list_remove.h"
#include "list_clear.h"

#include "list_traverse.h"

#include "list_sort.h"
#include "list_insertionsort.h"
#include "list_selectmax.h"
#include "list_selectionsort.h"
#include "list_merge.h"
#include "list_mergesort.h"

#include "list_deduplicate.h"
#include "list_uniquify.h"

#include "list_reverse1.h"
//#include "list_reverse2.h"
//#include "list_reverse3.h"
