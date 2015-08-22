
#ifndef __LIVELISTVIEW_VIEW_H_
#define __LIVELISTVIEW_VIEW_H_
#include"ui/CocosGUI.h"
#include"LLPMediator.h"
#include<functional>
#include<vector>
USING_NS_CC;
/*
一个自定义的liveView，基于ScrollView实现
用于显示live列表，
static LiveListView * create(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
_touchCallback是触摸了某一个列表项的回调，_bounceCallback上拉事件的回调
*/
//using namespace ui;
class LiveListView :public ui::ScrollView 
{
public:
	//_touchCallback是触摸了某一个列表项的回调，_bounceCallback上拉事件的回调
	static LiveListView * create(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
	//_touchCallback是触摸了某一个列表项的回调，_bounceCallback上拉事件的回调
	bool init(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
	//向尾部添加列表项
	void addItems(LiveList liveList);
	//移除所有项目
	void removeAllItems();
private:
	std::function<void()> bounceCallback;
	std::function<void(LiveListItem item)> touchCallback;

	void scrollEventCallback(Ref* ref, ScrollView::EventType eventType);
	std::vector<Layout*> layouts;
};




#endif