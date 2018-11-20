#include "StringUtil.h"
char* StringUtil::ConvertLPWSTRToLPSTR(LPWSTR lpwszStrIn)
{
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);

		// Double NULL Termination
		int nOutputStrLen = WideCharToMultiByte(CP_UTF8, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];

		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_UTF8, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}
LPWSTR StringUtil::ConvertLPSTRToLPWSTR(const char* lpwszStrIn)
{
	int dwLen = strlen(lpwszStrIn) + 1;
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, lpwszStrIn, dwLen, NULL, 0);//算出合适的长度 
	LPWSTR lpszPath = new WCHAR[dwLen];
	MultiByteToWideChar(CP_UTF8, 0, lpwszStrIn, dwLen, lpszPath, nwLen);
	return lpszPath;
}
LPCWSTR StringUtil::ConvertstringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}




wchar_t * StringUtil::MBCS2Unicode(wchar_t * buff, const char * str)

{

	wchar_t * wp = buff;

	char * p = (char *)str;

	while (*p)

	{

		if (*p & 0x80)

		{

			*wp = *(wchar_t *)p;

			p++;

		}

		else {

			*wp = (wchar_t)*p;

		}

		wp++;

		p++;

	}

	*wp = 0x0000;

	return buff;

}



char * StringUtil::Unicode2MBCS(char * buff, const wchar_t * str)

{

	wchar_t * wp = (wchar_t *)str;

	char * p = buff, *tmp;

	while (*wp) {

		tmp = (char *)wp;

		if (*wp & 0xFF00) {

			*p = *tmp;

			p++;tmp++;

			*p = *tmp;

			p++;

		}

		else {

			*p = *tmp;

			p++;

		}

		wp++;

	}

	*p = 0x00;

	return buff;

}



wstring StringUtil::str2wstr(string str)

{

	size_t len = str.size();

	wchar_t * b = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));

	MBCS2Unicode(b, str.c_str());

	wstring r(b);

	free(b);

	return r;

}



string StringUtil::wstr2str(wstring wstr)

{

	size_t len = wstr.size();

	char * b = (char *)malloc((2 * len + 1) * sizeof(char));

	Unicode2MBCS(b, wstr.c_str());

	string r(b);

	free(b);

	return r;

}



int StringUtil::wputs(wstring wstr)

{

	wputs(wstr.c_str());

	return 0;

}



int StringUtil::wputs(const wchar_t * wstr)

{

	int len = wcslen(wstr);

	char * buff = (char *)malloc((len * 2 + 1) * sizeof(char));

	Unicode2MBCS(buff, wstr);

	printf("%s", buff);

	free(buff);

	return 0;

}

wchar_t * StringUtil::UTF8ToUnicode(const char* str)
{
	int textlen;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return result;
}

char * StringUtil::UnicodeToUTF8(const wchar_t* str)
{
	char* result;
	int textlen;
	textlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	result = (char *)malloc((textlen + 1) * sizeof(char));
	memset(result, 0, sizeof(char) * (textlen + 1));
	WideCharToMultiByte(CP_UTF8, 0, str, -1, result, textlen, NULL, NULL);
	return result;
}