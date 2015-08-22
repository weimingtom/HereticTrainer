#ifndef __CROSSPLATFORMHELPER_CORE_H__
#define __CROSSPLATFORMHELPER_CORE_H__
#include"cocos2d.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string>
USING_NS_CC;
/*
一些跨平台帮助函数
*/
class CrossPlatformHelper
{
public:
	//获取下载文件，图片缓存目录的路径，默认会在sd根目录下创建heretictrainer文件夹
	static std::string getDownloadDirectory();
	//获取utf编码下的字符数
	static int getUtf8Length(std::string str);
	//utf编码的子串获取，获取start到end-1的子串
	static std::string subUtfString(std::string str, unsigned int start, unsigned int end);
	//返回一个处理过的字符串，str最多限制为maxLen长度，过长部分用...代替。
	static std::string limitString(std::string str, int maxLen);
};
#endif



