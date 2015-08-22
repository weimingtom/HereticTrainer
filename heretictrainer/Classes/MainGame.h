#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include "cocos2d.h"
#include"LiveInfo.h"
#include"BeatObject.h"
#include"Timer.h"
#include<map>
#include<vector>
USING_NS_CC;
class MainGame : public cocos2d::Layer
{
public:
	static MainGame*create(LiveInfo liveInfo);
	static Scene* createScene(LiveInfo liveInfo);
	virtual bool init(LiveInfo liveInfo);
private:
	void createScoreSprite();
	void createTouchLayer();
	void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	void showScoreEffect(Score score);//播放打击评分动画和声音
	void showPressEffect(int pos);
	bool checkTouch(int pos, const Vec2 &touchLocation);
	//评分显示用精灵
	Sprite *perfectSprite;
	Sprite *greatSprite;
	Sprite *goodSprite;
	Sprite *badSprite;
	Sprite *missSprite;
	LiveInfo liveInfo;
	//combo显示用label
	Label* comboLabel;
	Label* comboCountLabel;
	void createBeatObjects();
	std::vector<BeatObject *> (beats[9]);
	void startGame();
	void updateBeatObjects(float t);
	GameTimer *timer;
	int judgingIndexs[9];
	int touchingIndexs[9];
	std::map<cocos2d::Touch*, BeatObject*> touchMap;
	int comboCount = -1;
	int totalComboCount = 0;
	int mcomboCount = 0;
	int perfectCount = 0;
	int greatCount = 0;
	int goodCount = 0;
	int badCount = 0;
	int missCount = 0;
	void Count(Score score, bool isCountCombo);
	void showComboCountEffect(int cnt);

	void endGame();


};
#endif