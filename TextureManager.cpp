#include "TextureManager.h"
TEXTURE_MAP TextureManager::TextureMap;
LPDIRECT3DTEXTURE9 TextureManager::ptexture9;

Texture2d * TextureManager::getTexture(LPCWSTR path, int x, int y, int w, int h)
{
	TEXTURE_MAP::reverse_iterator iter;

	for (iter = TextureMap.rbegin(); iter != TextureMap.rend(); iter++)
	{
		if (lstrcmpW(iter->first, path) == 0)
			return new Texture2d(&iter->second, x, y, w, h);
	}
	HRESULT hr = D3DXCreateTextureFromFile(D3DUtil::getD3DDev(), path, &ptexture9);
	if (hr == S_OK) {
		TextureMap.insert(TEXTURE_MAP::value_type(path, ptexture9));
		return new Texture2d(&ptexture9, x, y, w, h);
	}
	else {
		return NULL;
	}
}
	


