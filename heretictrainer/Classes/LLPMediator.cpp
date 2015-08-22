#include"LLPMediator.h"
#include"json/document.h"
#include"CrossPlatformHelper.h"
#include"sha256.h"
#include"time.h"


LLPMediator* LLPMediator::instance = NULL;
LLPMediator* LLPMediator::getInstance()
{
	if (!instance)instance = new LLPMediator();
	return instance;
}
std::string  LLPMediator::encryptPassword(std::string password)
{
	char buf[260];
	sha_256(buf, ("as_8^yg8*R" + password).c_str());
	return std::string(buf);
}
std::string  LLPMediator::makeXSign(std::string str)
{
	
	char buf[260];
	sha_256(buf,  str.c_str());
	log("[HereticTrainer][Notice][LLPMediator::makeXSign]source is {%s},xsign is {%s}", str.c_str(), buf);
	return std::string(buf);
}
void LLPMediator::login(std::string username, std::string password, int timeout)
{
	loginConnertState = CONNERTSTATE_CONNERTING;
	loginConnertData = "";
	logined = false;
	loginUsername = "";
	loginUid = 0;
	loginToken = "";
	loginRole = "";
	loginCookie = "";
	
	//LLP约定的对密码的加密过程
	
	log("[HereticTrainer][Notice][LLPMediator::login]login operator,username is {%s},password_encrypted is {%s},timeout is {%d}", username.c_str(), password.c_str(),timeout);
	std::thread t(std::bind(&LLPMediator::__thread_login, this,username,password,timeout));
	t.detach();
}
bool LLPMediator::isLogined()
{
//	std::lock_guard<std::mutex> m(mtx);
	return logined;

}
int LLPMediator::getLoginConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loginConnertState;
}
size_t __notclassfunction_thread_login_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_login_callback(buffer, size, nmemb);
	
}
size_t LLPMediator::__thread_login_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;
	//log("%d", size*nmemb);
	loginConnertData.append(p, p + (size*nmemb));
	return nmemb*size;
}
void  LLPMediator::__thread_login(std::string username, std::string password, int timeout)
{
	CURL *handle = curl_easy_init();
	std::string loginJson = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\"}";
	log("[HereticTrainer][Notice][ LLPMediator::__thread_login]loginjson is {%s}", loginJson.c_str());
	curl_easy_setopt(handle, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_login_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1); // 自动设置Referer

	curl_easy_setopt(handle, CURLOPT_URL, "https://m.tianyi9.com/API/login");
	curl_slist *plist = curl_slist_append(NULL,"Content-Type:application/json");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, plist);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, loginJson.c_str());
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);

	CURLcode res;
	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loginConnertState = CONNERTSTATE_ERROR;
		curl_easy_cleanup(handle);
		log("[HereticTrainer][Error][ LLPMediator::__thread_login]curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
		return;
	}
	if (res==CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loginConnertState = CONNERTSTATE_COMPLETED;

		rapidjson::Document doc;
		doc.Parse<0>(loginConnertData.c_str());
		if (doc.HasParseError())
		{ 

			log("[HereticTrainer][Error][ LLPMediator::__thread_login]cannot parse,json is {%s}", loginConnertData.c_str());
			curl_easy_cleanup(handle);
			return;
		}

		if ((!doc.HasMember("succeed")) || doc["succeed"].GetBool() == false)
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_login]login operator fail,json is {%s}", loginConnertData.c_str());
			curl_easy_cleanup(handle);
			return;
		}
	
			
		loginUsername = doc["content"]["username"].GetString();
		loginToken= doc["content"]["token"].GetString();
		loginRole = doc["content"]["role"].GetString();
		loginUid = doc["content"]["uid"].GetInt();
		loginCookie = doc["content"]["logincookie"].GetString();	
		
	}
	logined = true;
	curl_easy_cleanup(handle);
	log("[HereticTrainer][Notice][ LLPMediator::__thread_login]{%s} logined,logincookie is {%s}",loginUsername.c_str(),loginCookie.c_str());
}
void LLPMediator::test()
{

}
size_t __notclassfunction_thread_reg_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_reg_callback(buffer, size, nmemb);
}
void LLPMediator::__thread_reg(std::string email, std::string password, std::string reg_code, std::string username, int timeout)
{
	CURL *handle = curl_easy_init();
	std::string regJson = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"email\":\"" + email + "\",\"reg_code\":\"" + reg_code + "\"}";
	log("[HereticTrainer][Notice][LLPMediator::__thread_reg]register json is {%s}", regJson.c_str());

	curl_easy_setopt(handle, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_reg_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1); 
	curl_easy_setopt(handle, CURLOPT_URL, "https://m.tianyi9.com/API/signup");
	curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, plist);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, regJson.c_str());
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
	CURLcode res;

	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		regConnertState = CONNERTSTATE_ERROR;
		log("[Heretic][Error][LLPMediator::__thread_reg] curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
		curl_easy_cleanup(handle);
		return;
	}

	if (res == CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		regConnertState = CONNERTSTATE_COMPLETED;

		rapidjson::Document doc;
		doc.Parse<0>(regConnertData.c_str());
		if (doc.HasParseError())
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_reg]cannot parse,json is {%s}", regConnertData.c_str());
			curl_easy_cleanup(handle);
			return;
		}
		if ((!doc.HasMember("succeed")) || doc["succeed"].GetBool() == false)
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_reg]login operator fail,json is {%s}", regConnertData.c_str());
			curl_easy_cleanup(handle);
			return;
		}
	}
	regSuccessed = true;
	curl_easy_cleanup(handle);
}

size_t LLPMediator::__thread_reg_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;
	regConnertData.append(p, p + (size*nmemb));
	return nmemb*size;
}
void LLPMediator::reg(std::string email, std::string password, std::string reg_code, std::string username,int timeout)
{
	regConnertState = CONNERTSTATE_CONNERTING;
	regConnertData = "";
	regSuccessed = false;
	
	log("[HereticTrainer][Notice][LLPMediator::reg]register operator username is{%s},password is{%s},timeout is {%d}", username.c_str(), password.c_str(),timeout);
	std::thread t(std::bind(&LLPMediator::__thread_reg, this, email,password, reg_code, username, timeout));
	t.detach();
}
int LLPMediator::getRegConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return regConnertState;
}
bool LLPMediator::isRegSuccessed()
{
//	std::lock_guard<std::mutex> m(mtx);
	return regSuccessed;
}
void LLPMediator::loadCategory(int timeout)
{
	loadCategoryConnertData = "";
	loadCategoryConnertState = CONNERTSTATE_CONNERTING;
	categorys.clear();
	loadCategorySuccessed = false;
	log("[HereticTrainer][Notice][LLPMediator::loadCategory ]loadCategory operator,timeout is {%d}",timeout);
	std::thread t(std::bind(&LLPMediator::__thread_loadCategory, this, timeout));
	t.detach();
}
int LLPMediator::getLoadCategoryConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadCategoryConnertState;
}
bool LLPMediator::isLoadCategorySuccessed()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadCategorySuccessed;
}
std::vector<Category> LLPMediator::getCategorys()
{
	return categorys;
}
void LLPMediator::__thread_loadCategory(int timeout)
{
	CURL *handle = curl_easy_init();

	curl_easy_setopt(handle, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadCategory_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(handle, CURLOPT_URL, "https://m.tianyi9.com/API/getcategory?");
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);

	CURLcode res;
	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadCategoryConnertState= CONNERTSTATE_ERROR;
		log("[Heretic][Error][LLPMediator::__thread_loadCategory] curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
		curl_easy_cleanup(handle);
		return;
	}
	if (res== CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadCategoryConnertState = CONNERTSTATE_COMPLETED;

		rapidjson::Document doc;
		doc.Parse<0>(loadCategoryConnertData.c_str());
		if (doc.HasParseError())
		{ 
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadCategory]cannot parse,json is {%s}", loadCategoryConnertData.c_str());
			curl_easy_cleanup(handle);
			return;
		}
		if ((!doc.HasMember("succeed")) || doc["succeed"].GetBool() == false)
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadCategory]login operator fail,json is {%s}", loadCategoryConnertData.c_str());
			curl_easy_cleanup(handle);
			return;

		}
		int size = doc["content"]["items"].Size();
		for (int i = 0; i < size; i++)
		{
			int id = doc["content"]["items"][i]["id"].GetInt();
			std::string name = doc["content"]["items"][i]["name"].GetString();
			categorys.push_back(Category(id, name));
		}
				
		
		
	}
	loadCategorySuccessed = true;
	curl_easy_cleanup(handle);
}
size_t __notclassfunction_thread_loadCategory_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadCategory_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadCategory_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;

	loadCategoryConnertData.append(p, p + (size*nmemb));
	return nmemb*size;
}

void LLPMediator::loadLiveList_Featured(int jsonTimeout , int downloadTimeout )
{

	std::string url = "https://m.tianyi9.com/API/getlivelist?";
	url += "type=featured";
	url += "&offset=undefined";
	url += "&limit=undefined";
	if (isLogined())
		url += String::createWithFormat("&uid=%d",loginUid)->_string;
	url += "&category=0";
	if (isLogined())
		url += "&logincookie=" + loginCookie;
	//url += "&timestamp=1438499519058";

	log("[HereticTrainer][Notice][ LLPMediator::loadLiveList_Featured]url is {%s},jsontimeout is {%d},downloadtimeout is {%d}", url.c_str(),jsonTimeout,downloadTimeout);
	loadLiveList(url, jsonTimeout, downloadTimeout);


}

void LLPMediator::loadLiveList_Public(int offset, int limit, int jsonTimeout, int downloadTimeout )
{

	std::string url = "https://m.tianyi9.com/API/getlivelist?";
	url += "type=public";
	url += String::createWithFormat("&offset=%d", offset)->_string;
	url += String::createWithFormat("&limit=%d", limit)->_string;
	if (isLogined())
		url += String::createWithFormat("&uid=%d", loginUid)->_string;
	url += "&category=0";
	if (isLogined())
		url += "&logincookie=" + loginCookie;
	//url += "&timestamp=1438499519058";
	log("[HereticTrainer][Notice][LLPMediator:: loadLiveList_Public]url is {%s},jsontimeout is {%d},downloadtimeout is {%d}", url.c_str(), jsonTimeout, downloadTimeout);
	loadLiveList(url, jsonTimeout, downloadTimeout);
}

void LLPMediator::loadLiveList_Category(int categoryID, int offset, int limit, int jsonTimeout , int downloadTimeout )
{
	
	std::string url = "https://m.tianyi9.com/API/getlivelist?";
	url += "type=category";
	url += String::createWithFormat("&offset=%d", offset)->_string;
	url += String::createWithFormat("&limit=%d", limit)->_string;
	if (isLogined())
		url += String::createWithFormat("&uid=%d", loginUid)->_string;
	url += String::createWithFormat("&category=%d",categoryID)->_string;
	if (isLogined())
		url +=( "&logincookie=" + loginCookie);
	//url += "&timestamp=1438499519058";
	log("[HereticTrainer][Notice][ LLPMediator::loadLiveList_Category]url is {%s},jsontimeout is {%d},downloadtimeout is {%d},categoryID is {%d}", url.c_str(), jsonTimeout, downloadTimeout, categoryID);
	loadLiveList(url, jsonTimeout, downloadTimeout);
}
void LLPMediator::loadLiveList_Favorites(int offset, int limit, int jsonTimeout, int downloadTimeout )
{
	if (!isLogined())return;
	std::string url = "https://m.tianyi9.com/API/getFavorites?";
	std::string xsign = "";
	url += "type=favorite";
	xsign += "type=favorite";
	url += String::createWithFormat("&offset=%d", offset)->_string;
	xsign += String::createWithFormat("&offset=%d", offset)->_string;
	url += String::createWithFormat("&limit=%d", limit)->_string;
	xsign += String::createWithFormat("&limit=%d", limit)->_string;
	url += String::createWithFormat("&uid=%d", loginUid)->_string;
	xsign += String::createWithFormat("&uid=%d", loginUid)->_string;
	url += "&category=1";
	xsign += "&category=1";
	url += "&logincookie=" + loginCookie;
	xsign += "&logincookie=" + loginCookie;
	
	long long timestamp = time(NULL)*1000;
	url += String::createWithFormat("&timestamp=%lld", timestamp)->_string;
	xsign += String::createWithFormat("&timestamp=%lld", timestamp)->_string;
	xsign = makeXSign(xsign + loginToken);
	//log("token is {%s}",loginToken);
	log("[HereticTrainer][Notice][ LLPMediator::loadLiveList_Favorites]url is {%s},jsontimeout is {%d},downloadtimeout is {%d},xSign is {%s}", url.c_str(), jsonTimeout, downloadTimeout, xsign.c_str());
	loadLiveList(url, jsonTimeout, downloadTimeout, xsign);
}
void LLPMediator::loadLiveList_Search(std::string keyword, int offset, int limit, int jsonTimeout , int downloadTimeout )
{
	std::string url = "https://m.tianyi9.com/API/search?";
	url += "keyword=" + keyword;
	url += String::createWithFormat("&offset=%d", offset)->_string;
	url += String::createWithFormat("&limit=%d", limit)->_string;


	if (isLogined())
		url += "&logincookie=" + loginCookie;
	//url += "&timestamp=1438499519058";
	log("[HereticTrainer][Notice][ LLPMediator::loadLiveList_Search]url is {%s},jsontimeout is {%d},downloadtimeout is {%d}", url.c_str(), jsonTimeout, downloadTimeout);
	loadLiveList(url, jsonTimeout, downloadTimeout);
}
size_t __notclassfunction_thread_loadLiveList_json_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadLiveList_json_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadLiveList_json_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;
	//log("%d", size*nmemb);
	loadLiveListJsonData.append(p, p + (size*nmemb));
	return nmemb*size;
}
size_t __notclassfunction_thread_loadLiveList_file_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadLiveList_file_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadLiveList_file_callback(void *buffer, size_t size, size_t nmemb)
{
	//char *p = (char*)buffer;
	if (loadLiveListDownloadingFileHandle)return fwrite(buffer, size, nmemb, loadLiveListDownloadingFileHandle);
	else return 0;
}
void LLPMediator::__thread_loadLiveList(std::string url, int jsonTimeout, int downloadTimeout, std::string xsign)
{


	CURL *handle = curl_easy_init();

	curl_easy_setopt(handle, CURLOPT_TIMEOUT, jsonTimeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveList_json_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_slist *plist = curl_slist_append(NULL, ("x-sign:"+xsign).c_str());
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, plist);
	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);


	CURLcode res;
	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadLiveListConnertState = CONNERTSTATE_ERROR;
		log("[Heretic][Error][LLPMediator::__thread_loadLiveList] curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
		curl_easy_cleanup(handle);
		return;
	}

		rapidjson::Document doc;
		doc.Parse<0>(loadLiveListJsonData.c_str());

		if (doc.HasParseError())
		{
//			std::lock_guard<std::mutex> m(mtx);
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveList]cannot parse,json is {%s}", loadLiveListJsonData.c_str());
			loadLiveListConnertState = CONNERTSTATE_COMPLETED;
			curl_easy_cleanup(handle);
			return;
		}
		if ((!doc.HasMember("succeed")) || doc["succeed"].GetBool() == false)
		{
//			std::lock_guard<std::mutex> m(mtx);
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveList]login operator fail,json is {%s}", loadLiveListJsonData.c_str());
			loadLiveListConnertState = CONNERTSTATE_COMPLETED;
			curl_easy_cleanup(handle);
			return;
		}


		rapidjson::Value& content = doc["content"];
		
		livelist.count = content["count"].GetInt();
		rapidjson::Value& items = content["items"];
		for (int i = 0; i < items.Size(); i++)
		{
			LiveListItem item;
			item.cover_path = items[i]["cover_path"].GetString();
			item.upload_user.username = items[i]["upload_user"]["username"].GetString();
			if (items[i]["upload_user"].HasMember("avatar_path"))
			
				if(!items[i]["upload_user"]["avatar_path"].IsNull())
			item.upload_user.avatar_path = items[i]["upload_user"]["avatar_path"].GetString();
			item.upload_user.id = items[i]["upload_user"]["id"].GetInt();
			item.level = items[i]["level"].GetInt();
			item.artist = items[i]["artist"].GetString();
			item.live_name = items[i]["live_name"].GetString();
			if (items[i].HasMember("memberonly"))
			item.memberonly = items[i]["memberonly"].GetBool();
			if (items[i].HasMember("click_count"))
				item.click_count = items[i]["click_count"].GetInt();
			else
				item.click_count = -1;
			item.live_id = items[i]["live_id"].GetString();
			livelist.items.push_back(item);

		}

		log("[HereticTrainer][Notice][LLPMediator::__thread_loadLiveList]load livelist json completed,count is {%d}", livelist.items.size());

		//log("hello");
		for (int i = 0; i < livelist.items.size(); i++)
		{
			//log("%d\n",i);
			std::string filePath = CrossPlatformHelper::getDownloadDirectory() + livelist.items[i].cover_path;
			//log("[Heretic][Notice][ LLPMediator::__thread_loadLiveList]will download {%s} to {%s}", livelist.items[i].cover_path.c_str(), filePath.c_str());
			if (FileUtils::getInstance()->isFileExist(filePath))
			{
				log("[HereticTrainer][Notice][LLPMediator::__thread_loadLiveList]file {%s} is exist", filePath.c_str());
				continue;
			}
			loadLiveListDownloadingFileHandle = fopen(filePath.c_str(), "wb");

			if (!loadLiveListDownloadingFileHandle)
			{
//				std::lock_guard<std::mutex> m(mtx);
				log("[Heretic][Error][ LLPMediator::__thread_loadLiveList]cannot open file,file path is {%s},index is {%d}", filePath.c_str(), i);
				loadLiveListConnertState = CONNERTSTATE_COMPLETED;
				curl_easy_cleanup(handle);
				return;

			}
			curl_easy_setopt(handle, CURLOPT_TIMEOUT, downloadTimeout);
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveList_file_callback);
			url = String::createWithFormat("https://m.tianyi9.com/upload/%s", livelist.items[i].cover_path.c_str())->_string;
			curl_easy_setopt(handle, CURLOPT_URL, url.c_str());



			if ((res = curl_easy_perform(handle)) != CURLE_OK)
			{

//				std::lock_guard<std::mutex> m(mtx);
				
				fclose(loadLiveListDownloadingFileHandle);
				remove(filePath.c_str());
				loadLiveListDownloadingFileHandle = NULL;
				loadLiveListConnertState = CONNERTSTATE_ERROR;
				log("[Heretic][Error][LLPMediator::__thread_loadLiveList] curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
				curl_easy_cleanup(handle);
				return;

			}
			fclose(loadLiveListDownloadingFileHandle);
			loadLiveListDownloadingFileHandle = NULL;

		}

	

	log("[HereticTrainer][Notice][LLPMediator::__thread_loadLiveList]load livelist  completed");
	loadLiveListSuccessed = true;
	loadLiveListConnertState = CONNERTSTATE_COMPLETED;
	curl_easy_cleanup(handle);
}
void LLPMediator::loadLiveList(std::string url, int jsonTimeout, int downloadTimeout,std::string xsign)
{
	loadLiveListJsonData = "";
	loadLiveListConnertState = CONNERTSTATE_CONNERTING;
	loadLiveListSuccessed = false;
	livelist.count = 0;
	livelist.items.clear();

	std::thread t(std::bind(&LLPMediator::__thread_loadLiveList, this,url,jsonTimeout,downloadTimeout,xsign));
	t.detach();
}
int LLPMediator::getLoadLiveListConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveListConnertState;
}
bool LLPMediator::isLoadLiveListSuccessed()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveListSuccessed;
}
LiveList LLPMediator::getLiveList()
{
//	std::lock_guard<std::mutex> m(mtx);
	return livelist;
}





void LLPMediator::loadLiveDetails(std::string liveID ,int timeout)
{
	loadLiveDetailsConnertData = "";
	loadLiveDetailsConnertState = CONNERTSTATE_CONNERTING;

	loadLiveDetailsSuccessed = false;
	log("[HereticTrainer][Notice][ loadLiveDetails]timeout is {%d}", timeout);
	std::thread t(std::bind(&LLPMediator::__thread_loadLiveDetails, this,liveID, timeout));
	t.detach();
}
int LLPMediator::getLoadLiveDetailsConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveDetailsConnertState;
}
bool LLPMediator::isLoadLiveDetailsSuccessed()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveDetailsSuccessed;
}
LiveDetails LLPMediator::getLiveDetails()
{
	return liveDetails;
}
void LLPMediator::__thread_loadLiveDetails(std::string liveID,int timeout)
{
	CURL *handle = curl_easy_init();

	curl_easy_setopt(handle, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveDetails_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	std::string url = "https://m.tianyi9.com/API/getlive?";
	url += "live_id=" + liveID;
	if (isLogined())
	{
		url += "&logincookie=" + loginCookie;
	}
	//url += "&timestamp=";
	
	curl_easy_setopt(handle, CURLOPT_URL,url.c_str());
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
	log("[HereticTrainer][Notice][  LLPMediator::__thread_loadLiveDetails]url is {%s}", url.c_str());
	CURLcode res;
	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadLiveDetailsConnertState = CONNERTSTATE_ERROR;
		log("[Heretic][Error][LLPMediator::__thread_loadLiveDetails] curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
		curl_easy_cleanup(handle);
		return;
	}
	if (res == CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadLiveDetailsConnertState= CONNERTSTATE_COMPLETED;

		rapidjson::Document doc;
		doc.Parse<0>(loadLiveDetailsConnertData.c_str());
		if (doc.HasParseError())
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveDetails]cannot parse,json is {%s}", loadLiveDetailsConnertData.c_str());
			curl_easy_cleanup(handle);
			return;

		}
		if ((!doc.HasMember("succeed")) || doc["succeed"].GetBool() == false)
		{
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveDetails]login operator fail,json is {%s}", loadLiveDetailsConnertData.c_str());
			curl_easy_cleanup(handle);
			return;

		}

				
		rapidjson::Value& content = doc["content"];
		liveDetails.category.id = content["category"]["id"].GetInt();
		liveDetails.category.name = content["category"]["name"].GetString();
		liveDetails.bgimg_file = content["bgimg_file"].GetString();
		liveDetails.cover_path = content["cover_path"].GetString();
		liveDetails.upload_user.username = content["upload_user"]["username"].GetString();
		liveDetails.upload_user.avatar_path = content["upload_user"]["avatar_path"].GetString();
		liveDetails.upload_user.id = content["upload_user"]["id"].GetInt();
		liveDetails.upload_user.post_count = content["upload_user"]["post_count"].GetInt();			
		liveDetails.click_count = content["click_count"].GetInt();
		liveDetails.live_info = content["live_info"].GetString();
		liveDetails.artist = content["artist"].GetString();
		liveDetails.like_count = content["like_count"].GetInt();
		liveDetails.state = content["state"].GetString();
		liveDetails.bgm_file = content["bgm_file"].GetString();
		liveDetails.live_name = content["live_name"].GetString();
		liveDetails.memberonly = content["memberonly"].GetBool();
		liveDetails.live_setting = content["live_setting"].GetString();
		liveDetails.live_id = content["live_id"].GetString();
		liveDetails.level = content["level"].GetInt();
		liveDetails.map_file = content["map_file"].GetString(); 
		loadLiveDetailsSuccessed = true;
	}

	curl_easy_cleanup(handle);
}
size_t __notclassfunction_thread_loadLiveDetails_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadLiveDetails_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadLiveDetails_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;
	
	loadLiveDetailsConnertData.append(p, p + (size*nmemb));
	return nmemb*size;
}


void LLPMediator::loadLiveData(std::string liveID, std::string map_file, std::string bgimg_file, std::string bgm_file, int jsonTimeout, int downloadTimeout)
{
	liveJson= "";
	loadLiveDataConnertState = CONNERTSTATE_CONNERTING;
	loadLiveDataProgress = 0;
	loadLiveDataSuccessed = false;
	loadLiveDataBgmFileHandle = NULL;
	loadLiveDataBgimgFileHandle = NULL;
	log("[HereticTrainer][Notice][  LLPMediator::loadLiveData]liveid is {%s},map_file id is {%s},bgimg_file id is {%s},bgm_file id is {%s},jsonTimeout is {%d},downloadTimeout is {%d}"
		, liveID.c_str()
		, map_file.c_str()
		, bgimg_file.c_str()
		, bgm_file.c_str()
		, jsonTimeout
		, downloadTimeout);

	std::thread t(std::bind(&LLPMediator::__thread_loadLiveData, this, liveID,map_file,bgimg_file,bgm_file, jsonTimeout,downloadTimeout));
	t.detach();
}
size_t __notclassfunction_thread_loadLiveData_bgimg_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadLiveData_bgimg_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadLiveData_bgimg_callback(void *buffer, size_t size, size_t nmemb)
{
	if (loadLiveDataBgimgFileHandle)return fwrite(buffer, size, nmemb, loadLiveDataBgimgFileHandle);
	else return 0;
}
 size_t __notclassfunction_thread_loadLiveData_bgm_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	 LLPMediator* p = (LLPMediator*)userp;
	 return p->__thread_loadLiveData_bgm_callback(buffer, size, nmemb);
}
 size_t LLPMediator::__thread_loadLiveData_bgm_callback(void *buffer, size_t size, size_t nmemb)
{
	 if (loadLiveDataBgmFileHandle)return fwrite(buffer, size, nmemb, loadLiveDataBgmFileHandle);
	 else return 0;

}
 size_t __notclassfunction_thread_loadLiveData_liveJson_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	 LLPMediator* p = (LLPMediator*)userp;
	 return p->__thread_loadLiveData_liveJson_callback(buffer, size, nmemb);
}
size_t LLPMediator::__thread_loadLiveData_liveJson_callback(void *buffer, size_t size, size_t nmemb)
{
	char *p = (char*)buffer;

	liveJson.append(p, p + (size*nmemb));
	return nmemb*size;
}
int   __notclassfunction_thread_loadLiveData_bgm_procress_callback(void *userp, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
	LLPMediator* p = (LLPMediator*)userp;
	return p->__thread_loadLiveData_bgm_procress_callback(TotalToDownload, NowDownloaded);
}
int  LLPMediator::__thread_loadLiveData_bgm_procress_callback(double TotalToDownload, double NowDownloaded)
{
//	std::lock_guard<std::mutex> m(mtx);
	loadLiveDataProgress = 30 + (NowDownloaded / TotalToDownload)*70;
	return 0;
}
void LLPMediator::__thread_loadLiveData(std::string liveID, std::string map_file, std::string bgimg_file, std::string bgm_file, int jsonTimeout, int downloadTimeout)
{
	CURL *handle = curl_easy_init();

	curl_easy_setopt(handle, CURLOPT_TIMEOUT, jsonTimeout);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveData_liveJson_callback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
	std::string url = "https://m.tianyi9.com/API/fo?";
	url += "live_id=" + liveID;
	url += "&file_id=" + map_file;
	if (isLogined())
	{
		url += "&logincookie=" + loginCookie;
	}
	//url += "&timestamp=";
	log("[HereticTrainer][Notice][ LLPMediator::__thread_loadLiveData]url is{%s}", url.c_str());

	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);

	CURLcode res;
	if ((res = curl_easy_perform(handle)) != CURLE_OK)
	{
//		std::lock_guard<std::mutex> m(mtx);
		loadLiveDataConnertState = CONNERTSTATE_ERROR;
		log("[Heretic][Error][LLPMediator::__thread_loadLiveData]livejson, curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));

		curl_easy_cleanup(handle);
		return;
	}
//	mtx.lock();
	loadLiveDataProgress = 10;
//	mtx.unlock();
	log("[HereticTrainer][Notice][ LLPMediator::__thread_loadLiveData]load livejson completed");
	std::string bgimg_file_path = (CrossPlatformHelper::getDownloadDirectory() + bgimg_file + ".jpg");
	if (!FileUtils::getInstance()->isFileExist(bgimg_file_path))
	{

		loadLiveDataBgimgFileHandle = fopen(bgimg_file_path.c_str(), "wb");
		if (!loadLiveDataBgimgFileHandle)
		{
//			std::lock_guard<std::mutex> m(mtx);
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveData]cannot open bgimgfile,file {%s}", bgimg_file_path.c_str());
			loadLiveDataConnertState = CONNERTSTATE_COMPLETED;
			curl_easy_cleanup(handle);
			return;

		}

		url = "https://m.tianyi9.com/API/fo?";
		url += "live_id=" + liveID;
		url += "&file_id=" + bgimg_file;
		if (isLogined())
		{
			url += "&logincookie=" + loginCookie;
		}
		log("[HereticTrainer][Notice][ LLPMediator::__thread_loadLiveData]load bgimg file ,url is {%s}",url.c_str());
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveData_bgimg_callback);
		curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, downloadTimeout);
		if ((res = curl_easy_perform(handle)) != CURLE_OK)
		{
		
//			std::lock_guard<std::mutex> m(mtx);
			fclose(loadLiveDataBgimgFileHandle);
			remove(bgimg_file_path.c_str());
			loadLiveDataBgimgFileHandle = NULL;
			loadLiveDataConnertState = CONNERTSTATE_ERROR;
			log("[Heretic][Error][ LLPMediator::__thread_loadLiveData]bgimg ,curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
			curl_easy_cleanup(handle);
			return;
		}
		fclose(loadLiveDataBgimgFileHandle);
		loadLiveDataBgimgFileHandle = NULL;

	}
//	mtx.lock();
	loadLiveDataProgress = 30;
//	mtx.unlock();
	log("[HereticTrainer][Notice][ LLPMediator::__thread_loadLiveData]load bgimg completed");
	std::string bgm_file_path = (CrossPlatformHelper::getDownloadDirectory() + bgm_file + ".mp3");
	if (!FileUtils::getInstance()->isFileExist(bgm_file_path))
	{

		loadLiveDataBgmFileHandle = fopen(bgm_file_path.c_str(), "wb");
		if (!loadLiveDataBgmFileHandle)
		{
//			std::lock_guard<std::mutex> m(mtx);
			log("[HereticTrainer][Error][ LLPMediator::__thread_loadLiveData]cannot open bgmgfile,file {%s}", bgm_file_path.c_str());
			loadLiveDataConnertState = CONNERTSTATE_COMPLETED;
			curl_easy_cleanup(handle);
			return;

		}

		url = "https://m.tianyi9.com/API/fo?";
		url += "live_id=" + liveID;
		url += "&file_id=" + bgm_file;
		if (isLogined())
		{
			url += "&logincookie=" + loginCookie;
		}
		log("[HereticTrainer][Notice][ LLPMediator::__thread_loadLiveData]load bgm file ,url is {%s}", url.c_str());
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __notclassfunction_thread_loadLiveData_bgm_callback);
		curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, downloadTimeout);
		curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(handle, CURLOPT_PROGRESSDATA, (void*)this);
		curl_easy_setopt(handle, CURLOPT_PROGRESSFUNCTION, __notclassfunction_thread_loadLiveData_bgm_procress_callback);
		if ((res = curl_easy_perform(handle)) != CURLE_OK)
		{

//			std::lock_guard<std::mutex> m(mtx);
			fclose(loadLiveDataBgmFileHandle);
			remove(bgm_file_path.c_str());
			loadLiveDataBgmFileHandle = NULL;
			loadLiveDataConnertState = CONNERTSTATE_ERROR;
			log("[Heretic][Error][ LLPMediator::__thread_loadLiveData]bgm ,curl_easy_perform operator failed,error infomation is {%s}", curl_easy_strerror(res));
			curl_easy_cleanup(handle);
			return;
		}
		fclose(loadLiveDataBgmFileHandle);
		loadLiveDataBgmFileHandle = NULL;

	}
//	mtx.lock();
	loadLiveDataProgress = 100;
//	mtx.unlock();
	log("[HereticTrainer][Notice][LLPMediator::__thread_loadLiveData ]load livedata completed");
	loadLiveDataConnertState = CONNERTSTATE_COMPLETED;
	loadLiveDataSuccessed = true;

		
	

}
int LLPMediator::getLoadLiveDataConnertState()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveDataConnertState;
}
bool LLPMediator::isLoadLiveDataSuccessed()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveDataSuccessed;
}
int LLPMediator::getLoadLiveProgress()
{
//	std::lock_guard<std::mutex> m(mtx);
	return loadLiveDataProgress;
}
std::string LLPMediator::getLiveJson()
{
//	std::lock_guard<std::mutex> m(mtx);
	return liveJson;
}
bool LLPMediator::parseLLPBeatMapJson(LiveInfo &liveInfo, std::string jsonText)
{
	LiveInfo ret = liveInfo;
	for (int i = 0; i < 9; i++)ret.beats[i].clear();

	
	rapidjson::Document doc;
	doc.Parse<0>(jsonText.c_str());
	if (doc.HasParseError())return false;
	double speed = 1.6;
	if (doc.HasMember("speed"))speed = doc["speed"].GetDouble();
	//处理偏移
	double offsettime = 0;
	if (doc.HasMember("offsettime"))offsettime = doc["offsettime"].GetDouble();

	rapidjson::Value& valLane = doc["lane"];

	if (valLane.IsArray())
	{
		for (unsigned int i = 0; i < valLane.Size(); i++)
		{

			const rapidjson::Value &valArray = valLane[i];
			for (unsigned int j = 0; j < valArray.Size(); j++)
			{
				const rapidjson::Value &val = valArray[j];
				double begintime = val["starttime"].GetDouble();
				double endtime = val["endtime"].GetDouble();
				bool longnote = val["longnote"].GetBool();
				bool parallel = val["parallel"].GetBool();
				int lane = val["lane"].GetInt();
				Beat tmp;
				tmp.beginTime = (begintime + offsettime) / 1000;
				tmp.type = 0;
				if (longnote)tmp.type |= Beat::TYPE_LONG;
				if (parallel)tmp.type |= Beat::TYPE_SAMETIME;
				tmp.pos = lane;
				tmp.endTime = (endtime + offsettime) / 1000;
				if (lane >= 0 && lane <= 8)
				{
					ret.beats[tmp.pos].push_back(tmp);
				}
					

			}

		}
	}
	//beat数量
	int sum = 0;
	for (int i = 0; i <= 8; i++)
	{
		sort(ret.beats[i].begin(), ret.beats[i].end());
		sum += ret.beats[i].size();
	}
	//0beat 的live显然没有什么意义？纯听歌？
	if (!sum)return false;
	liveInfo = ret;
	return true;
}