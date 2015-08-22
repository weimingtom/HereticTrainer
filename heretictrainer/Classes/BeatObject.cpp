#include"BeatObject.h"
#include<math.h>

bool BeatObject::init( Beat beat)
{
	if (!Node::init())return false;
	//设置为起始状态
	state = STATE_BEGIN;

	type = beat.type;
	pos = beat.pos;
	//是否为同时型beat，采用不同的纹理
	if (beat.type & Beat::TYPE_SAMETIME)
	{
		headRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_normal"));
		//设置到出生点，缩放到最小
		headRingSprite->setScale(0);
		headRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//headRingSprite->setVisible(false);
		addChild(headRingSprite,2);
	}
	else
	{
		headRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_sametime"));
		//设置到出生点，缩放到最小
		headRingSprite->setScale(0);
		headRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//headRingSprite->setVisible(false);
		addChild(headRingSprite,2);
	}
	//计算头部出现时间，到达时间，消失时间
	headAppearTime = beat.beginTime;
	headArriveTime = headAppearTime+GameSetting::getInstance()->getSpeed();
	headDisappearTime = headArriveTime + GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS);
	//如果是长型圆环
	if (beat.type & Beat::TYPE_LONG)
	{
		tailRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_tail"));
		//设置到出生点，缩放到最小
		tailRingSprite->setScale(0);
		tailRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//tailRingSprite->setVisible(false);
		addChild(tailRingSprite,3);
		stripSprite = StripSprite::create(headRingSprite, tailRingSprite);
		//stripSprite->setVisible(false);
		//计算尾部出现时间，到达时间，消失时间
		tailAppearTime = beat.endTime;
		tailArriveTime = tailAppearTime + GameSetting::getInstance()->getSpeed();
		tailDisappearTime = tailArriveTime + GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS);
		addChild(stripSprite,1);

	}
	setVisible(false);
	//初始化评价情况
	headResult = Score::NONE;
	//如果是非长型，那么尾部的评价状态为已显示，方便判定
	if ((beat.type & Beat::TYPE_LONG))
		tailResult = Score::NONE;
	else
		tailResult = Score::SHOWED;
	
	return true;
}
BeatObject* BeatObject::create(Beat beat)
{

	BeatObject *pRet = new(std::nothrow)BeatObject();
	if (pRet && pRet->init(beat))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}
int  BeatObject::getType()
{
	return type;
}
Score  BeatObject::getHeadScore()
{
	return headResult;
}
Score  BeatObject::getTailScore()
{
	return tailResult;
}
void BeatObject::updateState(double t)
{
	//根据状态更新情况
	switch (state)
	{
	case BeatObject::STATE_BEGIN:
	{
									//已经到达头部出现时间
									if (t >= headAppearTime)
									{
										//进入头部运行状态
										state = STATE_HEAD_RUNNING;
										//log("t=%lf",t);
										//显示并且更新位置
										setVisible(true);
										updatePosition(t);

									}
									break;
	}

	case BeatObject::STATE_HEAD_RUNNING:
	{
										   //更新位置
										   updatePosition(t);
										   //如果头部已经到达消失时间还未响应
										   if (t >= headDisappearTime)
										   {
											   
											   
											   //再次检测评价状态，这里在多线程下应该有问题，不过没办法，加锁可能假死
											   if (headResult != Score::NONE )return;
											   //设置头部miss评价，尾部未已显示评价，进入结束状态，并且消失。。
											   headResult = Score::MISS;
											   tailResult = Score::SHOWED;
											   setVisible(false);
											   state = STATE_END;
											   
										   }
										   break;
	}
	case BeatObject::STATE_TAIL_RUNNING:
	{
										   //更新位置
										   updatePosition(t);
										   //如果已经到达尾部的消失时间
										   if (t >= tailDisappearTime)
										   {
											   //再次检测评价状态，这里在多线程下应该有问题，不过没办法，加锁可能假死
											   if (tailResult != Score::NONE)return;
											   //设置尾部miss评价，进入结束状态，并且消失。。
											   state = STATE_END;
											   
											   tailResult = Score::MISS;
											   setVisible(false);
										   }
										   break;
	}

	case BeatObject::STATE_END:
	{
								  break;
	}
	default:
		break;
	}
}
void BeatObject::updatePosition(double t)
{
	//更新beat的位置和大小
	//如果是长型beat
	if (type &Beat::TYPE_LONG)
	{
		if (t < headAppearTime)return;

		if (state == STATE_HEAD_RUNNING)
		{
			
			auto gs = GameSetting::getInstance();
			//路程比例，表示圆环走到目标点和出生点这段路程的哪一段，进度，这里涉及一些向量运算。。
			auto scale = (t - headAppearTime) / gs->getSpeed();

			headRingSprite->setPosition(gs->getBornPosition() +((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale ));
			headRingSprite->setScale(scale);
			if (t >= tailAppearTime)
			{
				//路程比例。。
				scale = (t -tailAppearTime) / gs->getSpeed();
				tailRingSprite->setPosition(gs->getBornPosition() + ((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale));
				tailRingSprite->setScale(scale);
			}
			stripSprite->updatePosition();
			
		}
		else if (state == STATE_TAIL_RUNNING)
		{
			auto gs = GameSetting::getInstance();
			//尾部运动时，头部停在目标坐标
			headRingSprite->setPosition(gs->getTargetPosition(pos));
			headRingSprite->setScale(1.0);
			//路程比例。。
			auto scale = (t - tailAppearTime) / gs->getSpeed();
			tailRingSprite->setPosition(gs->getBornPosition() + ((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale));
			tailRingSprite->setScale(scale);
			stripSprite->updatePosition();
		}

	}
	else
	{
		if (t < headAppearTime)return;
		auto gs = GameSetting::getInstance();

		auto scale = (t - headAppearTime) / gs->getSpeed();
		headRingSprite->setPosition(gs->getBornPosition() + ((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale));
		headRingSprite->setScale(scale);
	}
}
int  BeatObject::touchBegin(double t)
{
	//如果改beatobject已经被评价了,返回1，应该传递到下一beat
	if (headResult != Score::NONE)return 1;
	//时间误差
	double d = fabs(t - headArriveTime);
//	log("%lf",d);
	if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS))
	{
		//headResult = Score::MISS;
		//if (t > tailDisappearTime)return -1;
		//还未到可判定时间，应当忽略这次触摸。
		return -1;
	}
	else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_BAD))
	{
		headResult = Score::BAD;

	}
	else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_GOOD))
	{
		headResult = Score::GOOD;
	}
	else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_GREAT))
	{
		headResult = Score::GREAT;
	}
	else
	{
		headResult = Score::PERFECT;
	}
	//如果是长型，则进入尾部运动状态
	if (type& Beat::TYPE_LONG)
		state = STATE_TAIL_RUNNING;
	else
	{
		setVisible(false);
		state = STATE_END;
	}
	return 0;
}
int BeatObject::getPos()
{
	return pos;
}
void BeatObject::headScoreShowed()
{
	if (headResult != Score::NONE)

	{
		headResult = Score::SHOWED;
	}
}

void BeatObject::tailScoreShowed()
{
	if (tailResult != Score::NONE)

	{
		tailResult = Score::SHOWED;
	}
}
bool BeatObject::touchEnd(double t)
{
	//如果尾部没有被评价过，即非已经miss了且是长型beat
	if (type&Beat::TYPE_LONG&&tailResult==Score::NONE)
	{
		double d = fabs(t - tailArriveTime);//获取触摸误差
		if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS))
		{
			tailResult = Score::MISS;
		}
		else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_BAD))
		{
			tailResult = Score::BAD;

		}
		else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_GOOD))
		{
			tailResult = Score::GOOD;
		}
		else if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_GREAT))
		{
			tailResult = Score::GREAT;
		}
		else
		{
			tailResult = Score::PERFECT;
		}
		//隐藏该beatObject，进入end状态
		setVisible(false);
		state = STATE_END;
		return true;
	}
	return false;
}