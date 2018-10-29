#include "StateControl.h"


StateControl::StateControl()
{
}


StateControl::~StateControl()
{
}

HRESULT StateControl::Update(float delta)
{
	return S_OK;
}

HRESULT StateControl::SetState(shared_ptr<IState> IState_1)
{
	m_IState = IState_1;
	return S_OK;
}
