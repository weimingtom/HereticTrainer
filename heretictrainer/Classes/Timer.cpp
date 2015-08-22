#include"Timer.h"
double GameTimer::getTime()
{
	return (double)(clock() - beginTime) / CLOCKS_PER_SEC;
}
void GameTimer::init()
{
	beginTime = pauseTime = clock();
}
void GameTimer::pause()
{
	pauseTime = clock();
}
void GameTimer::resume()
{
	beginTime += clock() - pauseTime;
	pauseTime = beginTime;
}
GameTimer* GameTimer::instance = NULL;
GameTimer*GameTimer::getInstance()
{
	if (!instance)instance = new GameTimer();
	return instance;
}