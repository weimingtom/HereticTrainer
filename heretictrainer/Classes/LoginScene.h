#ifndef __LOGINSCENE_SCENE_H__
#define __LOGINSCENE_SCENE_H__
/*
ʵ�ֵ�½����
createScene �������� isStartMode���������Ƿ���ʾ������������

*/
#include "cocos2d.h"
USING_NS_CC;
class LoginScene : public cocos2d::Layer
{
public:
	static LoginScene* create(bool isStartMode);
	static Scene* createScene(bool isStartMode);
	virtual bool init(bool isStartMode);

};

#endif // __HELLOWORLD_SCENE_H__

