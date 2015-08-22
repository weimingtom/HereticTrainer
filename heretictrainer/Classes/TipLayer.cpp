#include"TipLayer.h"

TipLayer* TipLayer::create(std::string tipText, float fontSize)
{
	TipLayer* layer = new (std::nothrow) TipLayer();
	if (layer && layer->init(tipText,fontSize))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}
bool TipLayer::init(std::string tipText, float fontSize)
{
	if (!Layer::init())return false;
	auto action1 = Sequence::create(Spawn::create(MoveTo::create(0.2, Vec2(Vec2(540, 95))), FadeIn::create(0.2), NULL), DelayTime::create(1.2), FadeOut::create(0.7), CallFunc::create([this](){this->removeFromParent(); }), NULL);
	auto action2 = Sequence::create(Spawn::create(MoveTo::create(0.2, Vec2(Vec2(540, 95))), FadeIn::create(0.2), NULL), DelayTime::create(1.2), FadeOut::create(0.7), NULL);

	auto backgroundSprite = Sprite::create("common_tip_background.png");
	backgroundSprite->setPosition(Vec2(540,75));
	backgroundSprite->setOpacity(0);
	backgroundSprite->runAction(action1);
	addChild(backgroundSprite,5);

	//log(tipText.c_str());
	auto tipLabel = Label::createWithSystemFont(tipText, "simhei.ttf", fontSize);
	tipLabel->setOpacity(0);
	tipLabel->setPosition(Vec2(540, 75));
	tipLabel->runAction(action2);
	addChild(tipLabel,10);
	return true;
}