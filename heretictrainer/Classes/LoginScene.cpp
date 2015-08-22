#include"LoginScene.h"
#include"ui/CocosGUI.h"
#include"CocosHelper.h"
#include"TipLayer.h"
#include "cocostudio/CocoStudio.h"
#include"LoadingLayer.h"
#include"LLPMediator.h"
#include"RegisterScene.h"
#include"LiveListScene.h"
USING_NS_CC;
using namespace ui;
LoginScene* LoginScene::create(bool isStartMode)
{

	LoginScene *pRet = new(std::nothrow)LoginScene(); 
	if (pRet && pRet->init(isStartMode)) 
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
Scene* LoginScene::createScene(bool isStartMode)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create(isStartMode);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoginScene::init(bool isStartMode)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//载入布局文件，详见cocos studio
	auto rootNode = CSLoader::createNode("startScene.csb");
	addChild(rootNode);
	//界面上存在两个层，一个启动动画层，一个登陆界面层
	auto startNode = (Node*)(seekNodeByName(rootNode, "startLayer"));
	auto loginNode = (Node*)(seekNodeByName(rootNode, "loginLayer"));
	
	//不显示启动动画，一定是进入应用后调用的，显示返回按钮
	auto returnButton = (Button*)(seekNodeByName(loginNode, "button_return"));
	if (!isStartMode)
	{
		//为返回按钮添加触摸事件
		returnButton->addTouchEventListener([](Ref*ref, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
				Director::getInstance()->popScene();
		});
	}
	else
	{
		returnButton->setVisible(false);
	}

	if (isStartMode)
	{
		//启动动画
		loginNode->setOpacity(0);

		auto logoSprite = (Sprite*)seekNodeByName(rootNode, "sprite_logo");
		logoSprite->runAction(Sequence::create(DelayTime::create(1), Spawn::create(ScaleTo::create(0.7, 0.4775), MoveTo::create(0.7, Vec2(551.81, 593.28)), NULL), NULL));
		startNode->runAction(Sequence::create(DelayTime::create(1), FadeOut::create(0.7), NULL));
		loginNode->runAction(Sequence::create(DelayTime::create(1), FadeIn::create(0.7), NULL));
		
	}
	else
	{
		//不显示动画
		auto logoSprite = (Sprite*)seekNodeByName(rootNode, "sprite_logo");
		logoSprite->setPosition(Vec2(551.81, 593.28));
		logoSprite->setScale(0.7);
		startNode->removeFromParent();

	}

	//log("ppppp");
	auto loginButton = (Button*)seekNodeByName(loginNode, "button_login");
	//loginButton->setTouchEnabled(true);
	//loginButton->setVisible(false);
	//登陆按钮添加事件
	loginButton->addTouchEventListener([this, loginNode](Ref*ref, Widget::TouchEventType type)
	{

		if (type == Widget::TouchEventType::ENDED)
		{
			
			auto username = ((TextField*)seekNodeByName(this, "textfield_username"))->getString();
			auto password = ((TextField*)seekNodeByName(this, "textfield_password"))->getString();
			//log("=%s %s", username.c_str(), password.c_str());
			//检查用户名密码是否为空
			if (username.size() && password.size())
			{
				//等待动画层
				auto loadingLayer =  LoadingLayer::create();
				addChild(loadingLayer, 20);

				auto llp = LLPMediator::getInstance();
				llp->login(username, llp->encryptPassword(password));
				
				//启动一个循环，没帧检查状态
				this->schedule([llp, loadingLayer, this](float t)
				{
					//如果不是正在连接状态，即连接完成
					if (llp->getLoginConnertState() != llp->CONNERTSTATE_CONNERTING)
					{
						//关闭循环
						this->unschedule("checkLogin");
						//移除等待动画层
						loadingLayer->removeFromParent();
						//是否登陆成功
						if (llp->isLogined())
						{
							//进入livelist页面
							auto scene = LiveListScene::createScene();
							Director::getInstance()->pushScene(scene);
						}
						else
						{
							//显示 tiplayer，提示登陆失败
							auto text = (Text*)seekNodeByName(this, "text_fail");
							auto layer=TipLayer::create(text->getString(), text->getFontSize());
							addChild(layer);
						}
					}
				},"checkLogin");
			}
			
		}
	});
	
	auto skipButton = (Button*)seekNodeByName(loginNode, "button_skip");
	skipButton->addTouchEventListener([this, isStartMode](Ref*ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			if (isStartMode)
			{
				auto scene = LiveListScene::createScene();
				Director::getInstance()->pushScene(scene);
			}
			else
			{
				Director::getInstance()->popScene();
			}
		}
	});
	


	auto registerButton = (Button*)seekNodeByName(rootNode, "button_register");
	registerButton->addTouchEventListener([this, isStartMode](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto scene = RegisterScene::createScene();
			Director::getInstance()->pushScene(scene);
		}
	});

	//47.75%,551.81 593.28
	
	return true;

}
