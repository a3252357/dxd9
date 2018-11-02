#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Seting.h"
class Texture2d;
typedef  map<LPCWSTR, LPDIRECT3DTEXTURE9> TEXTURE_MAP;
class TextureManager {
	public:
		static shared_ptr<Texture2d> getTexture(LPCWSTR path,int x,int y,int w,int h);
		static TEXTURE_MAP TextureMap;
		static LPDIRECT3DTEXTURE9 ptexture9;

};
#endif
