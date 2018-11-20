#pragma once  
#include "Seting.h"
static class StringUtil{
public:
	static char* ConvertLPWSTRToLPSTR(LPWSTR lpwszStrIn);
	static LPWSTR ConvertLPSTRToLPWSTR(const char* lpwszStrIn);
	static LPCWSTR ConvertstringToLPCWSTR(std::string orig);
	static wchar_t * MBCS2Unicode(wchar_t * buff, const char * str);
	static char * Unicode2MBCS(char * buff, const wchar_t * str);
	static wstring str2wstr(string str);
	static string wstr2str(wstring wstr);
	static int wputs(wstring wstr);
	static int wputs(const wchar_t * wstr);
	static wchar_t * UTF8ToUnicode(const char * str);
	static char * UnicodeToUTF8(const wchar_t * str);
};