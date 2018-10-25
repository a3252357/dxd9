#include "StateControl.h"


StateControl::StateControl()
{
}


StateControl::~StateControl()
{
}

HRESULT StateControl::Update(float delta)
{
	return E_NOTIMPL;
}

HRESULT StateControl::SetState(shared_ptr<IState> IState_1)
{
	m_IState = IState_1;
	return E_NOTIMPL;
}
