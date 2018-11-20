#pragma once
#include "Seting.h"
class IState
{
public:
	//IState();
	virtual ~IState() {};
	virtual HRESULT Update() =0;
	virtual HRESULT ChangeState()=0;
	virtual HRESULT Render() = 0;
	virtual HRESULT InputHandle(LPCWSTR name, LPCWSTR type,const CEGUI::EventArgs & e, CEGUI::Window * window) = 0;
};
