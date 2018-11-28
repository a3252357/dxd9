#pragma once
#include "IState.h"
#include "AnimationFrame.h"
#include "BaseGame.h"
class GameMenuState :
	public IState
{
public:
	GameMenuState(BaseGame *_game);
	~GameMenuState();
	BaseGame *game;
	AnimationFrame * background;
	// 通过 IState 继承
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;

	// 通过 IState 继承
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window) override;

	// 通过 IState 继承
	virtual HRESULT Render() override;
};

