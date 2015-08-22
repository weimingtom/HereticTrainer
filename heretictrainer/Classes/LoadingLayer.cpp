#include"LoadingLayer.h"

LoadingLayer* LoadingLayer::create()
{
	LoadingLayer* layer = new (std::nothrow) LoadingLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}
bool LoadingLayer::init()
{
	if (!Layer::init())return false;
	//����һ���㣬������û�¼�
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event *event)->bool{return true; };
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	Size size = Director::getInstance()->getVisibleSize();
	setContentSize(size);
	setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(0, 0));
	//����
	auto backgroundSprite = Sprite::create("res/common_loading_backgound.png");
	addChild(backgroundSprite);
	backgroundSprite->setAnchorPoint(Vec2(0.5, 0.5));
	backgroundSprite->setPosition(Vec2(size.width/2,size.height/2));
	//�ջ�����
	auto ringSprite = Sprite::create("res/common_loading_ring.png");
	addChild(ringSprite);
	//�ջ�ת�Ķ���
	ringSprite->setAnchorPoint(Vec2(0.5, 0.5));
	ringSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	ringSprite->runAction(RepeatForever::create(RotateBy::create(1.25, 360)));
	//log("===");
	return true;
}