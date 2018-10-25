#pragma once
#include "Seting.h"
#include "IState.h"
class StateControl
{
public:
	StateControl();
	~StateControl();
	HRESULT Update(float delta);
	HRESULT SetState(shared_ptr<IState> IState_1);
private:
	shared_ptr<IState> m_IState;
};

