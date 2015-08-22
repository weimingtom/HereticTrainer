#ifndef __LIVEINFO_CORE_H__
#define __LIVEINFO_CORE_H__
#include<string>
#include<vector>

/*
LIve���ݵĶ��壬����ͳһllp�ĸ�ʽ�ͱ��ظ�ʽ��
���ݸ�maingame������Ϸ
�洢��������
*/
//������beat������
struct Beat
{
	//beat���ͣ�����beat���ñ�־λ0��ʾ����beat
	static const int  TYPE_LONG = 0x00000001;
	//beat���ͣ�ͬʱ��beat��Ϊ��beat��ʾ����,��ʾ��beat������beat��Ҫͬʱ����
	static const int  TYPE_SAMETIME = 0x00000002;
	//beat���ͣ�������beat��ʧ��ʱ���Ѫ��Ϊ��beat��ʾ����
	static const int  TYPE_STAR = 0x00000004;
	int type;//��ʾ��beat���ͣ���BEATTYPE_*����
	int pos;//λ�ã���beat��������ڵڼ������±�����ұ��0-8
	double beginTime;//����ʱ��
	double endTime;//��ʧʱ�䣬���ڳ�������ʱ��Ч
	Beat();
	Beat(int type, int pos, double beginTime);
	Beat(int type, int pos, double beginTime, double endTime);
	bool operator<(const Beat&that) const;
	void log();

};
enum class Score{ PERFECT = 1, GREAT, GOOD, BAD, MISS, NONE ,SHOWED};

struct LiveInfo
{
	//������������·��
	std::string bgm_path;
	//����ͼƬ·��
	std::string bgimg_path;
	//live����
	std::string live_name;
	//����·��
	std::string cover_path;
	//�û���
	std::string username;
	//Live�ٶȣ���λ/s
	double speed = 1.6;
	//��Ϸ��������
	std::vector<Beat> beats[9];
};

#endif