#include "LogSystem.h"

LogSystem* LogSystem::instance;
LogSystem::LogSystem()
{
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
	return E_NOTIMPL;
}

HRESULT LogSystem::DebugLog(string _logmes)
{
	return E_NOTIMPL;
}
