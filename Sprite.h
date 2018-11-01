#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class SpriteBody;
class Sprite:public BaseSprite
{
	public:
		ID3DXSprite* m_Sprite;
		shared_ptr<Texture2d> m_Texture;
		HRESULT Sprite_Init(LPCWSTR  path, float x, float y, float angels);
		HRESULT Sprite_Init(Texture2d * Texture, float x, float y, float angels);
		HRESULT Sprite_Init(LPCWSTR path, float x, float y, float angels, int tx, int ty, int w, int h);
		HRESULT Set_State(float x, float y, int angels);
		HRESULT Update();
		HRESULT Render();
		RECT rect;
		D3DXVECTOR3 vec;
		D3DXMATRIX dd16;
		D3DXMATRIX T1, T2, TInv;
		SpriteBody* body;
		float m_x, m_y, m_angels,n_x,n_y;

};
