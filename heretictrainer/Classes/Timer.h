#ifndef __TIMMER_CORE_H__
#define  __TIMMER_CORE_H__

#include"cocos2d.h"
USING_NS_CC;
#include <time.h>
class GameTimer
{
public:
	//设置当前时间为起始时间
	void init();
	//取得相对于起始时间的时间差，单位s

	double getTime();
	//暂停计时，请务必成对调用
	void pause();
	//恢复计时
	void resume();
	static GameTimer*getInstance();
private:
	static GameTimer*instance;
	clock_t beginTime = 0;
	clock_t pauseTime = 0;

};
#endif