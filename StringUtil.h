#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include "Seting.h"
static class StringUtil{
public:
	static char* ConvertLPWSTRToLPSTR(LPWSTR lpwszStrIn);
	static LPWSTR ConvertLPSTRToLPWSTR(char* lpwszStrIn);
};
#endif