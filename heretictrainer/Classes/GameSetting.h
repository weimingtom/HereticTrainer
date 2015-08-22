#ifndef __GANESETTING_CORE_H__
#define __GANESETTING_CORE_H__
#include"cocos2d.h"
#include<string>
#include<map>
USING_NS_CC;
/*
游戏的配置类，单例，保存一些常量和配置。。

*/
class GameSetting
{
public:
	static const int JUDGETIME_MISS=0;
	static const int JUDGETIME_BAD = 1;
	static const int JUDGETIME_GOOD = 2;
	static const int JUDGETIME_GREAT = 3;
	//返回beat出生点
	Vec2 getBornPosition();
	//返回beat九个目标点
	Vec2 getTargetPosition(int pos);
	//根据名称返回一些文件名，主要便于管理，和动态替换纹理
	std::string  getFileName(std::string name);
	//返回判断时间阀值
	double getJudgeTime(int type);
	//返回live速度
	double getSpeed();
	//设置live速度
	void setSpeed(double speed);
	//改变文件名，用于动态替换该加载的纹理
	void changeFileName(std::string name, std::string fileName);
	GameSetting();
	//获取单例
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