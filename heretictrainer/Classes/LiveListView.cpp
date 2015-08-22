#include"LiveListView.h"
#include"CrossPlatformHelper.h"
LiveListView * LiveListView::create(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback)
{
	LiveListView* widget = new (std::nothrow) LiveListView();
	if (widget && widget->init(_touchCallback,_bounceCallback))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}
bool LiveListView::init(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback)
{
	if (ScrollView::init())

	{
		touchCallback = _touchCallback;
		bounceCallback = _bounceCallback;
		addEventListener(std::bind(&LiveListView::scrollEventCallback, this, std::placeholders::_1, std::placeholders::_2));
		setBounceEnabled(true);
		return true;
	}
	return false;
}
//�����ص�
void LiveListView::scrollEventCallback(Ref* ref, ScrollView::EventType eventType)
{
	if (eventType == EventType::BOUNCE_BOTTOM)
	{
		bounceCallback();
	}
}
void LiveListView::removeAllItems()
{
	//�Ƴ�����layout
	for (int i = 0; i < layouts.size(); i++)
		layouts[i]->removeFromParent();
	layouts.clear();
	//������С
	setInnerContainerSize(Size(1080, 0));
}
void LiveListView::addItems(LiveList liveList)
{


	
	for (int i = 0; i < liveList.items.size(); i++)
	{
		LiveListItem item = liveList.items[i];
		//item��Ŀ�ĵز�layout
		auto layout = ui::Layout::create();
		layout->setAnchorPoint(Vec2(0.5, 0.5));
		//layout->setPosition(Vec2(0, 0));
		addChild(layout);
		layout->setContentSize(Size(213, 256));
		layout->setBackGroundImage("common_livelist_background.png");
		//��Ӵ����¼�
		layout->addTouchEventListener([item, this](Ref * ref, Widget::TouchEventType touchType)
		{
			if (touchType == Widget::TouchEventType::ENDED)
			{
				touchCallback(item);
			
			}

		});
		layout->setTouchEnabled(true);
		//�����imageView�Ĵ���
		auto titleImageView = ui::ImageView::create(item.cover_path);
		layout->addChild(titleImageView);
		titleImageView->setAnchorPoint(Vec2(0, 1));
		titleImageView->setPosition(Vec2(1, 255));
		//titleImageView->setCapInsets(Rect(0, 0, 211, 192));
		//���ŷ���
		titleImageView->setScaleX(211 / titleImageView->getCustomSize().width);
		titleImageView->setScaleY(192 / titleImageView->getCustomSize().height);
		//һЩͼ��
		auto clickCountIconImageView = ui::ImageView::create("common_livelist_icon_clickcount.png");
		layout->addChild(clickCountIconImageView);
		clickCountIconImageView->setPosition(Vec2(27.77, 18.19));
		auto levelIconImageView = ui::ImageView::create("common_livelist_icon_level.png");
		levelIconImageView->setPosition(Vec2(125.70, 18.19));
		layout->addChild(levelIconImageView);
		ui::Text*clickCountText;
		if (item.click_count<0)
			clickCountText = ui::Text::create("?", "simhei.ttf", 17);
		else
		 clickCountText = ui::Text::create(String::createWithFormat("%d",item.click_count)->_string, "simhei.ttf", 17);
		clickCountText->setPosition(Vec2(66.96, 18.19));
		clickCountText->setTextColor(Color4B(0x7f, 0x7f, 0x7f, 255));
		layout->addChild(clickCountText);
		auto levelText = ui::Text::create(String::createWithFormat("%d", item.level)->_string, "simhei.ttf", 17);
		levelText->setPosition(Vec2(160.72, 18.19));
		levelText->setTextColor(Color4B(0x7f, 0x7f, 0x7f, 255));
		layout->addChild(levelText);



		std::string title = CrossPlatformHelper::limitString(item.live_name, 11); 

		auto titleText = ui::Text::create(title, "simhei.ttf", 16);
		titleText->setTextColor(Color4B(0x1a, 0x1a, 0x1a, 255));
		titleText->setPosition(Vec2(14, 44.74));
		titleText->setTextHorizontalAlignment(TextHAlignment::LEFT);
		titleText->setAnchorPoint(Vec2(0, 0.5));
		layout->addChild(titleText);

		

		
		layouts.push_back(layout);
		
		//layout->addClickEventListener()
	}
	//235 536
	//230 +300+200
	//setBackGroundColor(Color3B::BLACK);
	//�����ڲ�������С
	int height = ((layouts.size() - 1) / 4 + 1) * 300;
	setInnerContainerSize(Size(1080, height));
	for (int i = 0; i < layouts.size(); i++)
	{
		layouts[i]->setPosition(Vec2(160 + (i % 4) * 250, height - 150 - (i / 4) * 300));
	}


	
}