#pragma once
#include "IState.h"
#include "BaseGame.h"
#include "MapLoader.h"
class GamingState :
	public IState
{
public:
	GamingState(BaseGame * _game);
	~GamingState();
	BaseGame *game;
	MapLoader * maps;
	// Í¨¹ý IState ¼Ì³Ð
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;
	virtual HRESULT Render() override;
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const CEGUI::EventArgs & e, CEGUI::Window * window) override;
};

