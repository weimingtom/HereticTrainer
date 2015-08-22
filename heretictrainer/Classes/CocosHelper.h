#ifndef __COCOSHELPER_VIEW_H_
#define __COCOSHELPER_VIEW_H_
#include"cocos2d.h"
USING_NS_CC;
/*
实现一些帮助函数，帮助cocos的运行
*/
//DFS过程。搜索root以及子节点，返回符合名称的node。
Node* seekNodeByName(Node* root, const std::string& name);
#endif