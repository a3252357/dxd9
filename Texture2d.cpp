#include "Texture2d.h"



Texture2d::Texture2d(LPDIRECT3DTEXTURE9 *_texture,int _x,int _y,int _w,int _h):ptexture9(_texture),x(_x),y(_y),w(_w),h(_h)
{
}


Texture2d::~Texture2d()
{

}

HRESULT Texture2d::Render()
{
	return E_NOTIMPL;
}
