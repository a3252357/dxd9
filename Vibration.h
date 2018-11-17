#pragma once
#include "IState.h"
#include "VibrationUI.h"
#include "BaseGame.h"
class Vibration:
	public IState
{
public:
	Vibration(BaseGame *_game);
	~Vibration();
	BaseGame *game;
	// ͨ�� IState �̳�
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;
};

