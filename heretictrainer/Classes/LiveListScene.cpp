#include"LiveListScene.h"
#include"ui/CocosGUI.h"
#include"CocosHelper.h"
#include"TipLayer.h"
#include "cocostudio/CocoStudio.h"
#include"LoadingLayer.h"
#include"LLPMediator.h"
#include"AboutScene.h"
#include"SettingScene.h"
#include"LocalScene.h"
#include"RegisterScene.h"
#include"LiveDetailsScene.h"
using namespace ui;
LiveListScene* LiveListScene::create()
{

	LiveListScene *pRet = new(std::nothrow)LiveListScene();
	if (pRet && pRet->init())
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
Scene* LiveListScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LiveListScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
void LiveListScene::showSidebar()
{
	if (isSidebarShowed)return;

	sidebarNode->stopAllActions();
	publicListNode->stopAllActions();
	categoryListNode->stopAllActions();
	searchNode->stopAllActions();
	favoriteNode->stopAllActions();
	
	sidebarNode->runAction(MoveTo::create(0.3, Vec2(0, 0)));
	publicListNode->runAction(MoveTo::create(0.3, Vec2(398, 0)));
	categoryListNode->runAction(MoveTo::create(0.3, Vec2(398, 0)));
	searchNode->runAction(MoveTo::create(0.3, Vec2(398, 0)));
	favoriteNode->runAction(MoveTo::create(0.3, Vec2(398, 0)));
	isSidebarShowed = true;
}
void  LiveListScene::hideSidebar()
{
	if (!isSidebarShowed)return;
	sidebarNode->stopAllActions();
	publicListNode->stopAllActions();
	categoryListNode->stopAllActions();
	searchNode->stopAllActions();
	favoriteNode->stopAllActions();
	sidebarNode->runAction(MoveTo::create(0.3, Vec2(-398, 0)));
	publicListNode->runAction(MoveTo::create(0.3, Vec2(0, 0)));
	categoryListNode->runAction(MoveTo::create(0.3, Vec2(0, 0)));
	searchNode->runAction(MoveTo::create(0.3, Vec2(0, 0)));
	favoriteNode->runAction(MoveTo::create(0.3, Vec2(0, 0)));
	isSidebarShowed = false;

}
void  LiveListScene::resetSidebar()
{
	sidebarNode->setPosition(Vec2(-398, 0));
	publicListNode->setPosition(Vec2(0, 0));
	categoryListNode->setPosition(Vec2(0, 0));
	searchNode->setPosition(Vec2(0, 0));
	favoriteNode->setPosition(Vec2(0, 0));
}
void LiveListScene::categoryLiveListViewNextPageCallback()
{
	//�����δ���ع���ֱ�ӷ���
	if (!isCategoryLiveListLoaded)return;

	llp->loadLiveList_Category(currentCategory, categoryLiveListOffset, categoryLiveListLimit);
	//���ض�����
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);
	//����һ��ѭ��������Ƿ��Ѿ���������
	this->schedule([loadingLayer, this](float t)
	{
		//�Ƿ�������
		if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			//�Ƴ����ض�����
			loadingLayer->removeFromParent();
			//ֹͣѭ��
			this->unschedule("categoryLiveListViewNextPageCallback");
			//�Ƿ���سɹ�
			if (llp->isLoadLiveListSuccessed())
			{
				auto list = llp->getLiveList();
				//���������1���Լ�����
				if (list.items.size())
				{

					categoryLiveListOffset += list.items.size();
					
					categoryLiveListView->addItems(list);
					isCategoryLiveListLoaded = true;
				}
			}
			
		}
	}, "categoryLiveListViewNextPageCallback");

}
void LiveListScene::favoriteLiveListViewNextPageCallback()
{
	//���δ��¼����Ȼ�޷���ȡ�ղ��б�ֱ�ӷ���
	if (!llp->isLogined())return;
	//����Ѿ����ع��ˣ����Լ�����һҳ����������categoryLiveListViewNextPageCallback
	if (isFavoriteLiveListLoaded)
	{

		llp->loadLiveList_Favorites(favoriteLiveListOffset,favoriteLiveListLimit);
		auto loadingLayer = LoadingLayer::create();
		addChild(loadingLayer, 30);
		this->schedule([loadingLayer, this](float t)
		{
			if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
			{
				loadingLayer->removeFromParent();
				this->unschedule("loadFavoriteLiveListNextPage");
				if (llp->isLoadLiveListSuccessed())
				{
					auto list = llp->getLiveList();
					if (list.items.size())
					{
						favoriteLiveListOffset+= list.items.size();

						favoriteLiveListView->addItems(list);
					}

				}

			}
		}, "loadFavoriteLiveListNextPage");
	}
}
void LiveListScene::searchLiveListViewNextPageCallback()
{

	//����categoryLiveListViewNextPageCallback
		llp->loadLiveList_Search(keyword,publicLiveListOffset, publicLiveListLimit);
		auto loadingLayer = LoadingLayer::create();
		addChild(loadingLayer, 30);
		this->schedule([loadingLayer, this](float t)
		{
			
			if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
			{
				loadingLayer->removeFromParent();
				this->unschedule("loadsearchLiveListNextPage");
				if (llp->isLoadLiveListSuccessed())
				{
					auto list = llp->getLiveList();
					searchLiveListOffset += list.items.size();

					searchLiveListView->addItems(list);

				}

			}
		}, "loadsearchLiveListNextPage");
	
}
void LiveListScene::publicLiveListViewNextPageCallback()
{
	//����categoryLiveListViewNextPageCallback
	if (isPublicLiveListLoaded)
	{

		llp->loadLiveList_Public(publicLiveListOffset, publicLiveListLimit);
		auto loadingLayer = LoadingLayer::create();
		addChild(loadingLayer, 30);
		this->schedule([loadingLayer, this](float t)
		{
			if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
			{
				loadingLayer->removeFromParent();
				this->unschedule("loadPublicLiveListNextPage");
				if (llp->isLoadLiveListSuccessed())
				{
					auto list = llp->getLiveList();
					if (list.items.size())
					{
						publicLiveListOffset += list.items.size();

						publicLiveListView->addItems(list);
					}

				}

			}
		}, "loadPublicLiveListNextPage");
	}
}
void LiveListScene::showPublicListLayer()
{
	publicListNode->setVisible(true);
	categoryListNode->setVisible(false);
	searchNode->setVisible(false);
	favoriteNode->setVisible(false);
	if (!isPublicLiveListLoaded)reloadPublicLiveList();
}
void  LiveListScene::showCategoryListLayer()
{
	publicListNode->setVisible(false);
	categoryListNode->setVisible(true);
	searchNode->setVisible(false);
	favoriteNode->setVisible(false);
	if (!isCategoryLiveListLoaded)reloadCategoryLiveList();
}
void  LiveListScene::showFavoriteListLayer()
{
	publicListNode->setVisible(false);
	categoryListNode->setVisible(false);
	searchNode->setVisible(false);
	favoriteNode->setVisible(true);
	if (!isFavoriteLiveListLoaded)reloadFavoriteLiveList();
}
void  LiveListScene::showSearchListLayer()
{
	publicListNode->setVisible(false);
	categoryListNode->setVisible(false);
	searchNode->setVisible(true);
	favoriteNode->setVisible(false);

}
void   LiveListScene::search(std::string _keyword)
{
	//���ص���ʾ�޷����ӷ������Ĳ�

	((ui::Layout*)seekNodeByName(searchNode, "panel_cannot_connert_server"))->setVisible(false);
	//�����Ѿ���������
	searchLiveListOffset = 0;
	//�����Ŀ
	searchLiveListView->removeAllItems();
	llp->loadLiveList_Search(_keyword, searchLiveListOffset, searchLiveListLimit);
	keyword = _keyword;
	//���ض�����
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);
	//����һ��ѭ��������Ƿ�������
	this->schedule([loadingLayer, this](float t)
	{
		if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			//�Ƴ����ض�����
			loadingLayer->removeFromParent();
			//ֹͣѭ��
			this->unschedule("search");
			//�Ƿ���سɹ�
			if (llp->isLoadLiveListSuccessed())
			{
				auto list = llp->getLiveList();
				//�Ƿ����0������
				if (list.items.size())
				{
					searchLiveListOffset += list.items.size();

					searchLiveListView->addItems(list);
				}
				
			}
			else ((ui::Layout*)seekNodeByName(searchNode, "panel_cannot_connert_server"))->setVisible(true);
		}
	}, "search");

}
void LiveListScene::reloadPublicLiveList()
{
	//����void   LiveListScene::search(std::string _keyword)
	((ui::Layout*)seekNodeByName(publicListNode, "panel_cannot_connert_server"))->setVisible(false);
	publicLiveListOffset = 0;
	isPublicLiveListLoaded = false;
	publicLiveListView->removeAllItems();
	llp->loadLiveList_Public(publicLiveListOffset, publicLiveListLimit);
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);
	this->schedule([loadingLayer,this](float t)
	{
		if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			loadingLayer->removeFromParent();
			this->unschedule("reloadPublicLiveList");
			if (llp->isLoadLiveListSuccessed())
			{
				auto list = llp->getLiveList();
				if (list.items.size())
				{

					publicLiveListOffset += list.items.size();

					publicLiveListView->addItems(list);
					isPublicLiveListLoaded = true;
				}
			}
			else ((ui::Layout*)seekNodeByName(publicListNode, "panel_cannot_connert_server"))->setVisible(true);
		}
	}, "reloadPublicLiveList");

}
void LiveListScene::reloadCategoryLiveList()
{
	//����void   LiveListScene::search(std::string _keyword)

	((ui::Layout*)seekNodeByName(categoryListNode, "panel_cannot_connert_server"))->setVisible(false);
	//�����з���id���ȼ�����id�б��Ƿ��Ѿ�����
	if (!isCategoryLoaded)
	{
		llp->loadCategory();

		auto loadingLayer = LoadingLayer::create();
		addChild(loadingLayer, 30);
		this->schedule([loadingLayer, this](float t)
		{
			
			if (llp->getLoadCategoryConnertState() != llp->CONNERTSTATE_CONNERTING)
			{
				
				loadingLayer->removeFromParent();
				this->unschedule("loadCategory");
				if (llp->isLoadCategorySuccessed())
				{
					
					auto tmp = llp->getCategorys();
					if (tmp.size())
					{
						isCategoryLoaded = true;
						categorys.clear();
						for (int i = 0; i < tmp.size(); i++)
						{
							categorys.push_back(MenuDataItem(tmp[i].name, tmp[i].id));
						}
						currentCategory = categorys[0].userData;
						reloadCategoryLiveList_LoadLiveList();
					}
					else  ((ui::Layout*)seekNodeByName(categoryListNode, "panel_cannot_connert_server"))->setVisible(true);
					
				}
				else ((ui::Layout*)seekNodeByName(categoryListNode, "panel_cannot_connert_server"))->setVisible(true);
			}
		}, "loadCategory");

	}
	else reloadCategoryLiveList_LoadLiveList();
}
void LiveListScene::reloadCategoryLiveList_LoadLiveList()
{

	//����void   LiveListScene::search(std::string _keyword)
	categoryLiveListOffset = 0;
	isCategoryLiveListLoaded = false;
	categoryLiveListView->removeAllItems();
	llp->loadLiveList_Category(currentCategory, categoryLiveListOffset, categoryLiveListLimit);
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);

	this->schedule([loadingLayer, this](float t)
	{
		if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			loadingLayer->removeFromParent();
			this->unschedule("reloadCategoryLiveList_LoadLiveList");
			if (llp->isLoadLiveListSuccessed())
			{
				auto list = llp->getLiveList();
				if (list.items.size())
				{

					categoryLiveListOffset += list.items.size();

					categoryLiveListView->addItems(list);
					isCategoryLiveListLoaded = true;
				}
			}
			else ((ui::Layout*)seekNodeByName(favoriteNode, "panel_cannot_connert_server"))->setVisible(true);
		}
	}, "reloadCategoryLiveList_LoadLiveList");

}
void LiveListScene::reloadFavoriteLiveList()
{
	//δ��¼��������б�
	if (!llp->isLogined())return;
	//��������void   LiveListScene::search(std::string _keyword)
	((ui::Layout*)seekNodeByName(favoriteNode, "panel_cannot_connert_server"))->setVisible(false);
	favoriteLiveListOffset = 0;
	isFavoriteLiveListLoaded = false;
	favoriteLiveListView->removeAllItems();
	llp->loadLiveList_Favorites(favoriteLiveListOffset, favoriteLiveListLimit);
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);
	this->schedule([loadingLayer, this](float t)
	{
		if (llp->getLoadLiveListConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			loadingLayer->removeFromParent();
			this->unschedule("reloadFavoriteLiveList");
			if (llp->isLoadLiveListSuccessed())
			{
				auto list = llp->getLiveList();
				if (list.items.size())
				{

					favoriteLiveListOffset+= list.items.size();

					favoriteLiveListView->addItems(list);
					isFavoriteLiveListLoaded = true;
				}
			}
			else ((ui::Layout*)seekNodeByName(favoriteNode, "panel_cannot_connert_server"))->setVisible(true);
		}
	}, "reloadFavoriteLiveList");
}
void LiveListScene::LoadLiveDetailsCallback(LiveListItem item)
{
	//�û������live����ʼ����live���飬
	llp->loadLiveDetails(item.live_id);
	//���ض�����
	auto loadingLayer = LoadingLayer::create();
	addChild(loadingLayer, 30);
	this->schedule([loadingLayer, this](float t)
	{
		//�Ƿ�������
		if (llp->getLoadLiveDetailsConnertState() != llp->CONNERTSTATE_CONNERTING)
		{
			//�Ƴ����ض�����
			loadingLayer->removeFromParent();
			//ֹͣѭ��
			this->unschedule("LoadLiveDetailsCallback");
			//�Ƿ���سɹ�
			if (llp->isLoadLiveDetailsSuccessed())
			{
				//����live�������
				auto liveDetails = llp->getLiveDetails();
				auto scene = LiveDetailsScene::createScene(liveDetails);
				Director::getInstance()->pushScene(scene);
			}
		
		}
	}, "LoadLiveDetailsCallback");

}
bool LiveListScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	llp = LLPMediator::getInstance();
	//���ز����ļ�����ϸ��cocos studio
	auto rootNode = CSLoader::createNode("LiveList.csb");
	addChild(rootNode);
	sidebarNode = seekNodeByName(rootNode, "sidebarLayer");
	publicListNode = seekNodeByName(rootNode, "publicListLayer");
	categoryListNode = seekNodeByName(rootNode, "categoryListLayer");
	searchNode = seekNodeByName(rootNode, "searchLayer");
	favoriteNode = seekNodeByName(rootNode, "favoriteLayer");





	//һЩlistView�Ĵ��������ڲ��Ǳ�׼�ؼ���ֻ���ֹ��������Ҳ��֡�
	categoryLiveListView = LiveListView::create(std::bind(&LiveListScene::LoadLiveDetailsCallback, this, std::placeholders::_1)
		, std::bind(&LiveListScene::categoryLiveListViewNextPageCallback,this));
	categoryListNode->addChild(categoryLiveListView, 10);
	categoryLiveListView->setPosition(Vec2(0, 0));
	categoryLiveListView->setContentSize(Size(1080, 720 - 64));
	categoryLiveListView->setAnchorPoint(Vec2(0, 0));

	publicLiveListView = LiveListView::create(std::bind(&LiveListScene::LoadLiveDetailsCallback, this, std::placeholders::_1)
		, std::bind(&LiveListScene::publicLiveListViewNextPageCallback, this));

	publicListNode->addChild(publicLiveListView,10);
	publicLiveListView->setPosition(Vec2(0, 0));
	publicLiveListView->setContentSize(Size(1080, 720 - 64));
	publicLiveListView->setAnchorPoint(Vec2(0, 0));

	searchLiveListView = LiveListView::create(std::bind(&LiveListScene::LoadLiveDetailsCallback, this, std::placeholders::_1)
		, std::bind(&LiveListScene::searchLiveListViewNextPageCallback, this));

	searchNode->addChild(searchLiveListView, 10);
	searchLiveListView->setPosition(Vec2(0, 0));
	searchLiveListView->setContentSize(Size(1080,550));
	searchLiveListView->setAnchorPoint(Vec2(0, 0));

	favoriteLiveListView = LiveListView::create(std::bind(&LiveListScene::LoadLiveDetailsCallback, this, std::placeholders::_1)
		, std::bind(&LiveListScene::favoriteLiveListViewNextPageCallback, this));

	favoriteNode->addChild(favoriteLiveListView, 10);
	favoriteLiveListView->setPosition(Vec2(0, 0));
	favoriteLiveListView->setContentSize(Size(1080, 720 - 64));
	favoriteLiveListView->setAnchorPoint(Vec2(0, 0));

	//������ť�¼�
	((ui::Button*)seekNodeByName(rootNode, "button_search"))->addTouchEventListener([this, rootNode](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

			auto str = ((ui::TextField*)seekNodeByName(rootNode, "textfiled_search"))->getString();
			//log(str.c_str());
			//�ؼ��ʲ���Ϊ��
			if (str.size())
			search(str);
		}
	});
	//�����б�˵���ť���¼�
	((ui::Button*)seekNodeByName(categoryListNode, "button_categoryList_menu"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (categorys.size())
			{
				//��ʾ�˵�
				auto menu=MenuLayer::create( [this](MenuDataItem item)
				{
					currentCategory = item.userData;
					reloadCategoryLiveList();
				},this);
				menu->setItems(categorys, Vec2(1064,648));
				//addChild(menu,50);

			}

		}
	});
	//����������ƻ�����֧�ֲ�
	auto sideBarTouchHelperLayout = (ui::Layout*)seekNodeByName(sidebarNode, "layout_touchHelper");
	sideBarTouchHelperLayout->setSwallowTouches(false);
	sideBarTouchHelperLayout->addTouchEventListener([sideBarTouchHelperLayout,this](Ref*ref, Widget::TouchEventType type)
	{
		if (isSidebarShowed)
		{
			hideSidebar();
			return;
		}
		if (type == Widget::TouchEventType::ENDED)
		{
			
			if (!isSidebarShowed)
			{
				//�򵥵����Ƶ�ʶ��
				auto endPosition = sideBarTouchHelperLayout->getTouchEndPosition();
				auto beganPosition = sideBarTouchHelperLayout->getTouchBeganPosition();
				float angle = (endPosition - beganPosition).getAngle();

				if (fabs(angle) <= acos(-1) / 4 && beganPosition.x<(1080 / 4) && endPosition.x>(1080 / 4))
				{
					showSidebar();
				}
			}
			
		
		}
	});
	//�������ť���¼����
	((ui::Button*)seekNodeByName(sidebarNode, "button_user"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

		}
	});
	((ui::Button*)seekNodeByName(favoriteNode, "button_reload"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			reloadFavoriteLiveList();
		}
	});
	((ui::Button*)seekNodeByName(publicListNode, "button_reload"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			reloadPublicLiveList();
		}
	});
	((ui::Button*)seekNodeByName(categoryListNode, "button_reload"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			reloadCategoryLiveList();
		}
	});
	((ui::Button*)seekNodeByName(favoriteNode, "button_sidebar"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (!isSidebarShowed)
			showSidebar();
		}
	});
	((ui::Button*)seekNodeByName(publicListNode, "button_sidebar"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (!isSidebarShowed)
			showSidebar();
		}
	});
	((ui::Button*)seekNodeByName(categoryListNode, "button_sidebar"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (!isSidebarShowed)
			showSidebar();
		}
	});
	((ui::Button*)seekNodeByName(searchNode, "button_sidebar"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (!isSidebarShowed)
			showSidebar();
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_categorylist"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			showCategoryListLayer();
			hideSidebar();
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_publiclist"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			showPublicListLayer();
			hideSidebar();
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_favorite"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			showFavoriteListLayer();
			hideSidebar();
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_search"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			showSearchListLayer();
			hideSidebar();

		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_local"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			resetSidebar();
			auto scene = LocalScene::createScene();
			Director::getInstance()->pushScene(scene);
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_setting"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			resetSidebar();
			auto scene = SettingScene::createScene();
			Director::getInstance()->pushScene(scene);
		}
	});
	((ui::Button*)seekNodeByName(sidebarNode, "button_about"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			resetSidebar();
			auto scene = AboutScene::createScene();
			Director::getInstance()->pushScene(scene);
		}
	});

	((ui::Button*)seekNodeByName(sidebarNode, "button_exit"))->addTouchEventListener([this](Ref*ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
		}
	});





	//showCategoryListLayer();
	//���Ĭ����ʾ�����б�
	showPublicListLayer();
	return true;

}