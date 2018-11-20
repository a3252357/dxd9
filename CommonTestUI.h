#pragma once
#include "Seting.h"
#include "UISystem.h"
#include "BaseGame.h"
#include "BaseUI.h"
using namespace CEGUI;
class CommonTestUI : public BaseUI
{
public:
	CommonTestUI(BaseGame * _game);
	~CommonTestUI();
	Window* myRoot;
	Scrollbar* fWnd;
	HRESULT Update() ;
	HRESULT Init();
	bool onMouseButtonDown(const EventArgs & e);
	HRESULT Relese();
	bool get(const EventArgs& args);

	// Í¨¹ý BaseUI ¼Ì³Ð
	virtual HRESULT Render() override;
};

