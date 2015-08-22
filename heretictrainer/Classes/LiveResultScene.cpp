
#include"LiveResultScene.h"
#include "cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"CocosHelper.h"
#include"CrossPlatformHelper.h"
#include"MainGame.h"
using namespace ui;
LiveResultScene* LiveResultScene::create(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank)
{

	LiveResultScene *pRet = new(std::nothrow)LiveResultScene();
	if (pRet && pRet->init(liveInfo, perfectCount, greatCount, goodCount, badCount, missCount, comboCount, mcomboCount, score, rank))
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
Scene* LiveResultScene::createScene(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LiveResultScene::create(liveInfo,perfectCount,greatCount,goodCount,badCount,missCount,comboCount,mcomboCount,score,rank);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool LiveResultScene::init(LiveInfo liveInfo, int perfectCount, int greatCount, int goodCount, int badCount, int missCount, int comboCount, int mcomboCount, int score, std::string rank)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//加载布局文件
	auto rootNode = CSLoader::createNode("LiveResultScene.csb");
	addChild(rootNode);
	//一些数据的设置
	((Text*)seekNodeByName(rootNode, "text_perfect"))->setString(String::createWithFormat("%04d",perfectCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_great"))->setString(String::createWithFormat("%04d", greatCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_good"))->setString(String::createWithFormat("%04d", goodCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_bad"))->setString(String::createWithFormat("%04d", badCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_miss"))->setString(String::createWithFormat("%04d", missCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_combo"))->setString(String::createWithFormat("%04d", comboCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_mcombo"))->setString(String::createWithFormat("%04d", mcomboCount)->_string);
	((Text*)seekNodeByName(rootNode, "text_rank"))->setString(rank);
	((Text*)seekNodeByName(rootNode, "text_score"))->setString(String::createWithFormat("%012d", score)->_string);
	((Text*)seekNodeByName(rootNode, "text_livename"))->setString(CrossPlatformHelper::limitString(liveInfo.live_name, 12));
	auto username = ((Text*)seekNodeByName(rootNode, "text_username"))->getString();
//	log("%s",username.c_str());

	username =( CrossPlatformHelper::subUtfString(username, 0,1) + " " + liveInfo.username + " " + CrossPlatformHelper::subUtfString(username, 1, 3));
	((Text*)seekNodeByName(rootNode, "text_username"))->setString(username);
	auto cover = ((ImageView*)seekNodeByName(rootNode, "image_cover"));
	cover->loadTexture(liveInfo.cover_path);
	cover->setContentSize(Size(285,285));
	//重新开始按钮事件
	((Button*)seekNodeByName(rootNode, "button_retry"))->addTouchEventListener([liveInfo](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto scene = MainGame::createScene(liveInfo);
			Director::getInstance()->replaceScene(scene);
		}
	});
	//返回按钮事件
	((Button*)seekNodeByName(rootNode, "button_return"))->addTouchEventListener([](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});
	return true;

}