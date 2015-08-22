


#include"LocalScene.h"
#include"ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include"CocosHelper.h"
using namespace ui;

LocalScene* LocalScene::create()
{

	LocalScene *pRet = new(std::nothrow)LocalScene();
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
Scene* LocalScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LocalScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool LocalScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("LocalScene.csb");
	addChild(rootNode);
	((Button*)(seekNodeByName(rootNode, "button_return")))->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});
	return true;

}