
#include"LiveDetailsScene.h"
#include"ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include"CocosHelper.h"
#include"LoadLiveScene.h"
using namespace ui;
LiveDetailsScene* LiveDetailsScene::create(LiveDetails _liveDetails)
{

	LiveDetailsScene *pRet = new(std::nothrow)LiveDetailsScene();
	if (pRet && pRet->init(_liveDetails))
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
Scene* LiveDetailsScene::createScene(LiveDetails _liveDetails)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LiveDetailsScene::create(_liveDetails);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool LiveDetailsScene::init(LiveDetails _liveDetails)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	liveDetails = _liveDetails;
	//加载布局文件
	auto rootNode = CSLoader::createNode("LiveDetails.csb");
	addChild(rootNode);
	//设置返回按钮点击设计
	((ui::Button*)(seekNodeByName(rootNode, "button_return")))->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});
	//一些数据的加载显示
	((Text*)seekNodeByName(rootNode, "text_live_name"))->setString(liveDetails.live_name);
	((Text*)seekNodeByName(rootNode, "text_level"))->setString(String::createWithFormat("%d",liveDetails.level)->_string);
	((Text*)seekNodeByName(rootNode, "text_artist"))->setString(liveDetails.artist);
	((Text*)seekNodeByName(rootNode, "text_upload_user"))->setString(liveDetails.upload_user.username);
	((Text*)seekNodeByName(rootNode, "text_click_count"))->setString(String::createWithFormat("%d", liveDetails.click_count)->_string);
	((Text*)seekNodeByName(rootNode, "text_introduction"))->setString(liveDetails.live_info);
	//live简介这里显示排版有点问题，待修正
	((Text*)seekNodeByName(rootNode, "text_introduction"))->setTextAreaSize(Size(400,0));
	((Text*)seekNodeByName(rootNode, "text_introduction"))->ignoreContentAdaptWithSize(false);
	((Text*)seekNodeByName(rootNode, "text_introduction"))->ignoreAnchorPointForPosition(true);
	//((Text*)seekNodeByName(rootNode, "text_introduction"))->setPosition(Vec2(616.31, 284.19));
	//设置开始游戏按钮事件
	((ui::Button*)seekNodeByName(rootNode, "button_start"))->addTouchEventListener([this, rootNode](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			//进入加载界面
			auto scene = LoadLiveScene::createScene(liveDetails);
			Director::getInstance()->pushScene(scene);
			
		}
	});
	//显示封面
	auto titleSprite = Sprite::create(liveDetails.cover_path);
	titleSprite->setAnchorPoint(Vec2(0, 0));
	titleSprite->setPosition(Vec2(1, 1));
	auto titleImgBackgroundSprite = ((Sprite*)seekNodeByName(rootNode, "titleImgBackground"));
	titleSprite->setScaleX((titleImgBackgroundSprite->getContentSize().width-2) / titleSprite->getContentSize().width);
	titleSprite->setScaleY((titleImgBackgroundSprite->getContentSize().height - 2) / titleSprite->getContentSize().height);
	titleImgBackgroundSprite->addChild(titleSprite);
	return true;

}