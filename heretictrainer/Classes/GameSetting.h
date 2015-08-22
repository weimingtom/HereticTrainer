#ifndef __GANESETTING_CORE_H__
#define __GANESETTING_CORE_H__
#include"cocos2d.h"
#include<string>
#include<map>
USING_NS_CC;
/*
��Ϸ�������࣬����������һЩ���������á���

*/
class GameSetting
{
public:
	static const int JUDGETIME_MISS=0;
	static const int JUDGETIME_BAD = 1;
	static const int JUDGETIME_GOOD = 2;
	static const int JUDGETIME_GREAT = 3;
	//����beat������
	Vec2 getBornPosition();
	//����beat�Ÿ�Ŀ���
	Vec2 getTargetPosition(int pos);
	//�������Ʒ���һЩ�ļ�������Ҫ���ڹ����Ͷ�̬�滻����
	std::string  getFileName(std::string name);
	//�����ж�ʱ�䷧ֵ
	double getJudgeTime(int type);
	//����live�ٶ�
	double getSpeed();
	//����live�ٶ�
	void setSpeed(double speed);
	//�ı��ļ��������ڶ�̬�滻�ü��ص�����
	void changeFileName(std::string name, std::string fileName);
	GameSetting();
	//��ȡ����
	 static GameSetting*getInstance();
private:
	double speed;
	static GameSetting*instance;
	std::map<std::string, std::string> fileNameMap;
	double judgeTimeTable[5];
	Vec2 targetPosition[9];
	Vec2 bornPosition;
};
#endif