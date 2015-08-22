


#include"AboutScene.h"
#include"ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include"CocosHelper.h"
using namespace ui;

AboutScene* AboutScene::create()
{

	AboutScene *pRet = new(std::nothrow)AboutScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}
Scene* AboutScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AboutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool AboutScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("aboutScene.csb");
	addChild(rootNode);
	//���ذ�ť����¼�
	((Button*)(seekNodeByName(rootNode, "button_return")))->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});
	//����llp��ť����¼�
	((Button*)(seekNodeByName(rootNode, "button_llp")))->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			//���ⲿ�����������llp
			Application::getInstance()->openURL("https://m.tianyi9.com");
		}
	});
	return true;

}