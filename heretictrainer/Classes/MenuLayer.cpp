#include"MenuLayer.h"
#include"ui/CocosGUI.h"
MenuLayer* MenuLayer::create(std::function<void(MenuDataItem item)> _touchCallback, Node* node)
{
	MenuLayer* layer = new (std::nothrow) MenuLayer();
	if (layer && layer->init(_touchCallback,node))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}
bool MenuLayer::init(std::function<void(MenuDataItem item)> _touchCallback,Node* node)
{
	if (!Layer::init())return false;
	node->addChild(this, 100);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event *event)->bool{this->removeFromParent(); return true; };
	touchListener->onTouchEnded = [this](Touch* touch, Event *event){};

	touchListener->onTouchMoved = [this](Touch* touch, Event *event){};
	touchListener->onTouchCancelled = [this](Touch* touch, Event *event){};

	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	Size size = Director::getInstance()->getVisibleSize();
	setContentSize(size);
	setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(0, 0));
	touchCallback = _touchCallback;
	return true;
}
void MenuLayer::setItems(std::vector<MenuDataItem> items,Vec2 position)
{
	removeAllChildren();
	auto background = ui::ImageView::create("common_menu_background.png");
	background->setAnchorPoint(Vec2(1, 1));
	background->setPosition(position);
	addChild(background);

	auto scrollView = ui::ScrollView::create();
	addChild(scrollView,30);
	scrollView->setPosition(position);
	scrollView->setAnchorPoint(Vec2(1, 1));
	//156*264
	if (items.size() >= 5)
	{
		scrollView->setContentSize(Size(156, 264));
		background->setScaleY(1);
	}
	else
	{
		int h = 46 * items.size();
		scrollView->setContentSize(Size(156, h));
		background->setScaleY(h / 264.0);

	}
	scrollView->setInnerContainerSize(Size(156, 46 * items.size()));
	//scrollView->setTouchEnabled(true);
	for (int i = 0; i < items.size(); i++)
	{
		auto item = items[i];
		auto layout = ui::Layout::create();
		scrollView->addChild(layout);
		layout->setContentSize(Size(153, 46));

		layout->setAnchorPoint(Vec2(0.5, 0.5));
		layout->setPosition(Vec2(156 / 2, 46 * items.size() - (23 + 46 * i)));
		layout->addTouchEventListener([item, this](Ref*ref, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{ 
				touchCallback(item);
				this->removeFromParent();
			}
		});
		layout->setTouchEnabled(true);
		

		auto text = ui::Text::create(item.title,"simhei.ttf",20);
		text->setPosition(Vec2(156 / 2, 46 * items.size() - (23 + 46 * i)));
		text->setAnchorPoint(Vec2(0.5, 0.5));
		text->setTextHorizontalAlignment(TextHAlignment::CENTER);
		text->setTextVerticalAlignment(TextVAlignment::CENTER);
		scrollView->addChild(text,20);

		
		
		if (i != items.size() - 1)
		{
			auto line = ui::ImageView::create("res/common_menu_line.png");
			scrollView->addChild(line,0);
			line->setPosition(Vec2(153/2,46+i*46));
		}
	}
	

}