#ifndef D3DUTIL_H
#define D3DUTIL_H
#include "Seting.h"
#include "Texture2d.h"
static class D3DUtil{
public:
	static IDirect3DDevice9 * getD3DDev();
	static HWND  getHWND();
	static Texture2d * getTexture(LPCWSTR path);
	static Texture2d * getTexture(LPCWSTR path, int x, int y, int w, int h);
};
#endif