#ifndef __LLPMEDIATOR_CORE_H__
#define __LLPMEDIATOR_CORE_H__
#include"cocos2d.h"
#include<mutex>
#include<thread>
#include<stdio.h>
#include<string>
#include"curl\curl.h"
#include"LiveInfo.h"
#include<vector>
USING_NS_CC;
//分类，id+name
struct Category
{
	int id;
	std::string name;
	Category()
	{
		id = -1;
		name = "";
	}
	Category(int id, std::string name)
	{
		this->id = id;
		this->name = name;
	}
};
//上传用户
struct UploadUser
{
	std::string username;
	std::string avatar_path;
	int id;
	int post_count;
	UploadUser()
	{
		id = 0;
		post_count = 0;
	}
	UploadUser(std::string username, std::string avatar_path, int id)
	{
		this->username = username;
		this->avatar_path = avatar_path;
		this->id = id;
	}
};
//live列表，列表项
struct LiveListItem
{
	std::string cover_path;
	UploadUser upload_user;
	int level;
	std::string artist;
	std::string live_name;
	bool memberonly;
	int click_count;
	std::string live_id;
	LiveListItem()
	{
		level = click_count = 0;
		memberonly = false;
	}
	LiveListItem(std::string cover_path, UploadUser upload_user, int level, std::string artist, std::string live_name, bool memberonly, int click_count, std::string live_id)
	{
		this->cover_path = cover_path;
		this->upload_user = upload_user;
		this->level = level;
		this->artist = artist;
		this->live_name = live_name;
		this->memberonly = memberonly;
		this->click_count = click_count;
		this->live_id = live_id;
	}
};
//live列表
struct LiveList
{
	int count;
	std::vector<LiveListItem> items;
};
struct LiveDetails
{
	Category category;
	std::string bgimg_file;
	std::string update_time;
	std::string cover_path;
	UploadUser upload_user;
	//int added_like;
	int click_count;
	std::string live_info;
	std::string artist;
	int like_count;
	std::string state;
	std::string bgm_file;
	std::string live_name;
	bool memberonly;
	std::string live_setting;
	std::string live_id;
	int level;
	//int added_fav;
	std::string map_file;

};
//LLP中介者，负责与LLP网站沟通，实现登陆，注册，获取live列表，下载live信息，评论，收藏功能
class LLPMediator
{
public:
	void test();
	static  LLPMediator*getInstance();
	//连接状态
	const int CONNERTSTATE_ERROR = 0;
	const int CONNERTSTATE_CONNERTING = 1;
	const int CONNERTSTATE_COMPLETED = 2;
	//创建一个连接，开始尝试登陆操作
	std::string  encryptPassword(std::string password);
	std::string  makeXSign(std::string str);
	void login(std::string username,std::string password,int timeout=10);
	//获取登陆连接状态
	int getLoginConnertState();
	//是否已经登陆，可在获知连接完成后调用，获知是否登陆成功
	bool isLogined();
	//创建一个连接，开始尝试注册操作
	void reg(std::string email, std::string password, std::string reg_code/*邀请码*/, std::string username, int timeout = 10);
	int getRegConnertState();
	bool isRegSuccessed();
	//创建一个连接，开始尝试获取分类
	void loadCategory(int timeout=10);
	int getLoadCategoryConnertState();
	bool isLoadCategorySuccessed();
	//如成功获取得分类，调用该函数可以得到分类列表
	std::vector<Category> getCategorys();



	//获取livelist，推介列表,并自动下载封面
	void loadLiveList_Featured(int jsonTimeout=10, int downloadTimeout=20);
	//获取livelist，最新列表,并自动下载封面
	void loadLiveList_Public(int offset, int limit, int jsonTimeout = 10, int downloadTimeout = 20);
	//获取livelist，分类列表,并自动下载封面
	void loadLiveList_Category(int categoryID, int offset, int limit,int jsonTimeout = 10, int downloadTimeout = 20);
	void loadLiveList_Favorites(int offset, int limit, int jsonTimeout = 10, int downloadTimeout = 20);
	void loadLiveList_Search(std::string keyword,int offset, int limit, int jsonTimeout = 10, int downloadTimeout = 20);
	int getLoadLiveListConnertState();
	bool isLoadLiveListSuccessed();
	LiveList getLiveList();

	//获取live的详细信息
	void loadLiveDetails(std::string liveID, int timeout = 10);
	int getLoadLiveDetailsConnertState();
	bool isLoadLiveDetailsSuccessed();
	LiveDetails getLiveDetails();

	//加载live，获取所需要的谱面，背景音乐和背景图片
	void loadLiveData(std::string liveID,std::string map_file,std::string bgimg_file,std::string bgm_file, int jsonTimeout=10, int downloadTimeout=30);
	int getLoadLiveDataConnertState();
	bool isLoadLiveDataSuccessed();
	int getLoadLiveProgress();
	std::string getLiveJson();
	bool parseLLPBeatMapJson(LiveInfo &liveInfo,std::string jsonText);

	std::string loginUsername = "";
	int loginUid = 0;
	std::string loginToken = "";
	std::string loginRole = "";
	std::string loginCookie = "";

private:
	

	//std::mutex mtx;
	static LLPMediator* instance;
	void loadLiveList(std::string url, int jsonTimeout, int downloadTimeout,std::string xsign="");
	/////////////////////////////login//////////////////////////
	int loginConnertState = CONNERTSTATE_COMPLETED;
	bool logined = false;
	std::string loginConnertData;

	void __thread_login(std::string username, std::string password, int timeout);
	friend size_t __notclassfunction_thread_login_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_login_callback(void *buffer, size_t size, size_t nmemb);
	///////////////////////////////////////////////////////////////
	/////////////////////////////register//////////////////////////
	int regConnertState = CONNERTSTATE_COMPLETED;
	bool regSuccessed = false;
	std::string regConnertData;
	void __thread_reg(std::string email, std::string password, std::string reg_code, std::string username, int timeout);
	friend size_t __notclassfunction_thread_reg_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_reg_callback(void *buffer, size_t size, size_t nmemb);
	///////////////////////////////////////////////////////////////
	/////////////////////////////loadCategory//////////////////////////
	int loadCategoryConnertState = CONNERTSTATE_COMPLETED;
	bool loadCategorySuccessed = false;
	std::string loadCategoryConnertData;
	std::vector<Category> categorys;
	void __thread_loadCategory(int timeout);
	friend size_t __notclassfunction_thread_loadCategory_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadCategory_callback(void *buffer, size_t size, size_t nmemb);
	///////////////////////////////////////////////////////////////
	/////////////////////////////loadLiveList//////////////////////////
	int loadLiveListConnertState = CONNERTSTATE_COMPLETED;
	bool loadLiveListSuccessed = false;
	std::string loadLiveListJsonData;
	LiveList livelist;
	FILE *loadLiveListDownloadingFileHandle=NULL;
	void __thread_loadLiveList(std::string url, int jsonTimeout, int downloadTimeou, std::string xsignt);
	friend size_t __notclassfunction_thread_loadLiveList_json_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveList_json_callback(void *buffer, size_t size, size_t nmemb);
	friend size_t __notclassfunction_thread_loadLiveList_file_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveList_file_callback(void *buffer, size_t size, size_t nmemb);
	///////////////////////////////////////////////////////////////
	
	/////////////////////////////loadLiveDetails//////////////////////////
	int loadLiveDetailsConnertState = CONNERTSTATE_COMPLETED;
	bool loadLiveDetailsSuccessed = false;
	std::string loadLiveDetailsConnertData;
	LiveDetails liveDetails;

	void __thread_loadLiveDetails(std::string liveID,int timeout);
	friend size_t __notclassfunction_thread_loadLiveDetails_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveDetails_callback(void *buffer, size_t size, size_t nmemb);
	///////////////////////////////////////////////////////////////
	/////////////////////////////loadLiveData//////////////////////////
	int loadLiveDataConnertState = CONNERTSTATE_COMPLETED;
	bool loadLiveDataSuccessed = false;
	std::string liveJson = "";
	int loadLiveDataProgress = 0;
	void __thread_loadLiveData(std::string liveID, std::string map_file, std::string bgimg_file, std::string bgm_file, int jsonTimeout, int downloadTimeout);
	FILE*loadLiveDataBgmFileHandle;
	FILE*loadLiveDataBgimgFileHandle;
	friend size_t __notclassfunction_thread_loadLiveData_liveJson_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveData_liveJson_callback(void *buffer, size_t size, size_t nmemb);
	friend size_t __notclassfunction_thread_loadLiveData_bgimg_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveData_bgimg_callback(void *buffer, size_t size, size_t nmemb);
	friend size_t __notclassfunction_thread_loadLiveData_bgm_callback(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t __thread_loadLiveData_bgm_callback(void *buffer, size_t size, size_t nmemb);
	friend int   __notclassfunction_thread_loadLiveData_bgm_procress_callback(void *userp, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
	int  __thread_loadLiveData_bgm_procress_callback(double TotalToDownload, double NowDownloaded);

	///////////////////////////////////////////////////////////////


	
};

size_t __notclassfunction_thread_login_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_reg_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadCategory_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadLiveList_json_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadLiveList_file_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadLiveDetails_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadLiveData_liveJson_callback(void *buffer, size_t size, size_t nmemb, void *userp);
size_t __notclassfunction_thread_loadLiveData_bgimg_callback(void *buffer, size_t size, size_t nmemb, void *userp);

size_t __notclassfunction_thread_loadLiveData_bgm_callback(void *buffer, size_t size, size_t nmemb, void *userp);

int   __notclassfunction_thread_loadLiveData_bgm_procress_callback(void *userp, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);


/*
{"content": {"username": "AnzerWall", "token": "", "role": "user", "uid": 76, "logincookie": ""}, "succeed": true}
*/
/*
{"username": "AnzerWall", "password": "sha256"}
*/
/*
{"username":"anzerwall1","password":"sha256","email":"295103826@163.com","reg_code":" "}
*/
/*
{"content": {"items": [{"id": 1, "name": "EASY"}, {"id": 2, "name": "NORMAL"}, {"id": 3, "name": "HARD"}, {"id": 4, "name": "EXTREME"}, {"id": 5, "name": "TECHNICAL"},
{"id": 6, "name": "ULTIMATE"}, {"id": 0, "name": "\u5176\u4ed6"}]}, "succeed": true}
*/
/*
{
"content": {
"count": 633,
"items": [
{
"cover_path": "Djo9F6LZ6CiR.jpg",
"upload_user": {
"username": "MAMUS",
"avatar_path": "soDwsEgGM0pi.png",
"id": 260
},
"level": 9,
"artist": "Extreme Dinosaurs",
"live_name": "Golo ve",
"memberonly": false,
"click_count": 22,
"live_id": "XUG740fWFcUW6cBa"
},
{
"cover_path": "hz205krWW3FK.png",
"upload_user": {
"username": "yuyu0127",
"avatar_path": "UJQrDd2xunOm.png",
"id": 1935
},
"level": 14,
"artist": "t+pazolite",
"live_name": "Marry me, Nightmare [EX]",
"memberonly": false,
"click_count": 182,
"live_id": "AIo4hsu6a73jhDMv"
},
{
"cover_path": "FqvAJieTj09C.png",
"upload_user": {
"username": "如月喵",
"avatar_path": "sIguQvqt99X2.png",
"id": 324
},
"level": 12,
"artist": "Persona",
"live_name": "AREA184-Platinum Mix-",
"memberonly": false,
"click_count": 100,
"live_id": "VHG73qGauzLeyng1"
},
{
"cover_path": "QyVbh3W6aGFr.png",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 14,
"artist": "cosMo@暴走P",
"live_name": "For UltraPlayers",
"memberonly": false,
"click_count": 224,
"live_id": "7QdtNnZWgK1veRmW"
},
{
"cover_path": "cLuS3I3hip2K.jpg",
"upload_user": {
"username": "niconiconi",
"avatar_path": "yduPq887H9uW.png",
"id": 10
},
"level": 11,
"artist": "Neru （feat.鏡音リン）",
"live_name": "ロストワンの号哭",
"memberonly": false,
"click_count": 826,
"live_id": "mFSq99tc9dAlPdes"
},
{
"cover_path": "Wa7kNrf2WPtb.jpg",
"upload_user": {
"username": "oscar865",
"avatar_path": "DEUx8eXQbIke.png",
"id": 86
},
"level": 11,
"artist": "sunny day song:- -←HEARTBEAT",
"live_name": "- -←HEARTBEAT",
"memberonly": false,
"click_count": 897,
"live_id": "qHM69xnWgHFo1RJW"
},
{
"cover_path": "LDAwKqY0rk49.jpg",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 13,
"artist": "DJ SHARPNEL feat. みらい",
"live_name": "つぶやき魔法少女りむる",
"memberonly": false,
"click_count": 123,
"live_id": "hR884F40w6ShLMAt"
},
{
"cover_path": "bNp275FLC24q.jpg",
"upload_user": {
"username": "706蓝光",
"avatar_path": "1UT4Y2OJ9RA5.png",
"id": 80
},
"level": 10,
"artist": "Earphones",
"live_name": "それが声優！",
"memberonly": false,
"click_count": 163,
"live_id": "aUwuTIvIi3U5CrbK"
},
{
"cover_path": "SfvB4s8ppzOc.jpg",
"upload_user": {
"username": "散步君",
"avatar_path": "kA04MU4I4VDg.png",
"id": 329
},
"level": 11,
"artist": "ZAQ",
"live_name": "VOICE",
"memberonly": false,
"click_count": 392,
"live_id": "PcPViDzSs30eCVjj"
},
{
"cover_path": "BGDTqMkRtebl.png",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 12,
"artist": "すのうまん",
"live_name": "おお われら喜び讃うべし、主よ",
"memberonly": false,
"click_count": 103,
"live_id": "7owBDc9v7tdTOkPb"
},
{
"cover_path": "C2iLGw8ZKHyA.png",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 11,
"artist": "MAD CHILD",
"live_name": "Voice 2 Voice",
"memberonly": false,
"click_count": 129,
"live_id": "o9KLbrPB6GFFEbB2"
},
{
"cover_path": "1p5hcRV2ce6U.jpg",
"upload_user": {
"username": "MAMUS",
"avatar_path": "soDwsEgGM0pi.png",
"id": 260
},
"level": 9,
"artist": "ラペッジオート",
"live_name": "イマジネイション——HD",
"memberonly": false,
"click_count": 86,
"live_id": "9jLOWitwwzUGjJI7"
},
{
"cover_path": "Dp6QVFDWFy52.jpg",
"upload_user": {
"username": "依协莉丝",
"avatar_path": "FJeM4lvqGU9m.png",
"id": 201
},
"level": 10,
"artist": "三森すずこ",
"live_name": "纯情DA DANDAN",
"memberonly": false,
"click_count": 206,
"live_id": "D640h0bB6TYZhEIl"
},
{
"cover_path": "rSVlM0bknZL0.jpg",
"upload_user": {
"username": "oscar865",
"avatar_path": "DEUx8eXQbIke.png",
"id": 86
},
"level": 8,
"artist": "next to you",
"live_name": "Next to you",
"memberonly": false,
"click_count": 241,
"live_id": "SJTa4PvazSWhI8O8"
},
{
"cover_path": "lLGbp8T1abPl.jpg",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 10,
"artist": "niki feat.kradness;",
"live_name": "WAVE",
"memberonly": false,
"click_count": 308,
"live_id": "2h0gRk0HXd0Da0cw"
},
{
"cover_path": "HBiuWaG8EQMz.png",
"upload_user": {
"username": "LZKUY",
"avatar_path": "KZD9DeTOfQNF.png",
"id": 3141
},
"level": 12,
"artist": "Persona",
"live_name": "Green Eyes",
"memberonly": false,
"click_count": 187,
"live_id": "uijyWg6pnHpZTC4j"
},
{
"cover_path": "Rs6eoe2KlzrV.jpg",
"upload_user": {
"username": "天坑君",
"avatar_path": "jvqzjDsMP89b.png",
"id": 276
},
"level": 11,
"artist": "雨宫天",
"live_name": "Skyreach",
"memberonly": false,
"click_count": 236,
"live_id": "TRtOyUaCiiaUGBEl"
},
{
"cover_path": "lFlTpWJISvsO.jpg",
"upload_user": {
"username": "豆腐豆腐豆",
"avatar_path": "pzGTeaotzHTs.png",
"id": 75
},
"level": 9,
"artist": "μ's-高坂穗乃果(CV:新田惠海)",
"live_name": "もうひとりじゃないよ(自制Ex)",
"memberonly": false,
"click_count": 662,
"live_id": "hBfXZdPjJXSrZier"
},
{
"cover_path": "3N5topsy1mTH.jpg",
"upload_user": {
"username": "MAMUS",
"avatar_path": "soDwsEgGM0pi.png",
"id": 260
},
"level": 9,
"artist": "作：食戟のソーマ 歌：东京カランコロン",
"live_name": "スパイス",
"memberonly": false,
"click_count": 292,
"live_id": "hhCNkAd0gGeoafja"
},
{
"cover_path": "80IfY9D1FGUm.jpg",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
},
"level": 10,
"artist": "Mili",
"live_name": "YUBIKIRI-GENMAN",
"memberonly": false,
"click_count": 528,
"live_id": "3rHD7q0WSXa7VQQl"
},
{
"cover_path": "JV2JsoEyP67G.jpg",
"upload_user": {
"username": "YingC",
"avatar_path": "pemO5nyoCDAn.png",
"id": 1354
},
"level": 10,
"artist": "森永真由美",
"live_name": "Mermaid girl",
"memberonly": false,
"click_count": 169,
"live_id": "cc8xee0lfubsYbcY"
},
{
"cover_path": "ULTEEXeZRf7q.jpg",
"upload_user": {
"username": "Dororo",
"avatar_path": "aRLtC4Au2uTb.png",
"id": 308
},
"level": 9,
"artist": "西浦智仁",
"live_name": "谜4（Puzzle 4）",
"memberonly": false,
"click_count": 54,
"live_id": "UgIarveexZBNN2Pq"
},
{
"cover_path": "FYfVg7PFL4d3.jpg",
"upload_user": {
"username": "口袋迷",
"avatar_path": "LTjoS7Bo5JkO.png",
"id": 321
},
"level": 8,
"artist": "今井麻美",
"live_name": "苍い鸟 TV ARRANGE",
"memberonly": false,
"click_count": 158,
"live_id": "c7cxiG79AoOmimWb"
},
{
"cover_path": "JHaHLt6RtyCr.png",
"upload_user": {
"username": "次奥这不科学",
"avatar_path": "FAbLgak0Yva6.png",
"id": 305
},
"level": 10,
"artist": "μ's",
"live_name": "Dancing stars on me【創作譜面】",
"memberonly": false,
"click_count": 989,
"live_id": "wxJTivqDZ8ywSMex"
}
]
},
"succeed": true
}
*/

/*
https://m.tianyi9.com/API/postcomment?logincookie=OEVDZucWYT02Bs27eJWPYOWnjSMQMzAH&timestamp=1438506693599
post

{"live_id":"7QdtNnZWgK1veRmW","comment":"@AnzerWall1 测试API，别管我喵~","type":"public"}


响应
{"content": {}, "succeed": true}
*/
/*
https://m.tianyi9.com/API/getcomments?live_id=7QdtNnZWgK1veRmW&limit=20&offset=0&logincookie=OEVDZucWYT02Bs27eJWPYOWnjSMQMzAH&timestamp=1438506598941
{
"content": {
"count": 4,
"items": [
{
"content": "测试评论API，勿理",
"comment_date": "2015-08-02T09:09:58",
"id": 2024,
"user": {
"username": "AnzerWall",
"avatar_path": null,
"id": 76
}
},
{
"content": "@MAMUS 做出来挺长时间啦，今天顺便31了下",
"comment_date": "2015-07-31T14:18:53",
"id": 2011,
"user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63
}
},
{
"content": "。。。。果然是公主的110谱，我报警了",
"comment_date": "2015-07-31T12:30:35",
"id": 2008,
"user": {
"username": "SoulMar大头猫",
"avatar_path": "eBymQcwKvrG8.png",
"id": 294
}
},
{
"content": "以后无（常）法（常）投（杀）稿（人）",
"comment_date": "2015-07-31T11:30:03",
"id": 2007,
"user": {
"username": "MAMUS",
"avatar_path": "soDwsEgGM0pi.png",
"id": 260
}
}
]
},
"succeed": true
}

*/
/*
{
"content": {
"category": {
"id": 6,
"name": "ULTIMATE"
},
"bgimg_file": "9v8XSNpEnfir",
"update_time": "2015-07-25T13:12:10",
"cover_path": "QyVbh3W6aGFr.png",
"upload_user": {
"username": "小泉花陽",
"avatar_path": "dWcX8gkzR3SD.png",
"id": 63,
"post_count": 110
},
"added_like": null,
"click_count": 234,
"live_info": "SDVXII最高难度曲，BPM201，For UltraPlayers！",
"artist": "cosMo@暴走P",
"like_count": 0,
"state": "public",
"bgm_file": "j0e04GkBxGq4",
"live_name": "For UltraPlayers",
"memberonly": false,
"live_setting": "",
"live_id": "7QdtNnZWgK1veRmW",
"level": 14,
"added_fav": null,
"map_file": "UWAt7q0e7FPk"
},
"succeed": true
}
*/
/*
https://m.tianyi9.com/API/addFavorite?live_id=7QdtNnZWgK1veRmW&logincookie=OEVDZucWYT02Bs27eJWPYOWnjSMQMzAH&timestamp=1438507782231

{"content": {}, "succeed": true}
*/
/*
https://m.tianyi9.com/API/likeLive?live_id=7QdtNnZWgK1veRmW&logincookie=OEVDZucWYT02Bs27eJWPYOWnjSMQMzAH&timestamp=1438507884400
{"content": {}, "succeed": true}
*/
/*
https://m.tianyi9.com/API/delFavorite?live_id=7QdtNnZWgK1veRmW&logincookie=OEVDZucWYT02Bs27eJWPYOWnjSMQMzAH&timestamp=1438507978257
{"content": {}, "succeed": true}
*/
#endif