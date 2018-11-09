#pragma once  
#include "Seting.h"
#include "D3DUtil.h"
#include "Texture2d.h"
typedef  map<LPCWSTR, LPDIRECT3DTEXTURE9> TEXTURE_MAP;
class TextureManager {
	public:
		static shared_ptr<Texture2d> getTexture(LPCWSTR path,int x,int y,int w,int h);
		static TEXTURE_MAP TextureMap;
		static LPDIRECT3DTEXTURE9 ptexture9;

};
