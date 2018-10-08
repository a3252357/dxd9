#ifndef SYSTEMINIT_H
#define SYSTEMINIT_H
#include "Seting.h"
static class SystemInit
{
	public:
		static HWND hwnd;
		static IDirect3DDevice9 * d3d9dev;
		static HRESULT init_D3D();
		static HRESULT init_Sys(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, WNDPROC WndProc);
	private:
		static VOID Light_Set(UINT nType);
		static VOID Matrix_Set();
};
#endif