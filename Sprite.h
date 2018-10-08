#pragma once
#include "BaseSprite.h"
#include "Seting.h"
class Sprite:public BaseSprite
{
	public:
		ID3DXSprite* m_Sprite;
		LPDIRECT3DTEXTURE9 * m_Texture;
		HRESULT Sprite_Init(LPCWSTR  path, float x, float y, float angels);
		HRESULT Sprite_Init(LPDIRECT3DTEXTURE9 * Texture, float x, float y, float angels);
		HRESULT Set_State(float x, float y, int angels);
		HRESULT Update();
		HRESULT Render();
		RECT rect;
		D3DXVECTOR3 vec;
		D3DXMATRIX dd16;
		D3DXMATRIX T1, T2, TInv;
		float m_x, m_y, m_angels,n_x,n_y;

};
