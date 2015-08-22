#ifndef __LIVELISTSCENE_SCENE_H__
#define __LIVELISTSCENE_SCENE_H__
#include "cocos2d.h"
#include"LiveListView.h"
#include"LLPMediator.h"
#include"MenuLayer.h"
USING_NS_CC;
/*
��ʾlive�б�֧����llp��վͨѶ��ȡ���ݲ�����ʾ

*/
class LiveListScene : public cocos2d::Layer
{
public:
	static LiveListScene*create();
	static Scene* createScene();
	virtual bool init();
private:
	//llpͨѶ��
	LLPMediator *llp;
	//�������
	Node *sidebarNode;
	bool isSidebarShowed = false;
	//��ʾ���������ʾ��������ֶ���
	void showSidebar();
	//���ز��������ʾ�������ʧ����
	void hideSidebar();
	//ֱ�����ز��������ʾ����
	void resetSidebar();
	//һ���ص��������û������һ��live��ʱ�򱻵���
	void LoadLiveDetailsCallback(LiveListItem item);

	/////////////////////////public LiveList/////////////////////////
	//�����б��
	Node *publicListNode;
	//�����б���listView
	LiveListView * publicLiveListView;
	//һ�εļ�������
	int publicLiveListLimit = 15;
	//�Ѿ����ص�����
	int publicLiveListOffset = 0;
	//�Ƴ�������Ŀ�����¼��������б�listView
	void reloadPublicLiveList();
	//�Ƿ������б��Ѿ������ع������ع���ֱ����ʾ
	bool isPublicLiveListLoaded = false;
	//��ʾ�����б�
	void showPublicListLayer();
	//һ���ص������������б���һҳ
	void publicLiveListViewNextPageCallback();
	/////////////////////////search /////////////////////////////////
	//���������
	Node *searchNode;
	//���������listView
	LiveListView *searchLiveListView;
	//һ�μ��ص�����
	int searchLiveListLimit = 15;
	//�Ѿ����ص�����
	int searchLiveListOffset = 0;
	//�Ƴ�������Ŀ������һ��������keyword�ǹؼ���
	void search(std::string _keyword);
	//��ǰ�ؼ���
	std::string keyword;
	//��ʾ������
	void showSearchListLayer();
	//һ���ص������������б����һҳ
	void searchLiveListViewNextPageCallback();
	/////////////////////////favorite////////////////////////////////
	//�ղ��б��
	Node *favoriteNode;
	//�ղ��б���listView
	LiveListView *favoriteLiveListView;
	//һ�μ��ص�����
	int favoriteLiveListLimit = 15;
	//�Ѿ����ص�����
	int favoriteLiveListOffset = 0;
	//�Ƿ��ղ��б��Ѿ����ع��ˣ����ع���ֱ����ʾ
	bool isFavoriteLiveListLoaded = false;
	//�Ƴ�������Ŀ�����¼����ղ��б�
	void reloadFavoriteLiveList();
	//��ʾ�ղ��б��
	void showFavoriteListLayer();
	//һ���ص�����ʾ�ղ��б����һҳ
	void favoriteLiveListViewNextPageCallback();
	/////////////////////////category LiveList///////////////////////
	//�����б��
	Node *categoryListNode;
	//�����б���listView
	LiveListView * categoryLiveListView;
	//�Ѿ����ص�����
	int categoryLiveListOffset = 0;
	//һ�μ��ص�����
	int categoryLiveListLimit = 15;
	//���ط����б��������id�б�δ���أ����ȼ��ط���id�б�
	void reloadCategoryLiveList();
	//�Ƴ�������Ŀ�����ݵ�ǰ����id���¼��ط����б�
	void reloadCategoryLiveList_LoadLiveList();
	//��ʾ�����б����
	void showCategoryListLayer();
	//�����б��Ƿ��Ѿ����أ����ع���ֱ����ʾ
	bool isCategoryLiveListLoaded = false;
	//��ʾ�����б����һҳ
	void categoryLiveListViewNextPageCallback();
	//�Ƿ��Ѿ�����id�б��Ѿ�����
	bool isCategoryLoaded = false;
	//����id�б�
	std::vector<MenuDataItem> categorys;
	//��ǰ�����б�id
	int currentCategory = 0;
	
	

	
	
};

#endif // __HELLOWORLD_SCENE_H__
