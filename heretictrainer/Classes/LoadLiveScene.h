

#ifndef __LOADLIVESCENE_SCENE_H__
#define __LOADLIVESCENE_SCENE_H__
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"LLPMediator.h"
USING_NS_CC;
/*
live���ؽ��棬����live�ı������֣��������ݣ�����ͼƬ���������ʧ���򷵻�
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


