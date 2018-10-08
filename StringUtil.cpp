#include "StringUtil.h"
char* StringUtil::ConvertLPWSTRToLPSTR(LPWSTR lpwszStrIn)
{
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);

		// Double NULL Termination
		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];

		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}
LPWSTR StringUtil::ConvertLPSTRToLPWSTR(char* lpwszStrIn)
{
	int dwLen = strlen(lpwszStrIn) + 1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, lpwszStrIn, dwLen, NULL, 0);//算出合适的长度 
	LPWSTR lpszPath = new WCHAR[dwLen];
	MultiByteToWideChar(CP_ACP, 0, lpwszStrIn, dwLen, lpszPath, nwLen);
	return lpszPath;
}