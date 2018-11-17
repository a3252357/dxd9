#pragma once
#include "BaseUI.h"
#include "Seting.h"
#include "UISystem.h"
#include "BaseGame.h"
#include "BaseUI.h"
class VibrationUI :
	public BaseUI
{
public:
	VibrationUI(BaseGame *_game);
	~VibrationUI();
	BaseGame *game;
	Window* myRoot;
	Scrollbar* fWnd;
	HRESULT Update();
	HRESULT Init();
	bool onMouseButtonDown(const EventArgs & e);
	HRESULT Relese();
	bool get(const EventArgs& args);
};

