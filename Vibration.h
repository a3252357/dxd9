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
	// Í¨¹ý IState ¼Ì³Ð
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;
};

