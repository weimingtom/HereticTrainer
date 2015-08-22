#ifndef __TIMMER_CORE_H__
#define  __TIMMER_CORE_H__

#include"cocos2d.h"
USING_NS_CC;
#include <time.h>
class GameTimer
{
public:
	//���õ�ǰʱ��Ϊ��ʼʱ��
	void init();
	//ȡ���������ʼʱ���ʱ����λs

	double getTime();
	//��ͣ��ʱ������سɶԵ���
	void pause();
	//�ָ���ʱ
	void resume();
	static GameTimer*getInstance();
private:
	static GameTimer*instance;
	clock_t beginTime = 0;
	clock_t pauseTime = 0;

};
#endif