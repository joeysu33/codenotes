/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

/******************************************************************************************
* 将BST各方法的实现部分，简洁地引入BST.h
* 效果等同于将这些实现直接汇入BST.h
* 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
******************************************************************************************/
#include "redblack_insert.h" //插入
#include "redblack_remove.h" //删除
#include "redblack_updateheight.h" //更新高度
#include "redblack_solvedoublered.h" //双红修正
#include "redblack_solvedoubleblack.h" //双黑修正
