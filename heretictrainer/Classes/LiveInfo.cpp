#include"LiveInfo.h"
#include"cocos2d.h"
USING_NS_CC;
Beat::Beat(){ this->type = 0; this->beginTime = 0; };
Beat::Beat(int type, int pos, double beginTime)
{
	this->pos = pos;
	this->type = type;
	this->beginTime = beginTime;
	this->endTime = 0;
};
Beat::Beat(int type, int pos, double beginTime, double endTime)
{
	this->pos = pos;
	this->type = type;
	this->beginTime = beginTime;
	this->endTime = endTime;

}
bool Beat::operator<(const Beat&that) const
{
	return this->beginTime < that.beginTime;
}
void Beat::log()
{
	if (type | Beat::TYPE_LONG)
		cocos2d::log("Beat %lf %lf", beginTime, endTime);
	else
		cocos2d::log("Beat %lf", beginTime);
}