#include "TestManger.h"


TestManger::TestManger()
{
}


TestManger::~TestManger()
{
}
HRESULT TestManger::Init()
{
	state = new FristCommonTset(this);
	return E_NOTIMPL;
}
