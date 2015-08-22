/*
���ܣ����飬����beat��ͷβԲ�����Ǹ�����
*/
#ifndef __STRIPSPRITE_VIEW_H__
#define __STRIPSPRITE_VIEW_H__
//�����chao�����Ķ���=��=
#include "cocos2d.h"
USING_NS_CC;
//��ʾlong beat�İ�ɫ��״����
class StripSprite : public Sprite
{
public:
	//ͨ��ͷβ����Բ�ξ��鴴��
	static StripSprite *create(Sprite * headring, Sprite *tailring);
	//ͨ��ͷβ����Բ�ξ��������״
	void updatePosition();



private:
	/*
	* �����ĸ���������꣬����ͼ��״
	* @param pTL ���ϽǶ�������
	* @param pBL ���½Ƕ�������
	* @param pTR ���ϽǶ�������
	* @param pBR ���½Ƕ�������
	*/
	void setVertex(const Vec2& pTL, const Vec2& pBL, const Vec2& pTR, const Vec2& pBR);
	void setDisplayFrameWithAnimationName(const std::string &  animationName, ssize_t  frameIndex)
	{
		Sprite::setDisplayFrameWithAnimationName(animationName, frameIndex);
	}

	bool initWithFile(const std::string& filename);
	Sprite *headRing;
	Sprite *tailRing;
	StripSprite(){}
};

#endif