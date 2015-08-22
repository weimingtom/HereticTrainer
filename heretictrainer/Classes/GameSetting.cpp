#include"GameSetting.h"

GameSetting* GameSetting::instance = NULL;
 GameSetting*GameSetting::getInstance()
{
	if (instance == NULL)instance = new GameSetting();
	return instance;
}
GameSetting::GameSetting()
{
	fileNameMap["ring_normal"] = "live_ring_normal.png";
	fileNameMap["ring_sametime"] = "live_ring_sametime.png";
	fileNameMap["strip"] = "live_strip.png";
	fileNameMap["ring_tail"] = "live_ring_tail.png";
	judgeTimeTable[GameSetting::JUDGETIME_MISS] = 0.2;
	judgeTimeTable[GameSetting::JUDGETIME_BAD] = 0.1;
	judgeTimeTable[GameSetting::JUDGETIME_GOOD] = 0.075;
	judgeTimeTable[GameSetting::JUDGETIME_GREAT] = 0.028;
	speed = 1.6;
	targetPosition[0] = Vec2(89, 539);
	targetPosition[1] = Vec2(124, 364);
	targetPosition[2] = Vec2(220, 219);
	targetPosition[3] = Vec2(367, 122);
	targetPosition[4] = Vec2(539, 88);
	targetPosition[5] = Vec2(712, 122);
	targetPosition[6] = Vec2(858, 219);
	targetPosition[7] = Vec2(954, 364);
	targetPosition[8] = Vec2(989, 539);
	bornPosition = Vec2(539, 539);
}
 double GameSetting::getSpeed()
{
	return speed;
}
 void GameSetting::setSpeed(double speed)
{
	this->speed = speed;
}
 std::string GameSetting::getFileName(std::string name)
{
	return fileNameMap[name];
}
void GameSetting::changeFileName(std::string name, std::string fileName)
{
	fileNameMap[name] = fileName;
}
 double GameSetting::getJudgeTime(int type)
{
	return judgeTimeTable[type];
}
 Vec2 GameSetting::getBornPosition()
{
	return bornPosition;
}
 Vec2 GameSetting::getTargetPosition(int pos)
{
	return targetPosition[pos];
}