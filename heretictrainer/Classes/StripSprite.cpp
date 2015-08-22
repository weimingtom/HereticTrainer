#include"StripSprite.h"
#include<algorithm>
#include"GameSetting.h"
StripSprite* StripSprite::create(Sprite * headring, Sprite *tailring)
{
	auto ret = new StripSprite();

	if (ret->initWithFile(GameSetting::getInstance()->getFileName("strip")))
	{
		ret->autorelease();
		ret->setAnchorPoint(Vec2(0, 0));
		ret->headRing = headring;
		ret->tailRing = tailring;
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}


bool StripSprite::initWithFile(const std::string& filename)
{
	return Sprite::initWithFile(filename);
}

void StripSprite::updatePosition()
{
	double x1 = tailRing->getPositionX();//根据两圆环确定梯形的4个点
	double y1 = tailRing->getPositionY();
	double x2 = headRing->getPositionX();
	double y2 = headRing->getPositionY();
	//两圆缩放后半径
	double R1 = tailRing->getScale() * 62;
	double R2 = headRing->getScale() * 62;
	//两圆距离
	double dis = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	//巴拉巴拉的一串计算，说不明白，画下图你就懂。。
	double Sin = (x1 - x2) / dis;
	double Cos = (y1 - y2) / dis;
	setVertex(
		Vec2(x1 - R1*Cos, y1 + R1*Sin)//左上角
		, Vec2(x2 - R2*Cos, y2 + R2*Sin)//左下角
		, Vec2(x1 + R1*Cos, y1 - R1*Sin)//右上角
		, Vec2(x2 + R2*Cos, y2 - R2*Sin)//右下角


		);


}
void StripSprite::setVertex(const Vec2& pTL, const Vec2& pBL, const Vec2& pTR, const Vec2& pBR)
{
	//借鉴（chao）的，直接操控顶点=。=
	// Top Left
	//
	this->_quad.tl.vertices.x = pTL.x;
	this->_quad.tl.vertices.y = pTL.y;
	// Bottom Left
	//
	this->_quad.bl.vertices.x = pBL.x;
	this->_quad.bl.vertices.y = pBL.y;
	// Top Right
	//
	this->_quad.tr.vertices.x = pTR.x;
	this->_quad.tr.vertices.y = pTR.y;
	// Bottom Right
	//
	this->_quad.br.vertices.x = pBR.x;
	this->_quad.br.vertices.y = pBR.y;
	float size = std::max(fabs(pBR.x - pBL.x), fabs(pTL.y - pBL.y));

	this->setContentSize(Size(size, size));//要有宽度高度
}