
/*
���ܣ���Ϸ�����ֺ���Ч�Ĺ���
*/
#ifndef __SOUBD_CORE_H__
#define __SOUND_CORE_H__
#include"cocos2d.h"
#include<functional>
/*
��Ϸ����Ƶ�Ĺ���
*/
class Sound
{
public:
	typedef std::function<void(int, const std::string &)> SoundFinishCallback;
	static Sound*getInstance();
	void init();
	void miss();
	void good();
	void bad();
	void great();
	void perfect();
	void pauseALL();
	void resumeAll();
	void stopAll();
	int playBGM(std::string path, SoundFinishCallback callback);

private:
	static Sound* instance;
	SoundFinishCallback soundFinishCallback;
};
#endif