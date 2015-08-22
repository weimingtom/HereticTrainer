#ifndef __BEATOBJECT_VIEW_H__
#define __BEATOBJECT_VIEW_H__
#include"cocos2d.h"
#include"StripSprite.h"
#include"LiveInfo.h"
#include"GameSetting.h"
USING_NS_CC;
/*
��Ϸ���飬����һ��beat
�ö�������һ��Node
����3���ӽڵ㣬		
Sprite* headRingSprite;//ͷԲ��
Sprite * tailRingSprite;//βԲ��
StripSprite *stripSprite;//��״����

updateState(double t)Ӧ��ÿһ֡�����ã�����״̬��
����״̬�����ƣ�����4��״̬
��ʼ��STATE_BEGIN������ʾ��λ�ڳ����㣬����������ʱ����ת��ΪSTATE_HEAD_RUNNING״̬
STATE_HEAD_RUNNING ��ʾ������ͷ��Բ������λ�ã���Ȼ�����β��Բ��Ҳ�������ʱ�䣬Ҳ����λ�ø��¡�����ǳ���beat����������������STATE_TAIL_RUNNING״̬������miss����STATE_END
STATE_TAIL_RUNNING �������ڳ���beat�У�ͷ��Բ���̶���Ŀ��㣬β��Բ���˶���������������miss�����STATE_END״̬
STATE_END ��ֹ״̬������ʾ

�����¼�ͨ��int touchBegin(double t)���ݣ�
int touchBegin(double t)��3�ַ���ֵ������1��ʾ����ǰbeat�Ѿ����ж����ôδ����¼�Ӧ�����ݸ���һ��beat������-1��ʾ��δ�����Դ������¼���Ӧ�����Ա��δ���������0��ʾ�ôδ��������ܣ����Ѿ������ж������
bool touchEnd(double t) Ҳ�з���ֵ���������ʾ�ôδ��������¼�Ӧ�������ԣ��������ʾ�ô��������ܣ������Ѿ������ж���

�����ж�����ԭʵ�ֲ�ͬ
Ȼ��ͨ��ÿһ֡����
Score getHeadScore();
Score getTailScore();
��ȡ�������������ʾ��������ͳ�ƣ��������ͬһ֡�ڳ�����Ҫ��ʾ�������������ʱ��ֻ��ʾһ�֣���Ȼͳ��������������Ч�����ĵ��ã���֤ÿһ֡������һ�Ρ�
void headScoreShowed();tailScoreShowed()���Ϊ�Ѿ���ʾ״̬���������´κ�����

*/
class BeatObject:public Node
{
public:
	//״̬����ϸ����˵��
	static const int STATE_BEGIN=0;
	
	static const int STATE_HEAD_RUNNING = 1;
	//static const int STATE_HEAD_JUDGEING = 2;
	static const int STATE_TAIL_RUNNING = 3;
	//static const int STATE_TAIL_JUDGEING = 4;
	static const int STATE_END = 5;

	static BeatObject*create(Beat beat);
	bool init( Beat beat);

	//����beatObject״̬��t���ݵ�ǰʱ��
	void updateState(double t);
	//���ݴ�����ʼʱ�䣬t���ݵ�ǰʱ�䣬��3�ַ���ֵ������1��ʾ����ǰbeat�Ѿ����ж����ôδ����¼�Ӧ�����ݸ���һ��beat��
	//����-1��ʾ��δ�����Դ������¼���Ӧ�����Ա��δ���������0��ʾ�ôδ��������ܣ����Ѿ������ж������
	int touchBegin(double t);
	//���ݴ�������ʱ�䣬t���ݵ�ǰʱ�䣬����ֵ���������ʾ�ôδ��������¼�Ӧ�������ԣ��������ʾ�ô��������ܣ������Ѿ������ж���
	bool touchEnd(double t);
	
	//��ȡ��beat������
	int getType();
	//��ȡͷ���������Noneδ���ۣ�Showed �Ѿ���ʾ����
	Score getHeadScore();
	//���ͷ������Ϊ�Ѿ���ʾ��showed
	void headScoreShowed();
	//��ȡβ���������Noneδ���ۣ�Showed �Ѿ���ʾ����
	Score getTailScore();
	//��ȡ��beat������һ����
	int getPos();
	//���β������Ϊ�Ѿ���ʾ��showed
	void tailScoreShowed();
private:
	
	int type;
	int pos;
	Score headResult;
	Score tailResult;
	//ͷ������ʱ��
	double headAppearTime;
	//ͷ������Ŀ���ʱ��
	double headArriveTime;
	//ͷ����ʧʱ�䣬��missʱ��
	double headDisappearTime;
	//β������ʱ��
	double tailAppearTime;
	//β������Ŀ���ʱ��
	double tailArriveTime;
	//β����ʧʱ�䣬��missʱ��
	double tailDisappearTime;
	int state;
	Sprite* headRingSprite;
	Sprite * tailRingSprite;
	StripSprite *stripSprite;
	//����beatλ��
	void updatePosition(double t);

	
};
#endif