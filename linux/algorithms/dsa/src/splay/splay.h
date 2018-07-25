/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "../bst/bst.h" //基于bst实现splay
template <typename T> class Splay : public BST<T> { //由BST派生的Splay树模板类
protected:
   BinNodePosi(T) splay ( BinNodePosi(T) v ); //将节点v伸展至根
public:
   BinNodePosi(T) & search ( const T& e ); //查找（重写）
   BinNodePosi(T) insert ( const T& e ); //插入（重写）
   bool remove ( const T& e ); //删除（重写）
};

#include "splay_implementation.h"
