#ifndef __LOADINGLAYER_LAYER_H_
#define __LOADINGLAYER_LAYER_H_
#include"cocos2d.h"
USING_NS_CC;
/*
加载动画界面，屏蔽触摸事件，但是效果好像不怎么好。。。
*/
class LoadingLayer :public Layer
{
public:
	static LoadingLayer* create();
	bool init();
};
#endif