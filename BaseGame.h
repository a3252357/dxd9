#pragma once  
#include "Seting.h"
#include "IState.h"
#include "BaseUI.h"
class BaseGame
{
public:
	IState * state;
	BaseUI * ui;
	virtual HRESULT Update() = 0;
	virtual HRESULT Init() = 0;
	virtual HRESULT Render() = 0;
};