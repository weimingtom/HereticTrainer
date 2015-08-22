#ifndef __CROSSPLATFORMHELPER_CORE_H__
#define __CROSSPLATFORMHELPER_CORE_H__
#include"cocos2d.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string>
USING_NS_CC;
/*
һЩ��ƽ̨��������
*/
class CrossPlatformHelper
{
public:
	//��ȡ�����ļ���ͼƬ����Ŀ¼��·����Ĭ�ϻ���sd��Ŀ¼�´���heretictrainer�ļ���
	static std::string getDownloadDirectory();
	//��ȡutf�����µ��ַ���
	static int getUtf8Length(std::string str);
	//utf������Ӵ���ȡ����ȡstart��end-1���Ӵ�
	static std::string subUtfString(std::string str, unsigned int start, unsigned int end);
	//����һ����������ַ�����str�������ΪmaxLen���ȣ�����������...���档
	static std::string limitString(std::string str, int maxLen);
};
#endif



