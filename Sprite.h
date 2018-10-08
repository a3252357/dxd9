#ifndef SPRITE_H
#define SPRITE_H
#include "Seting.h"
#include "Base.h"
class Sprite:public Base	
{
	public:
		ID3DXSprite* m_Sprite;
		LPDIRECT3DTEXTURE9 * m_Texture;
		HRESULT Sprite_Init(LPCWSTR  path, int x, int y, int angels);
		HRESULT Sprite_Init(LPDIRECT3DTEXTURE9 * Texture, int x, int y, int angels);
		HRESULT Set_State(float x, float y, int angels);
		RECT rect;
		D3DXVECTOR3 vec;
		D3DXMATRIX dd16;
		D3DXMATRIX T1, T2, TInv;
		float m_x, m_y, m_angels,n_x,n_y;
	private:
		void OUpdate() override;
		void ORender() override;

};
#endif
