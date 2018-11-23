#pragma once
#include "Seting.h"
#include "Player.h"
class IPlayerState
{
public:
	//IPlayerState();
	virtual ~IPlayerState() {};
	virtual HRESULT Update() = 0;
	virtual HRESULT Render() = 0;
	virtual HRESULT InputHandle() = 0;
};

