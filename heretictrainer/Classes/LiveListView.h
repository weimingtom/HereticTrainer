
#ifndef __LIVELISTVIEW_VIEW_H_
#define __LIVELISTVIEW_VIEW_H_
#include"ui/CocosGUI.h"
#include"LLPMediator.h"
#include<functional>
#include<vector>
USING_NS_CC;
/*
һ���Զ����liveView������ScrollViewʵ��
������ʾlive�б�
static LiveListView * create(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
_touchCallback�Ǵ�����ĳһ���б���Ļص���_bounceCallback�����¼��Ļص�
*/
//using namespace ui;
class LiveListView :public ui::ScrollView 
{
public:
	//_touchCallback�Ǵ�����ĳһ���б���Ļص���_bounceCallback�����¼��Ļص�
	static LiveListView * create(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
	//_touchCallback�Ǵ�����ĳһ���б���Ļص���_bounceCallback�����¼��Ļص�
	bool init(std::function<void(LiveListItem item)> _touchCallback, std::function<void()> _bounceCallback);
	//��β������б���
	void addItems(LiveList liveList);
	//�Ƴ�������Ŀ
	void removeAllItems();
private:
	std::function<void()> bounceCallback;
	std::function<void(LiveListItem item)> touchCallback;

	void scrollEventCallback(Ref* ref, ScrollView::EventType eventType);
	std::vector<Layout*> layouts;
};




#endif