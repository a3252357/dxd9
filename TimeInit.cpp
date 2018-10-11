#include "TimeInit.h"
shared_ptr<TimeWheel> TimeInit::time;

HRESULT TimeInit::Time_Init()
{
	time = make_shared<TimeWheel>();
	return S_OK;
}
