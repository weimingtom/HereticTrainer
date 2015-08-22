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
	double x1 = tailRing->getPositionX();//������Բ��ȷ�����ε�4����
	double y1 = tailRing->getPositionY();
	double x2 = headRing->getPositionX();
	double y2 = headRing->getPositionY();
	//��Բ���ź�뾶
	double R1 = tailRing->getScale() * 62;
	double R2 = headRing->getScale() * 62;
	//��Բ����
	double dis = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	//����������һ�����㣬˵�����ף�����ͼ��Ͷ�����
	double Sin = (x1 - x2) / dis;
	double Cos = (y1 - y2) / dis;
	setVertex(
		Vec2(x1 - R1*Cos, y1 + R1*Sin)//���Ͻ�
		, Vec2(x2 - R2*Cos, y2 + R2*Sin)//���½�
		, Vec2(x1 + R1*Cos, y1 - R1*Sin)//���Ͻ�
		, Vec2(x2 + R2*Cos, y2 - R2*Sin)//���½�


		);


}
void StripSprite::setVertex(const Vec2& pTL, const Vec2& pBL, const Vec2& pTR, const Vec2& pBR)
{
	//�����chao���ģ�ֱ�Ӳٿض���=��=
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

	this->setContentSize(Size(size, size));//Ҫ�п�ȸ߶�
}