#include "Texture2d.h"
#include "D3DUtil.h"



Texture2d::Texture2d(LPDIRECT3DTEXTURE9 _texture,int _x,int _y,int _w,int _h):ptexture9(_texture),x(_x),y(_y),w(_w),h(_h)
{
}


Texture2d::~Texture2d()
{

}

HRESULT Texture2d::Render(D3DXMATRIX& TInv, RECT& rect, D3DXVECTOR3& vec)
{
	D3DUtil::getID3DXSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	D3DUtil::getID3DXSprite()->SetTransform(&TInv);
	D3DUtil::getID3DXSprite()->Draw(ptexture9, &rect, NULL, &vec, 0xffffffff);
	D3DUtil::getID3DXSprite()->End();
	return E_NOTIMPL;
}
