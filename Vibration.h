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
	// 通过 IState 继承
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;

	// 通过 IState 继承
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window) override;

	// 通过 IState 继承
	virtual HRESULT Render() override;
};

