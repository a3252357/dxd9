#pragma once
#include "Seting.h" 
class BaseGame;
class BaseUI {
	//IState();
public:
	BaseGame *game;
	virtual ~BaseUI() {};
	virtual HRESULT Init() = 0;
	virtual HRESULT Update() = 0;
	virtual HRESULT Render() = 0;
};
