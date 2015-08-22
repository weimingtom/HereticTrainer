#ifndef __LOGINSCENE_SCENE_H__
#define __LOGINSCENE_SCENE_H__
/*
实现登陆界面
createScene 创建场景 isStartMode参数决定是否显示启动动画。。

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

