#include"BeatObject.h"
#include<math.h>

bool BeatObject::init( Beat beat)
{
	if (!Node::init())return false;
	//����Ϊ��ʼ״̬
	state = STATE_BEGIN;

	type = beat.type;
	pos = beat.pos;
	//�Ƿ�Ϊͬʱ��beat�����ò�ͬ������
	if (beat.type & Beat::TYPE_SAMETIME)
	{
		headRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_normal"));
		//���õ������㣬���ŵ���С
		headRingSprite->setScale(0);
		headRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//headRingSprite->setVisible(false);
		addChild(headRingSprite,2);
	}
	else
	{
		headRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_sametime"));
		//���õ������㣬���ŵ���С
		headRingSprite->setScale(0);
		headRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//headRingSprite->setVisible(false);
		addChild(headRingSprite,2);
	}
	//����ͷ������ʱ�䣬����ʱ�䣬��ʧʱ��
	headAppearTime = beat.beginTime;
	headArriveTime = headAppearTime+GameSetting::getInstance()->getSpeed();
	headDisappearTime = headArriveTime + GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS);
	//����ǳ���Բ��
	if (beat.type & Beat::TYPE_LONG)
	{
		tailRingSprite = Sprite::create(GameSetting::getInstance()->getFileName("ring_tail"));
		//���õ������㣬���ŵ���С
		tailRingSprite->setScale(0);
		tailRingSprite->setPosition(GameSetting::getInstance()->getBornPosition());
		//tailRingSprite->setVisible(false);
		addChild(tailRingSprite,3);
		stripSprite = StripSprite::create(headRingSprite, tailRingSprite);
		//stripSprite->setVisible(false);
		//����β������ʱ�䣬����ʱ�䣬��ʧʱ��
		tailAppearTime = beat.endTime;
		tailArriveTime = tailAppearTime + GameSetting::getInstance()->getSpeed();
		tailDisappearTime = tailArriveTime + GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS);
		addChild(stripSprite,1);

	}
	setVisible(false);
	//��ʼ���������
	headResult = Score::NONE;
	//����Ƿǳ��ͣ���ôβ��������״̬Ϊ����ʾ�������ж�
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
	//����״̬�������
	switch (state)
	{
	case BeatObject::STATE_BEGIN:
	{
									//�Ѿ�����ͷ������ʱ��
									if (t >= headAppearTime)
									{
										//����ͷ������״̬
										state = STATE_HEAD_RUNNING;
										//log("t=%lf",t);
										//��ʾ���Ҹ���λ��
										setVisible(true);
										updatePosition(t);

									}
									break;
	}

	case BeatObject::STATE_HEAD_RUNNING:
	{
										   //����λ��
										   updatePosition(t);
										   //���ͷ���Ѿ�������ʧʱ�仹δ��Ӧ
										   if (t >= headDisappearTime)
										   {
											   
											   
											   //�ٴμ������״̬�������ڶ��߳���Ӧ�������⣬����û�취���������ܼ���
											   if (headResult != Score::NONE )return;
											   //����ͷ��miss���ۣ�β��δ����ʾ���ۣ��������״̬��������ʧ����
											   headResult = Score::MISS;
											   tailResult = Score::SHOWED;
											   setVisible(false);
											   state = STATE_END;
											   
										   }
										   break;
	}
	case BeatObject::STATE_TAIL_RUNNING:
	{
										   //����λ��
										   updatePosition(t);
										   //����Ѿ�����β������ʧʱ��
										   if (t >= tailDisappearTime)
										   {
											   //�ٴμ������״̬�������ڶ��߳���Ӧ�������⣬����û�취���������ܼ���
											   if (tailResult != Score::NONE)return;
											   //����β��miss���ۣ��������״̬��������ʧ����
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
	//����beat��λ�úʹ�С
	//����ǳ���beat
	if (type &Beat::TYPE_LONG)
	{
		if (t < headAppearTime)return;

		if (state == STATE_HEAD_RUNNING)
		{
			
			auto gs = GameSetting::getInstance();
			//·�̱�������ʾԲ���ߵ�Ŀ���ͳ��������·�̵���һ�Σ����ȣ������漰һЩ�������㡣��
			auto scale = (t - headAppearTime) / gs->getSpeed();

			headRingSprite->setPosition(gs->getBornPosition() +((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale ));
			headRingSprite->setScale(scale);
			if (t >= tailAppearTime)
			{
				//·�̱�������
				scale = (t -tailAppearTime) / gs->getSpeed();
				tailRingSprite->setPosition(gs->getBornPosition() + ((gs->getTargetPosition(pos) - gs->getBornPosition()) *scale));
				tailRingSprite->setScale(scale);
			}
			stripSprite->updatePosition();
			
		}
		else if (state == STATE_TAIL_RUNNING)
		{
			auto gs = GameSetting::getInstance();
			//β���˶�ʱ��ͷ��ͣ��Ŀ������
			headRingSprite->setPosition(gs->getTargetPosition(pos));
			headRingSprite->setScale(1.0);
			//·�̱�������
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
	//�����beatobject�Ѿ���������,����1��Ӧ�ô��ݵ���һbeat
	if (headResult != Score::NONE)return 1;
	//ʱ�����
	double d = fabs(t - headArriveTime);
//	log("%lf",d);
	if (d > GameSetting::getInstance()->getJudgeTime(GameSetting::JUDGETIME_MISS))
	{
		//headResult = Score::MISS;
		//if (t > tailDisappearTime)return -1;
		//��δ�����ж�ʱ�䣬Ӧ��������δ�����
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
	//����ǳ��ͣ������β���˶�״̬
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
	//���β��û�б����۹��������Ѿ�miss�����ǳ���beat
	if (type&Beat::TYPE_LONG&&tailResult==Score::NONE)
	{
		double d = fabs(t - tailArriveTime);//��ȡ�������
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
		//���ظ�beatObject������end״̬
		setVisible(false);
		state = STATE_END;
		return true;
	}
	return false;
}