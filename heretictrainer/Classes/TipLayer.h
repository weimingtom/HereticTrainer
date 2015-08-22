#ifndef _TIPLAYER_LAYER_H_
#define _TIPLAYER_LAYER_H_


#include"cocos2d.h"
#include<string>
USING_NS_CC;

class TipLayer :public Layer
{
public:
	static TipLayer* create(std::string tipText,float fontSize);
	bool init(std::string tipText, float fontSize);
};



#endif