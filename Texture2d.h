#pragma once
#include "Seting.h"
class Texture2d
{
public:
	Texture2d(LPDIRECT3DTEXTURE9 *_texture, int _x, int _y, int _w, int _h);
	~Texture2d();
	HRESULT Render(D3DXMATRIX & TInv, RECT & rect, D3DXVECTOR3 & vec);
	LPDIRECT3DTEXTURE9 *ptexture9;
	int x;
	int y;
	int w;
	int h;
};

