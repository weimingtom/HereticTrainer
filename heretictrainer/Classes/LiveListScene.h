#ifndef __LIVELISTSCENE_SCENE_H__
#define __LIVELISTSCENE_SCENE_H__
#include "cocos2d.h"
#include"LiveListView.h"
#include"LLPMediator.h"
#include"MenuLayer.h"
USING_NS_CC;
/*
显示live列表，支持与llp网站通讯获取数据并且显示

*/
class LiveListScene : public cocos2d::Layer
{
public:
	static LiveListScene*create();
	static Scene* createScene();
	virtual bool init();
private:
	//llp通讯类
	LLPMediator *llp;
	//侧边栏层
	Node *sidebarNode;
	bool isSidebarShowed = false;
	//显示侧边栏，显示侧边栏出现动画
	void showSidebar();
	//隐藏侧边栏，显示侧边栏消失动画
	void hideSidebar();
	//直接隐藏侧边栏不显示动画
	void resetSidebar();
	//一个回调函数，用户点击了一个live的时候被调用
	void LoadLiveDetailsCallback(LiveListItem item);

	/////////////////////////public LiveList/////////////////////////
	//最新列表层
	Node *publicListNode;
	//最新列表层的listView
	LiveListView * publicLiveListView;
	//一次的加载数量
	int publicLiveListLimit = 15;
	//已经加载的数量
	int publicLiveListOffset = 0;
	//移除所有项目，重新加载最新列表listView
	void reloadPublicLiveList();
	//是否最新列表已经被加载过，加载过则直接显示
	bool isPublicLiveListLoaded = false;
	//显示最新列表
	void showPublicListLayer();
	//一个回调，加载最新列表下一页
	void publicLiveListViewNextPageCallback();
	/////////////////////////search /////////////////////////////////
	//搜索界面层
	Node *searchNode;
	//搜索界面的listView
	LiveListView *searchLiveListView;
	//一次加载的数量
	int searchLiveListLimit = 15;
	//已经加载的数量
	int searchLiveListOffset = 0;
	//移除所有项目，进行一次搜索，keyword是关键词
	void search(std::string _keyword);
	//当前关键词
	std::string keyword;
	//显示搜索层
	void showSearchListLayer();
	//一个回调，加载搜索列表的下一页
	void searchLiveListViewNextPageCallback();
	/////////////////////////favorite////////////////////////////////
	//收藏列表层
	Node *favoriteNode;
	//收藏列表层的listView
	LiveListView *favoriteLiveListView;
	//一次加载的数量
	int favoriteLiveListLimit = 15;
	//已经加载的数量
	int favoriteLiveListOffset = 0;
	//是否收藏列表已经加载过了，加载过了直接显示
	bool isFavoriteLiveListLoaded = false;
	//移除所有项目，重新加载收藏列表
	void reloadFavoriteLiveList();
	//显示收藏列表层
	void showFavoriteListLayer();
	//一个回调，显示收藏列表的下一页
	void favoriteLiveListViewNextPageCallback();
	/////////////////////////category LiveList///////////////////////
	//分类列表层
	Node *categoryListNode;
	//分类列表层的listView
	LiveListView * categoryLiveListView;
	//已经加载的数量
	int categoryLiveListOffset = 0;
	//一次加载的数量
	int categoryLiveListLimit = 15;
	//加载分类列表，如果分类id列表未加载，则先加载分类id列表
	void reloadCategoryLiveList();
	//移除所有项目，根据当前分类id重新加载分类列表。
	void reloadCategoryLiveList_LoadLiveList();
	//显示分类列表界面
	void showCategoryListLayer();
	//分类列表是否已经加载，加载过了直接显示
	bool isCategoryLiveListLoaded = false;
	//显示分类列表的下一页
	void categoryLiveListViewNextPageCallback();
	//是否已经分类id列表已经加载
	bool isCategoryLoaded = false;
	//分类id列表
	std::vector<MenuDataItem> categorys;
	//当前分类列表id
	int currentCategory = 0;
	
	

	
	
};

#endif // __HELLOWORLD_SCENE_H__
