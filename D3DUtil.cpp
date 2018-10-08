#include "D3DUtil.h"
IDirect3DDevice9 * D3DUtil::getD3DDev()
{
	return SystemInit::d3d9dev;
}

HWND D3DUtil::getHWND()
{
	return SystemInit::hwnd;
}

LPDIRECT3DTEXTURE9 * D3DUtil::getTexture(LPCWSTR path)
{
	return TextureManager::getTexture(path);
}
