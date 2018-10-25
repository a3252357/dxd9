#pragma once
#include "Seting.h"
class LogSystem
{
private:
	LogSystem();
	~LogSystem();
	LogSystem(const LogSystem&);
	LogSystem& operator=(const LogSystem&);
	static LogSystem *instance;
public:
	static	LogSystem * getInstance();
	HRESULT InitLog();
	HRESULT DebugLog(string _logmes);
};