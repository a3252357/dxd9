#pragma once  
#include "Seting.h"
#include "IState.h"
#include "BaseUI.h"
class BaseGame
{
public:
	IState * state;
	BaseUI * ui;
	virtual HRESULT Update() {
		if(ui!=NULL)
			ui->Update();
		if (state != NULL) {
			state->Update();
		}
		return S_OK;
	};
	virtual HRESULT Init() = 0;
	virtual HRESULT Render() {
		if (ui != NULL)
			ui->Render();
		if (state != NULL) {
			state->Render();
		}
		return S_OK;
	};
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type, const CEGUI::EventArgs& e, CEGUI::Window * window) {
		state->InputHandle(name, type, e, window);
		return S_OK;
	};
};