#ifndef __LOADINGLAYER_LAYER_H_
#define __LOADINGLAYER_LAYER_H_
#include"cocos2d.h"
USING_NS_CC;
/*
���ض������棬���δ����¼�������Ч��������ô�á�����
*/
class LoadingLayer :public Layer
{
public:
	static LoadingLayer* create();
	bool init();
};
#endif