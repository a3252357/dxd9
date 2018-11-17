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
	// ͨ�� IState �̳�
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;
};

