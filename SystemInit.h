#pragma once  
#include "Seting.h"
#include "UISystem.h"
#include "D3DRect.h"
#include "GameSystem.h"
#include "InputInit.h"
static class SystemInit
{
	public:
		static HWND hwnd;
		static IDirect3DDevice9 * d3d9dev;
		static ID3DXSprite* m_Sprite;
		static HRESULT init_D3D();
		static HRESULT init_Sys(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, WNDPROC WndProc);
	private:
		static VOID Light_Set(UINT nType);
		static VOID Matrix_Set();
};