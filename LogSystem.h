#pragma once
#include "Seting.h"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h> 
#include <log4cplus/layout.h> 
#include <log4cplus/loggingmacros.h> 
#include <log4cplus/helpers/stringhelper.h> 
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
#define MY_LOG_FILE_PATH "F:/ConsoleApplication2/conf/logconfig.properites"
#define DEBUG__LOG(str) 	LOG4CPLUS_DEBUG(LogSystem::getInstance()->logger, str);
class LogSystem
{
private:
	LogSystem();
	~LogSystem();
	LogSystem(const LogSystem&);
	LogSystem& operator=(const LogSystem&);
	static LogSystem *instance;
public:
	Logger logger;
	static	LogSystem * getInstance();
	HRESULT InitLog();
};