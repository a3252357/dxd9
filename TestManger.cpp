#include "TestManger.h"


TestManger::TestManger()
{
}


TestManger::~TestManger()
{
}

HRESULT TestManger::Update()
{
	state->Update();
	ui->Update();
	return E_NOTIMPL;
}

HRESULT TestManger::Render()
{
	return E_NOTIMPL;
}

HRESULT TestManger::Init()
{
	state = new FristCommonTset(this);
	return E_NOTIMPL;
}
