#pragma once
#include "Seting.h"
class IState
{
public:
	//IState();
	virtual ~IState() {};
	virtual HRESULT Update() =0;
	virtual HRESULT ChangeState()=0;
};
