#pragma once
#include "BaseGame.h"
#include "IState.h"
#include "FristCommonTset.h"
class TestManger :
	public BaseGame
{
public:
	TestManger();
	~TestManger();
	//CEGUI::Direct3D9Renderer* myRenderer;
	// Í¨¹ý BaseGame ¼Ì³Ð
	virtual HRESULT Init() override;
	virtual HRESULT Update() override;
	virtual HRESULT Render() override;
};

