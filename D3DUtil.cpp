#include "D3DUtil.h"
IDirect3DDevice9 * D3DUtil::getD3DDev()
{
	return SystemInit::d3d9dev;
}

HWND D3DUtil::getHWND()
{
	return SystemInit::hwnd;
}

Texture2d * D3DUtil::getTexture(LPCWSTR path)
{
	return TextureManager::getTexture(path);
}

Texture2d *  D3DUtil::getTexture(LPCWSTR path,int x,int y,int w,int h)
{
	return TextureManager::getTexture(path, x, y, w, h);
}

