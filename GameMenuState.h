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
	// ͨ�� IState �̳�
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;

	// ͨ�� IState �̳�
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window) override;

	// ͨ�� IState �̳�
	virtual HRESULT Render() override;
};

