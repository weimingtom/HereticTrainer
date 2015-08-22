
#include"RegisterScene.h"
#include"ui/CocosGUI.h"
#include"CocosHelper.h"
#include"TipLayer.h"
#include "cocostudio/CocoStudio.h"
#include"LoadingLayer.h"
#include"LLPMediator.h"
using namespace ui;
RegisterScene* RegisterScene::create()
{

	RegisterScene *pRet = new(std::nothrow)RegisterScene();
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
Scene* RegisterScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RegisterScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool RegisterScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("RegisterScene.csb");
	addChild(rootNode);
	auto returnButton = (Button*)seekNodeByName(rootNode, "button_return");
	returnButton->addTouchEventListener([rootNode, this](Ref*ref, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});



	auto registerButton=(ui::Button*)seekNodeByName(rootNode, "button_register");
	registerButton->addTouchEventListener([rootNode,this](Ref*ref, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			std::string email = ((TextField*)seekNodeByName(rootNode, "textfield_email"))->getString();
			//数据的校检
			if (!email.size())
			{
				//显示提示，由于未免于字符串的转换，这里的字符串均存储在布局文件中，故获取
				Text* text = (Text*)seekNodeByName(rootNode, "text_email_empty");
				auto layer = TipLayer::create(text->getString(), text->getFontSize());
				addChild(layer);
				return;
			}
			std::string username = ((TextField*)seekNodeByName(rootNode, "textField_username"))->getString();
			if (!username.size())
			{
				Text* text = (Text*)seekNodeByName(rootNode, "text_username_empty");
				auto layer = TipLayer::create(text->getString(), text->getFontSize());
				addChild(layer);
				return;
			}
			std::string password = ((TextField*)seekNodeByName(rootNode, "textField_password"))->getString();
			if (!password.size())
			{
				Text* text = (Text*)seekNodeByName(rootNode, "text_password_empty");
				auto layer = TipLayer::create(text->getString(), text->getFontSize());
				addChild(layer);
				return;
			}

			std::string repty= ((TextField*)seekNodeByName(rootNode, "textField_repty"))->getString();
			if (!repty.size())
			{
				Text* text = (Text*)seekNodeByName(rootNode, "text_repty_empty");
				auto layer = TipLayer::create(text->getString(), text->getFontSize());
				addChild(layer);
				return;
			}
			if (password != repty)
			{
				Text* text = (Text*)seekNodeByName(rootNode, "text_password_wrong");
				auto layer = TipLayer::create(text->getString(), text->getFontSize());
				addChild(layer);
				return;
			}


			std::string code= ((TextField*)seekNodeByName(rootNode, "textField_code"))->getString();
			auto loadingLayer = LoadingLayer::create();
			addChild(loadingLayer, 20);

			auto llp = LLPMediator::getInstance();
			llp->reg(email, llp->encryptPassword(password), code, username);


			this->schedule([llp, loadingLayer, this,rootNode](float t)
			{
				if (llp->getRegConnertState() != llp->CONNERTSTATE_CONNERTING)
				{
					this->unschedule("checkRegister");
					loadingLayer->removeFromParent();
					if (llp->isRegSuccessed())
					{
						auto text = (Text*)seekNodeByName(this, "text_register_successed");
						auto layer = TipLayer::create(text->getString(), text->getFontSize());
						addChild(layer);
						((TextField*)seekNodeByName(rootNode, "textfield_email"))->setString("");
						((TextField*)seekNodeByName(rootNode, "textField_username"))->setString("");
						((TextField*)seekNodeByName(rootNode, "textField_password"))->setString("");
						((TextField*)seekNodeByName(rootNode, "textField_repty"))->setString("");
						((TextField*)seekNodeByName(rootNode, "textField_code"))->setString("");
					}
					else
					{
						auto text = (Text*)seekNodeByName(this, "text_register_fail");
						auto layer = TipLayer::create(text->getString(), text->getFontSize());
						addChild(layer);
					}
				}
			}, "checkRegister");
		}

	});
	return true;

}
