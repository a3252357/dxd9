#pragma once
#include "Seting.h"
#include "IState.h"
#include "CommonTestUI.h"
#include "BaseGame.h"
#include "Vibration.h"
class FristCommonTset :
	public IState
{
public:
	FristCommonTset(BaseGame * _game);
	~FristCommonTset();
	BaseGame *game;
	// 通过 IState 继承
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;

	// 通过 IState 继承
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window) override;

	// 通过 IState 继承
	virtual HRESULT Render() override;
};

