#ifndef __PAUSELIVESCENE_SCENE_H__
#define __PAUSELIVESCENE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
/*
��ͣ��Ϸ������
PauseLiveScene::create(Texture2D* texture)����һ��������Ϊ������һ���ǵ�ǰ��Ϸ�Ľ�ͼ������������������ͣ��
*/
class PauseLiveScene : public cocos2d::Layer
{
public:
	static PauseLiveScene*create(Texture2D* texture);
	static Scene* createScene(Texture2D* texture);
	virtual bool init(Texture2D* texture);

};

#endif // __HELLOWORLD_SCENE_H__
