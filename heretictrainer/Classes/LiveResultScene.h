#ifndef __LIVERESULTSCENE_SCENE_H__
#define __LIVERESULTSCENE_SCENE_H__
#include "cocos2d.h"
#include"LiveInfo.h"
USING_NS_CC;
/*
live������棬֧�����¿�ʼ��������

*/
class LiveResultScene : public cocos2d::Layer
{
public:
	//�Ҳ����㿴����������rank�����۵ȼ���S��Щ
	static LiveResultScene* create(LiveInfo liveInfo,int perfectCount,int greatCount,int goodCount,int badCount,int missCount,int comboCount,int mcomboCount,int score,std::string rank);
	static Scene* createScene(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank);
	virtual bool init(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank);

};

#endif // __HELLOWORLD_SCENE_H__
