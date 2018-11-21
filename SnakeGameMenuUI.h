#pragma once
#include "Seting.h"
#include "UISystem.h"
#include "BaseGame.h"
#include "BaseUI.h"
using namespace CEGUI;
class SnakeGameMenuUI : public BaseUI
{
public:
	SnakeGameMenuUI(BaseGame * _game);
	~SnakeGameMenuUI();
	Window* myRoot;
	Scrollbar* fWnd;
	HRESULT Update();
	HRESULT Init();
	bool onMouseButtonDown(const EventArgs & e);
	HRESULT Relese();
	bool get(const EventArgs& args);

	// Í¨¹ý BaseUI ¼Ì³Ð
	virtual HRESULT Render() override;
};



