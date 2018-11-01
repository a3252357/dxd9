#pragma once
#include <d3d9.h>
class Texture2d
{
public:
	Texture2d(LPDIRECT3DTEXTURE9 *_texture, int _x, int _y, int _w, int _h);
	~Texture2d();
	LPDIRECT3DTEXTURE9 *ptexture9;
	HRESULT Render();
	int x;
	int y;
	int w;
	int h;
};

