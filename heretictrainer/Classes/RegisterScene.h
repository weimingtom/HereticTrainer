#ifndef __REGISTERSCENE_SCENE_H__
#define __REGISTERSCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
/*
×¢²áÒ³Ãæ
*/
class RegisterScene : public cocos2d::Layer
{
public:
	static RegisterScene* create();
	static Scene* createScene();
	virtual bool init();

};

#endif // __HELLOWORLD_SCENE_H__


