#include "LogSystem.h"
LogSystem* LogSystem::instance;
LogSystem::LogSystem()
{
	InitLog();
}
LogSystem* LogSystem::getInstance()
{
	if (instance == NULL)
	{
		if (instance == NULL)
		{
			instance = new LogSystem();
		}
	}

	return instance;
}


LogSystem::~LogSystem()
{
}

HRESULT LogSystem::InitLog()
{
	log4cplus::initialize();
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(MY_LOG_FILE_PATH));
	logger = Logger::getRoot();
	return S_OK;
}
