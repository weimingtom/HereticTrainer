#ifndef __BEATOBJECT_VIEW_H__
#define __BEATOBJECT_VIEW_H__
#include"cocos2d.h"
#include"StripSprite.h"
#include"LiveInfo.h"
#include"GameSetting.h"
USING_NS_CC;
/*
游戏精灵，代表一个beat
该对象本身是一个Node
管理3个子节点，		
Sprite* headRingSprite;//头圆环
Sprite * tailRingSprite;//尾圆环
StripSprite *stripSprite;//带状精灵

updateState(double t)应该每一帧被调用，更新状态。
类似状态机机制，存在4个状态
初始是STATE_BEGIN，不显示，位于出生点，如果到达出现时间则转换为STATE_HEAD_RUNNING状态
STATE_HEAD_RUNNING 显示，并且头部圆环更新位置，当然，如果尾部圆环也到达出现时间，也进行位置更新。如果是长型beat，正常触摸后会进入STATE_TAIL_RUNNING状态，否则miss进入STATE_END
STATE_TAIL_RUNNING 仅存在于长型beat中，头部圆环固定在目标点，尾部圆环运动，正常触摸或者miss后进入STATE_END状态
STATE_END 终止状态，不显示

触摸事件通过int touchBegin(double t)传递，
int touchBegin(double t)有3种返回值，返回1表示，当前beat已经被判定，该次触摸事件应当传递给下一个beat，返回-1表示还未到可以触摸的事件，应当忽略本次触摸，返回0表示该次触摸被接受，并已经产生判定结果。
bool touchEnd(double t) 也有返回值，返回真表示该次触摸结束事件应当被忽略，返回真表示该触摸被接受，并且已经产生判定。

对于判定，与原实现不同
然后通过每一帧调用
Score getHeadScore();
Score getTailScore();
获取评价情况，并显示他，并且统计，这里如果同一帧内出现需要显示多种评价情况的时候只显示一种，当然统计正常，减少音效函数的调用，保证每一帧最多调用一次。
void headScoreShowed();tailScoreShowed()标记为已经显示状态，便于在下次忽略他

*/
class BeatObject:public Node
{
public:
	//状态，详细见上说明
	static const int STATE_BEGIN=0;
	
	static const int STATE_HEAD_RUNNING = 1;
	//static const int STATE_HEAD_JUDGEING = 2;
	static const int STATE_TAIL_RUNNING = 3;
	//static const int STATE_TAIL_JUDGEING = 4;
	static const int STATE_END = 5;

	static BeatObject*create(Beat beat);
	bool init( Beat beat);

	//更新beatObject状态，t传递当前时间
	void updateState(double t);
	//传递触摸开始时间，t传递当前时间，有3种返回值，返回1表示，当前beat已经被判定，该次触摸事件应当传递给下一个beat，
	//返回-1表示还未到可以触摸的事件，应当忽略本次触摸，返回0表示该次触摸被接受，并已经产生判定结果。
	int touchBegin(double t);
	//传递触摸结束时间，t传递当前时间，返回值，返回真表示该次触摸结束事件应当被忽略，返回真表示该触摸被接受，并且已经产生判定。
	bool touchEnd(double t);
	
	//获取该beat的类型
	int getType();
	//获取头评价情况，None未评价，Showed 已经显示过了
	Score getHeadScore();
	//标记头部评价为已经显示，showed
	void headScoreShowed();
	//获取尾评价情况，None未评价，Showed 已经显示过了
	Score getTailScore();
	//获取该beat处于哪一个道
	int getPos();
	//标记尾部评价为已经显示，showed
	void tailScoreShowed();
private:
	
	int type;
	int pos;
	Score headResult;
	Score tailResult;
	//头部出现时间
	double headAppearTime;
	//头部到达目标点时间
	double headArriveTime;
	//头部消失时间，即miss时间
	double headDisappearTime;
	//尾部出现时间
	double tailAppearTime;
	//尾部到达目标点时间
	double tailArriveTime;
	//尾部消失时间，即miss时间
	double tailDisappearTime;
	int state;
	Sprite* headRingSprite;
	Sprite * tailRingSprite;
	StripSprite *stripSprite;
	//更新beat位置
	void updatePosition(double t);

	
};
#endif