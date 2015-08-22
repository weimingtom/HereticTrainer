
#ifndef __USERSCENE_SCENE_H__
#define __USERSCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class UserScene : public cocos2d::Layer
{
public:
	static UserScene* create();
	static Scene* createScene();
	virtual bool init();

};

#endif // __HELLOWORLD_SCENE_H__



