



#ifndef __LOCALSCENE_SCENE_H__
#define __LOCALSCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class LocalScene : public cocos2d::Layer
{
public:
	static LocalScene*create();
	static Scene* createScene();
	virtual bool init();

};

#endif // __HELLOWORLD_SCENE_H__



