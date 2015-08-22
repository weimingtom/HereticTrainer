

#ifndef __LIVEDETAILSSCENE_SCENE_H__
#define __LIVEDETAILSSCENE_SCENE_H__
#include "cocos2d.h"
#include"LLPMediator.h"
USING_NS_CC;
/*
live详情界面，显示live的详细信息，可以查看评论（8/22前未实现），进入游戏，设置游戏模式等。
createScene(LiveDetails _liveDetails)_liveDetail传递live详细信息。
*/
class LiveDetailsScene : public cocos2d::Layer
{
public:
	static  LiveDetailsScene* create(LiveDetails _liveDetails);
	static Scene* createScene(LiveDetails _liveDetails);
	virtual bool init(LiveDetails _liveDetails);
private:
	LiveDetails liveDetails;
};

#endif // __HELLOWORLD_SCENE_H__


