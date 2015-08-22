

#ifndef __LIVEDETAILSSCENE_SCENE_H__
#define __LIVEDETAILSSCENE_SCENE_H__
#include "cocos2d.h"
#include"LLPMediator.h"
USING_NS_CC;
/*
live������棬��ʾlive����ϸ��Ϣ�����Բ鿴���ۣ�8/22ǰδʵ�֣���������Ϸ��������Ϸģʽ�ȡ�
createScene(LiveDetails _liveDetails)_liveDetail����live��ϸ��Ϣ��
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


