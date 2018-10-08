#include "TextureManager.h"
TEXTURE_MAP TextureManager::TextureMap;
LPDIRECT3DTEXTURE9 TextureManager::ptexture9;
LPDIRECT3DTEXTURE9 * TextureManager::getTexture(LPCWSTR path)
{
	TEXTURE_MAP::reverse_iterator iter;

	for (iter = TextureMap.rbegin(); iter != TextureMap.rend(); iter++)
	{
		if (lstrcmpW(iter->first,path)==0)
			return &iter->second;
	}
	HRESULT hr = D3DXCreateTextureFromFile(D3DUtil::getD3DDev(), path, &ptexture9);
	TextureMap.insert(TEXTURE_MAP::value_type(path, ptexture9));
	return &ptexture9;
}
	


