#pragma once
#include "IState.h"
#include "CommonTestUI.h"
#include "BaseGame.h"
class FristCommonTset :
	public IState
{
public:
	FristCommonTset(BaseGame * _game);
	~FristCommonTset();
	BaseGame *game;
	// Í¨¹ý IState ¼Ì³Ð
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;
};

