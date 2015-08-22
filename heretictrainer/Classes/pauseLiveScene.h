#ifndef __PAUSELIVESCENE_SCENE_H__
#define __PAUSELIVESCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
/*
暂停游戏。。。
PauseLiveScene::create(Texture2D* texture)传递一个纹理作为背景，一般是当前游戏的截图，这样看起来像是暂停了
*/
class PauseLiveScene : public cocos2d::Layer
{
public:
	static PauseLiveScene*create(Texture2D* texture);
	static Scene* createScene(Texture2D* texture);
	virtual bool init(Texture2D* texture);

};

#endif // __HELLOWORLD_SCENE_H__
