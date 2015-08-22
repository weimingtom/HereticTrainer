#include"MainGame.h"
#include"Sound.h"
#include"LiveResultScene.h"
#include"ui/CocosGUI.h"
#include"pauseLiveScene.h"
using namespace ui;
MainGame* MainGame::create(LiveInfo liveInfo)
{

	MainGame *pRet = new(std::nothrow)MainGame();
	if (pRet && pRet->init(liveInfo))
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
void  MainGame::createScoreSprite()
{
	//评分精灵创建
	perfectSprite = Sprite::create("perfect.png");
	greatSprite = Sprite::create("great.png");
	goodSprite = Sprite::create("good.png");
	badSprite = Sprite::create("bad.png");
	missSprite = Sprite::create("miss.png");
	perfectSprite->setVisible(false);
	greatSprite->setVisible(false);
	goodSprite->setVisible(false);
	badSprite->setVisible(false);
	missSprite->setVisible(false);
	perfectSprite->setPosition(Vec2(540, 360));
	greatSprite->setPosition(Vec2(540, 360));
	goodSprite->setPosition(Vec2(540, 360));
	badSprite->setPosition(Vec2(540, 360));
	missSprite->setPosition(Vec2(540, 360));

	addChild(perfectSprite, 30);
	addChild(greatSprite, 30);
	addChild(goodSprite, 30);
	addChild(badSprite, 30);
	addChild(missSprite, 30);

	//combo显示
	comboLabel = Label::createWithSystemFont("combo", "simhei.ttf", 30);
	comboLabel->setPosition(Vec2(570, 415));
	comboLabel->setAnchorPoint(Vec2(0, 0));
	comboLabel->setVisible(false);
	addChild(comboLabel);
	comboCountLabel = Label::createWithSystemFont("101", "simhei.ttf", 55);
	comboCountLabel->setPosition(Vec2(480, 405));
	comboCountLabel->setAlignment(TextHAlignment::RIGHT);
	comboCountLabel->setAnchorPoint(Vec2(0, 0));
	addChild(comboCountLabel);
	comboCountLabel->setVisible(false);
}
//创建触摸层
void MainGame::createTouchLayer()
{
	//创建一个透明的layer覆盖全部
	auto touchLayer = Layer::create();
	touchLayer->setAnchorPoint(Vec2::ZERO);
	touchLayer->setPosition(Vec2::ZERO);
	touchLayer->setContentSize(Size(1080, 720));

	addChild(touchLayer, 30);
	//为其添加一个触摸监听者
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(MainGame::onTouchesBegan, this);
	//touchListener->onTouchesMoved = CC_CALLBACK_2(MainGame::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(MainGame::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, touchLayer);


}
void MainGame::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto touch : touches)
	{
		//如果是属于长型beat的触摸释放事件
		auto iter = touchMap.find(touch);
		if (iter != touchMap.end())
		{

			
			if (touchMap[touch]->touchEnd(timer->getTime()))
			{
				showPressEffect(touchMap[touch]->getPos());
			}
			touchMap.erase(iter);
		}
	}

}
void MainGame::showPressEffect(int pos)
{
	auto spRing = Sprite::create("PressEffect_Ring.png");
	spRing->setPosition(GameSetting::getInstance()->getTargetPosition(pos));
	spRing->setScale(0.4);
	auto sqRing = Sequence::create(Spawn::create(FadeOut::create(0.2), ScaleTo::create(0.1, 1), NULL),
		CCCallFuncN::create([=](Ref *sender){this->removeChild(spRing); }), NULL);;
	spRing->runAction(sqRing);
	this->addChild(spRing, 5);

	auto spStar = Sprite::create("PressEffect_Star.png");
	spStar->setPosition(GameSetting::getInstance()->getTargetPosition(pos));
	auto sqStar = Sequence::create(DelayTime::create(0.1), FadeOut::create(0.1),
		CCCallFuncN::create([=](Ref *sender){this->removeChild(spStar); }), NULL);
	spStar->runAction(sqStar);
	this->addChild(spStar, 5);


}
bool MainGame::checkTouch(int pos, const Vec2 &touchLocation)//这里采取的判定区域是在圆内+长方形内
{
	auto bornPoint = GameSetting::getInstance()->getBornPosition();
	auto targetPoint = GameSetting::getInstance()->getTargetPosition(pos);
	float touchWidth = 80;
	float touchHeight = 140;
	float touchDistance = 142;
	float dis = targetPoint.distance(bornPoint);
	Rect checkRect = Rect(targetPoint.x - touchWidth, targetPoint.y - touchHeight, touchWidth * 2, touchHeight * 2);
	auto point = touchLocation.rotateByAngle(targetPoint, atan((bornPoint.x - targetPoint.x) / (bornPoint.y - targetPoint.y)));
	return (checkRect.containsPoint(point) && touchLocation.distance(targetPoint) < touchDistance);

}
void MainGame::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto touch : touches)
	{
		auto location = touch->getLocation();


		for (int i = 0; i < 9; i++)
		{
			if (checkTouch(i, location) && (touchingIndexs[i] < beats[i].size()) )
			{
				//log("%d\n",i);
				//return;
				int ret;
				do
				{
					auto beatObject = beats[i][touchingIndexs[i]];
					ret = beatObject->touchBegin(timer->getTime());
					if (ret == 0)
					{
						touchMap[touch] = beatObject;
						touchingIndexs[i]++;
						break;
						
					}
					if (ret == 1)
					{
						touchingIndexs[i]++;
					}
					if (ret == -1)
					{
						break;
					}
					
				} while (touchingIndexs[i]< beats[i].size());
				return;

			}
		}

	}
}

void MainGame::showScoreEffect(Score score)
{
	if (score == Score::NONE || score == Score::SHOWED)return;
	//static int cnt = 0;
	//log("score %d",cnt++);
	//先停止所有动作，隐藏精灵
	perfectSprite->stopAllActions();
	greatSprite->stopAllActions();
	goodSprite->stopAllActions();
	badSprite->stopAllActions();
	missSprite->stopAllActions();
	perfectSprite->setVisible(false);
	greatSprite->setVisible(false);
	goodSprite->setVisible(false);
	badSprite->setVisible(false);
	missSprite->setVisible(false);
	auto sound = Sound::getInstance();
	switch (score)
	{
	case Score::PERFECT:
		//恢复初始位置大小和透明度
		perfectSprite->setVisible(true);
		perfectSprite->setOpacity(255);
		perfectSprite->setScale(0.4);
		//缩放并渐显
		perfectSprite->runAction(Sequence::create(Show::create(), ScaleTo::create(0.1, 1), FadeOut::create(0.3), NULL));
		sound->perfect();
		break;
	case Score::GREAT:
		//恢复初始位置大小和透明度
		greatSprite->setVisible(true);
		greatSprite->setOpacity(255);
		greatSprite->setScale(0.4);
		//缩放并渐显
		greatSprite->runAction(Sequence::create(Show::create(), ScaleTo::create(0.1, 1), FadeOut::create(0.3), NULL));
		//播放声音。。。
		sound->great();
		break;
	case Score::GOOD:
		//恢复初始位置大小和透明度
		goodSprite->setVisible(true);
		goodSprite->setOpacity(255);
		goodSprite->setScale(0.4);
		//缩放并渐显
		goodSprite->runAction(Sequence::create(Show::create(), ScaleTo::create(0.1, 1), FadeOut::create(0.3), NULL));
		sound->good();
		break;
	case Score::BAD:
		//恢复初始位置大小和透明度
		badSprite->setVisible(true);
		badSprite->setOpacity(255);
		badSprite->setScale(0.4);
		//缩放并渐显
		badSprite->runAction(Sequence::create(Show::create(), ScaleTo::create(0.1, 1), FadeOut::create(0.3), NULL));
		sound->bad();
		break;
	case Score::MISS:
		//恢复初始位置大小和透明度
		missSprite->setVisible(true);
		missSprite->setOpacity(255);
		missSprite->setScale(0.4);
		//缩放并渐显
		missSprite->runAction(Sequence::create(Show::create(), ScaleTo::create(0.1, 1), FadeOut::create(0.3), NULL));
		sound->miss();
		break;
	default:
		break;
	}
}
Scene* MainGame::createScene(LiveInfo liveInfo)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGame::create(liveInfo);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool MainGame::init(LiveInfo liveInfo)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->timer = GameTimer::getInstance();
	this->liveInfo = liveInfo;
	if (FileUtils::getInstance()->isFileExist(liveInfo.bgimg_path))
	{
		//创建背景，并缩放到1080*720；
		auto backgroundSprite = Sprite::create(liveInfo.bgimg_path);
		addChild(backgroundSprite);
		backgroundSprite->setPosition(Vec2(540, 360));
		backgroundSprite->setScaleX(1080 / backgroundSprite->getContentSize().width);
		backgroundSprite->setScaleY(720 / backgroundSprite->getContentSize().height);
		
	}
	auto pauseButton = ui::Button::create("button_pause.png");
	pauseButton->addTouchEventListener([this, pauseButton](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			
			pauseButton->setVisible(false);
			RenderTexture *renderTexture = RenderTexture::create(1080, 720);
			renderTexture->begin();
			//renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
			this->getParent()->visit();
			renderTexture->end();
			Director::getInstance()->getRenderer()->render();
			auto scene = PauseLiveScene::createScene(renderTexture->getSprite()->getTexture());
			pauseButton->setVisible(true);
			Director::getInstance()->pushScene(scene);
			Sound::getInstance()->pauseALL();
			timer->pause();
			
			
			
		}
	});
	pauseButton->setPosition(Vec2(1039.57, 693.79));
	addChild(pauseButton,40);

	createScoreSprite();
	createTouchLayer();
	createBeatObjects();
	/*for (int i = 0; i < 9; i++)
	{
		auto test = DrawNode::create();
		test->drawDot(targetPoint[i], 142/2, Color4F::WHITE);
		addChild(test, 20);
	}*/
	startGame();
	return true;

}
void MainGame::createBeatObjects()
{
	for (int i = 0; i < 9; i++)
	{
		beats[i].clear();
		for (int j = 0; j < liveInfo.beats[i].size(); j++)
		{
			auto node = BeatObject::create(liveInfo.beats[i][j]);
			beats[i].push_back(node);
			addChild(node);

		}
		judgingIndexs[i] = 0;
		touchingIndexs[i] = 0;
	}
}
void MainGame::startGame()
{
	timer->init();
	Sound::getInstance()->playBGM(liveInfo.bgm_path, [this](int id, const std::string &path) 
	{
		//log("end!!!!!11");
	//	endGame(); 
	}
	);
	this->schedule(schedule_selector(MainGame::updateBeatObjects));
}

void MainGame::endGame()
{
	auto scene = LiveResultScene::createScene(liveInfo, perfectCount, greatCount, goodCount, badCount, missCount, totalComboCount, mcomboCount, 0, "S");
	Director::getInstance()->replaceScene(scene);
	Sound::getInstance()->stopAll();
}
void MainGame::Count(Score score,bool isCountCombo)
{
//	log("%d",score);
	switch (score)
	{
	case Score::PERFECT:
		perfectCount++;
		if (isCountCombo)
		{
			comboCount++;
			if (comboCount>0)
			{
				totalComboCount++;
				showComboCountEffect(comboCount);
			}
			if (comboCount > mcomboCount)mcomboCount = comboCount;

		
		}
		break;
	case Score::GREAT:

		greatCount++;
		if (isCountCombo)
		{
			comboCount++;
			if (comboCount>0)
			{
				totalComboCount++;
				showComboCountEffect(comboCount);
			}
			if (comboCount > mcomboCount)mcomboCount = comboCount;
		}
		break;
	case Score::GOOD:
		goodCount++;
		comboCount = -1;
		showComboCountEffect(comboCount);
		break;
	case Score::BAD:
		badCount++;
		comboCount = -1;
		showComboCountEffect(comboCount);
		break;
	case Score::MISS:
		missCount++;
		comboCount = -1;
		showComboCountEffect(comboCount);
		break;
	default:
		break;
	}
	
}
void MainGame::updateBeatObjects(float t)
{

	for (int i = 0; i < 9; i++)
	{
		for (int j =0; j < beats[i].size(); j++)
		{
			
			beats[i][j]->updateState(timer->getTime());
			

		}
	}
	bool ended = true;
	auto lastScore = Score::NONE;
	for (int i = 0; i < 9; i++)
	{
		while (1)
		{
			if (judgingIndexs[i] >= beats[i].size())break;
			ended = false;
			auto score = beats[i][judgingIndexs[i]]->getHeadScore();
			if (score != Score::NONE&&score != Score::SHOWED)
			{
			//	log("t");
				
				
				lastScore = score;
				
				Count(score, true);
				beats[i][judgingIndexs[i]]->headScoreShowed();
			}
			score = beats[i][judgingIndexs[i]]->getTailScore();
			if (score != Score::NONE&&score != Score::SHOWED)
			{
			//	log("t");
				auto 
				
				lastScore = score;
				Count(score, false);
				beats[i][judgingIndexs[i]]->tailScoreShowed();
			}
			if (beats[i][judgingIndexs[i]]->getTailScore() == Score::SHOWED&&beats[i][judgingIndexs[i]]->getHeadScore() == Score::SHOWED)
			{
				judgingIndexs[i]++;
				//log("p");
			}
			else break;

		}
	}
	showScoreEffect(lastScore);
	if (ended)endGame();
	
}
void MainGame::showComboCountEffect(int cnt)
{
	if (cnt>0)
	{
		comboCountLabel->setString(String::createWithFormat("%d", cnt)->_string);
		comboCountLabel->setVisible(true);
		comboLabel->setVisible(true);
		comboCountLabel->runAction(Sequence::create(EaseIn::create(ScaleTo::create(0.1, 1.2), 2), EaseIn::create(ScaleTo::create(0.1, 1), 2), NULL));
		comboLabel->runAction(Sequence::create(EaseIn::create(ScaleTo::create(0.1, 1.2), 2), EaseIn::create(ScaleTo::create(0.1, 1), 2), NULL));
	}
	else
	{
		comboCountLabel->setVisible(false);
		comboLabel->setVisible(false);
	}
}