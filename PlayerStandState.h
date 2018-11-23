#pragma once
#include "Seting.h"
#include "IPlayerState.h"
#include "InputInit.h"
class PlayerStandState:public IPlayerState
{
public:
	Player * player;
	PlayerStandState(Player * _player);
	~PlayerStandState();

	// ͨ�� IPlayerState �̳�
	virtual HRESULT Update() override;
	virtual HRESULT Render() override;
	virtual HRESULT InputHandle() override;
};

