#ifndef __LIVEINFO_CORE_H__
#define __LIVEINFO_CORE_H__
#include<string>
#include<vector>

/*
LIve数据的定义，用于统一llp的格式和本地格式。
传递给maingame进行游戏
存储谱面数据
*/
//代表单个beat的数据
struct Beat
{
	//beat类型，长型beat，该标志位0表示短型beat
	static const int  TYPE_LONG = 0x00000001;
	//beat类型，同时型beat，为该beat显示白条,表示该beat与其他beat需要同时按下
	static const int  TYPE_SAMETIME = 0x00000002;
	//beat类型，星星型beat，失误时会扣血，为该beat显示星星
	static const int  TYPE_STAR = 0x00000004;
	int type;//表示该beat类型，由BEATTYPE_*定义
	int pos;//位置，该beat物件出现在第几道，下标从左到右标号0-8
	double beginTime;//出现时间
	double endTime;//消失时间，仅在长型旋律时有效
	Beat();
	Beat(int type, int pos, double beginTime);
	Beat(int type, int pos, double beginTime, double endTime);
	bool operator<(const Beat&that) const;
	void log();

};
enum class Score{ PERFECT = 1, GREAT, GOOD, BAD, MISS, NONE ,SHOWED};

struct LiveInfo
{
	//背景音乐音乐路径
	std::string bgm_path;
	//背景图片路径
	std::string bgimg_path;
	//live名称
	std::string live_name;
	//封面路径
	std::string cover_path;
	//用户名
	std::string username;
	//Live速度，单位/s
	double speed = 1.6;
	//游戏谱面数据
	std::vector<Beat> beats[9];
};

#endif