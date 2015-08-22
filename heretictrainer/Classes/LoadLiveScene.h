

#ifndef __LOADLIVESCENE_SCENE_H__
#define __LOADLIVESCENE_SCENE_H__
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"LLPMediator.h"
USING_NS_CC;
/*
live加载界面，加载live的背景音乐，谱面数据，背景图片，如果加载失败则返回
*/
class LoadLiveScene : public cocos2d::Layer
{
public:
	static  LoadLiveScene*  create(LiveDetails _liveDetails);
	static Scene* createScene(LiveDetails _liveDetails);
	virtual bool init(LiveDetails _liveDetails);
	
private:
	LiveDetails liveDetails;
	LLPMediator* llp;
	ui::LoadingBar* lodingBar;
};

#endif // __HELLOWORLD_SCENE_H__


