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
	// ͨ�� IState �̳�
	virtual HRESULT Update() override;
	virtual HRESULT ChangeState() override;

	// ͨ�� IState �̳�
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window) override;

	// ͨ�� IState �̳�
	virtual HRESULT Render() override;
};

