#include"CrossPlatformHelper.h"



std::string CrossPlatformHelper::getDownloadDirectory()
{
#if (CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	std::string path[] = { "/mnt/sdcard/", "/sdcard/", "/mnt/storage/sdcard/", "/storage/emulated/0/", "/storage/emulated/1/", "/storage/extSdCard/" };
	for (auto i : path)
	if (FileUtils::getInstance()->isDirectoryExist(i))
	{
		if (!FileUtils::getInstance()->isDirectoryExist(i + "heretictrainer/"))
			FileUtils::getInstance()->createDirectory(i + "heretictrainer/");
		return (i + "heretictrainer/");
	}
#endif
	if (!FileUtils::getInstance()->isDirectoryExist("heretictrainer/"))
		FileUtils::getInstance()->createDirectory("heretictrainer/");

	return  FileUtils::getInstance()->fullPathForFilename("heretictrainer/");

}


//utf8字符长度1-6，可以根据每个字符第一个字节判断整个字符长度
//0xxxxxxx
//110xxxxx 10xxxxxx
//1110xxxx 10xxxxxx 10xxxxxx
//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//
//定义查找表，长度256，表中的数值表示以此为起始字节的utf8字符长度
unsigned char utf8_look_for_table[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};
#define UTFLEN(x)  utf8_look_for_table[(x)]

//计算str字符数目
int CrossPlatformHelper::getUtf8Length(std::string str)
{
	int clen = str.length();
	int len = 0;

	for (const char *ptr = str.c_str();
		*ptr != 0 && len < clen;
		len++, ptr += UTFLEN((const unsigned char)*ptr));

	return len;
}

//get子串
std::string CrossPlatformHelper::subUtfString(std::string str, unsigned int start, unsigned int end)
{
	int len = getUtf8Length(str);

	if (start >= len) return "";
	if (end > len) end = len;

	const char *sptr = str.c_str();
	for (int i = 0; i < start; ++i, sptr += UTFLEN((const unsigned char)*sptr));

	const char *eptr = sptr;
	for (int i = start; i < end; ++i, eptr += UTFLEN((const unsigned char)*eptr));

	int retLen = eptr - sptr;


	return std::string(sptr,eptr);
}
std::string CrossPlatformHelper::limitString(std::string str, int maxLen)
{
	int len = getUtf8Length(str);
	if (len>maxLen)
	{
		return subUtfString(str, 0, maxLen) + "...";
	}
	else return str;
}