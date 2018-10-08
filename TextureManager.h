#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Seting.h"
typedef  map<LPCWSTR, LPDIRECT3DTEXTURE9> TEXTURE_MAP;
class TextureManager {
	public:
		static LPDIRECT3DTEXTURE9 * getTexture(LPCWSTR path);
		static TEXTURE_MAP TextureMap;
		static LPDIRECT3DTEXTURE9 ptexture9;

};
#endif
