#include"Sound.h"

#include"audio\include\AudioEngine.h"
using namespace cocos2d;
using namespace experimental;
void Sound::bad()
{
	AudioEngine::play2d("good.ogg");
}
void Sound::good()
{
	AudioEngine::play2d("good.ogg");
}
void Sound::great()
{
	AudioEngine::play2d("great.ogg");
}
void Sound::perfect()
{
	AudioEngine::play2d("perfect.ogg");
}
void Sound::miss()
{
	AudioEngine::play2d("miss.ogg");

}
void Sound::init()
{

}
void Sound::stopAll()
{
	AudioEngine::stopAll();
}
void Sound::pauseALL()
{
	AudioEngine::pauseAll();

}
void Sound::resumeAll()
{
	AudioEngine::resumeAll();
}
int Sound::playBGM(std::string path, SoundFinishCallback callback)
{
	auto id = AudioEngine::play2d(path);
	AudioEngine::setFinishCallback(id, callback);

	return 0;
}
Sound *Sound::instance = NULL;
Sound* Sound::getInstance()
{
	if (instance == NULL)instance = new Sound();
	return instance;
}
