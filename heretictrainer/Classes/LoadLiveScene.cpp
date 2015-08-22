
#include"LoadLiveScene.h"

#include "cocostudio/CocoStudio.h"
#include"CocosHelper.h"
#include"MainGame.h"
using namespace ui;
LoadLiveScene* LoadLiveScene::create(LiveDetails _liveDetails)
{

	LoadLiveScene *pRet = new(std::nothrow)LoadLiveScene();
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
Scene* LoadLiveScene::createScene(LiveDetails _liveDetails)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadLiveScene::create(_liveDetails);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool LoadLiveScene::init(LiveDetails _liveDetails)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	llp = LLPMediator::getInstance();
	liveDetails = _liveDetails;
	//加载布局文件，详细见cocos studio
	auto rootNode = CSLoader::createNode("LoadLiveScene.csb");
	addChild(rootNode);
	//加载封面
	auto titleSprite = Sprite::create(liveDetails.cover_path);
	titleSprite->setAnchorPoint(Vec2(0, 0));
	titleSprite->setPosition(Vec2(1, 1));
	auto titleImgBackgroundSprite = ((Sprite*)seekNodeByName(rootNode, "titleImgBackground"));
	titleSprite->setScaleX((titleImgBackgroundSprite->getContentSize().width - 2) / titleSprite->getContentSize().width);
	titleSprite->setScaleY((titleImgBackgroundSprite->getContentSize().height - 2) / titleSprite->getContentSize().height);
	titleImgBackgroundSprite->addChild(titleSprite);
	//加载live名称

	((Text*)seekNodeByName(rootNode, "title"))->setString(liveDetails.live_name);
	lodingBar = ((LoadingBar*)seekNodeByName(rootNode, "loadingBar"));
	
	llp->loadLiveData(liveDetails.live_id, liveDetails.map_file, liveDetails.bgimg_file, liveDetails.bgm_file);
	//启动一个循环，显示加载进度
	this->schedule([this](float t)
	{
		lodingBar->setPercent(llp->getLoadLiveProgress());
		if (llp->getLoadLiveDataConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			if (llp->isLoadLiveDataSuccessed())
			{
				//log("%s", llp->getLiveJson().c_str());
				LiveInfo liveInfo;
				liveInfo.cover_path = liveDetails.cover_path;
				liveInfo.live_name = liveDetails.live_name;
				liveInfo.bgimg_path = liveDetails.bgimg_file + ".jpg";
				liveInfo.bgm_path = liveDetails.bgm_file + ".mp3";
				if (llp->isLogined())liveInfo.username = llp->loginUsername;
				//解析谱面数据
				llp->parseLLPBeatMapJson(liveInfo, llp->getLiveJson());
				auto scene = MainGame::createScene(liveInfo);
				Director::getInstance()->replaceScene(scene);
			}
			else Director::getInstance()->popScene();
			this->unschedule("load");
		}
	}, "load");
	return true;

}