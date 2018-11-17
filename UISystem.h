#pragma once
#include "Seting.h"
#include "MapLoader.h"
#include "D3Dutil.h"
using namespace CEGUI;
static class UISystem
{
public:
	static CEGUI::Direct3D9Renderer* myRenderer;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
	static bool get(const EventArgs& args);
	/////// 获得输入框的坐标 (Added by Azure)
	static bool getFocusedInputBoxCoord(POINT& point, float& height);

	////// 输入法跟随 (Added by Azure)
	static bool IMEFollow(HWND hWnd);
};
 
