/*
功能：精灵，长型beat，头尾圆环间那个长条
*/
#ifndef __STRIPSPRITE_VIEW_H__
#define __STRIPSPRITE_VIEW_H__
//借鉴（chao）来的东西=。=
#include "cocos2d.h"
USING_NS_CC;
//表示long beat的白色带状精灵
class StripSprite : public Sprite
{
public:
	//通过头尾两个圆形精灵创建
	static StripSprite *create(Sprite * headring, Sprite *tailring);
	//通过头尾两个圆形精灵更新形状
	void updatePosition();



private:
	/*
	* 设置四个顶点的坐标，即贴图形状
	* @param pTL 左上角顶点坐标
	* @param pBL 左下角顶点坐标
	* @param pTR 右上角顶点坐标
	* @param pBR 右下角顶点坐标
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