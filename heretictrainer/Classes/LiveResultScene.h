#ifndef __LIVERESULTSCENE_SCENE_H__
#define __LIVERESULTSCENE_SCENE_H__
#include "cocos2d.h"
#include"LiveInfo.h"
USING_NS_CC;
/*
live结算界面，支持重新开始操作。。

*/
class LiveResultScene : public cocos2d::Layer
{
public:
	//我不信你看不懂参数，rank是评价等级，S那些
	static LiveResultScene* create(LiveInfo liveInfo,int perfectCount,int greatCount,int goodCount,int badCount,int missCount,int comboCount,int mcomboCount,int score,std::string rank);
	static Scene* createScene(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank);
	virtual bool init(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank);

};

#endif // __HELLOWORLD_SCENE_H__
