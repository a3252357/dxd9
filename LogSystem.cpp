#include "LogSystem.h"


LogSystem::LogSystem()
{
}
LogSystem* LogSystem::getInstance()
{
	if (instance == NULL)
	{
		lock();
		if (instance == NULL)
		{
			instance = new LogSystem();
		}
		unlock();
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
