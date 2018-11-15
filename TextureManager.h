#pragma once  
#include "Seting.h"
#include "D3DUtil.h"
#include "Texture2d.h"
typedef  map<LPCWSTR, LPDIRECT3DTEXTURE9> TEXTURE_MAP;
class TextureManager {
	public:
		static Texture2d * getTexture(LPCWSTR path,int x,int y,int w,int h);
		static Texture2d * getTexture(LPCWSTR path);
		static TEXTURE_MAP TextureMap;
		static LPDIRECT3DTEXTURE9 ptexture9;

};
