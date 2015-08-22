#ifndef __MENULAYER_LAYER_
#define __MENULAYER_LAYER_
#include<string>
#include<vector>
#include<functional>
#include"cocos2d.h"
USING_NS_CC;
/*
显示一个菜单,目前只用于显示多少分类
*/
struct MenuDataItem
{
	std::string title;
	int userData;
	MenuDataItem(std::string title = "", int userData = 0){ this->title = title; this->userData = userData; };
};
class MenuLayer :public Layer
{
public:
	static MenuLayer* create(std::function<void(MenuDataItem item)> _touchCallback, Node* node);
	bool init(std::function<void(MenuDataItem item)> _touchCallback, Node* node);
	void setItems(std::vector<MenuDataItem> items, Vec2 position);
private:
	std::function<void(MenuDataItem item)> touchCallback;
};

#endif