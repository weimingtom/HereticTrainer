
#ifndef __ABOUTSCENE_SCENE_H__
#define __ABOUTSCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
/*
¹ØÓÚ Ò³Ãæ
*/
class AboutScene : public cocos2d::Layer
{
public:
	static AboutScene* create();
	static Scene* createScene();
	virtual bool init();

};

#endif // __HELLOWORLD_SCENE_H__