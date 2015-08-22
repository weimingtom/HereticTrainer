
#include"pauseLiveScene.h"
#include "cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"CocosHelper.h"
#include"CrossPlatformHelper.h"
#include"Timer.h"
#include"Sound.h"
using namespace ui;
PauseLiveScene* PauseLiveScene::create(Texture2D* texture)
{

	PauseLiveScene *pRet = new(std::nothrow)PauseLiveScene();
	if (pRet && pRet->init(texture))
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
Scene* PauseLiveScene::createScene(Texture2D* texture)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseLiveScene::create(texture);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool PauseLiveScene::init(Texture2D* texture)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto background = Sprite::createWithTexture(texture);
	background->setPosition(540, 360);
	background->setFlippedY(true);
	//spBackGround->setScale(0.5);
	addChild(background);
	auto rootNode = CSLoader::createNode("PauseLiveScene.csb");
	addChild(rootNode);
	((Button*)seekNodeByName(rootNode, "button_return"))->addTouchEventListener([](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
			Director::getInstance()->popScene();
		}
	});
	((Button*)seekNodeByName(rootNode, "button_resume"))->addTouchEventListener([](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			
			Director::getInstance()->popScene();
			Sound::getInstance()->resumeAll();
			GameTimer::getInstance()->resume();
		}
	});

	return true;

}