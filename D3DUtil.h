#ifndef D3DUTIL_H
#define D3DUTIL_H
#include "Seting.h"
static class D3DUtil{
public:
	static IDirect3DDevice9 * getD3DDev();
	static HWND  getHWND();
	static LPDIRECT3DTEXTURE9 * getTexture(LPCWSTR path);
};
#endif