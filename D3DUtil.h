#pragma once  
#include "Seting.h"
#include "Texture2d.h"
#include "SystemInit.h"
#include "TextureManager.h"
static class D3DUtil{
public:
	static IDirect3DDevice9 * getD3DDev();
	static HWND  getHWND();
	static ID3DXSprite* getID3DXSprite();
	static Texture2d * getTexture(LPCWSTR path);
	static Texture2d * getTexture(LPCWSTR path, int x, int y, int w, int h);
};