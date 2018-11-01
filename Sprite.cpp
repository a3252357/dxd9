#include "Sprite.h"
HRESULT Sprite::Sprite_Init(LPCWSTR  path,float x, float y, float angels)
{
	D3DXCreateSprite(D3DUtil::getD3DDev(), &m_Sprite);
	m_Texture= make_shared<Texture2d>(*D3DUtil::getTexture(path));
	//n_x = m_x;
	//n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	return S_OK;
}
HRESULT Sprite::Sprite_Init(Texture2d * Texture, float x, float y, float angels)
{
	D3DXCreateSprite(D3DUtil::getD3DDev(), &m_Sprite);
	m_Texture = make_shared<Texture2d>(*Texture);
	//n_x = m_x;
	///n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	return S_OK;
}

HRESULT Sprite::Sprite_Init(LPCWSTR  path, float x, float y, float angels,int tx,int ty,int w=BOX_WIDTH,int h = BOX_WIDTH)
{
	D3DXCreateSprite(D3DUtil::getD3DDev(), &m_Sprite);
	m_Texture = make_shared<Texture2d>(*D3DUtil::getTexture(path,tx,ty,w,h));
	//n_x = m_x;
	//n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	return S_OK;
}

HRESULT Sprite::Set_State(float x, float y, int angels)
{
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	return S_OK;
}

HRESULT Sprite::Update()
{
	//m_angels+=0.5;
	//body->Update(0);
	rect.left = m_Texture->x;
	rect.right = m_Texture->x+ m_Texture->w;
	rect.top = m_Texture->y;
	rect.bottom = m_Texture->y+m_Texture->h;
	vec.x = m_x;
	vec.y = m_y;
	vec.z = 0;

	D3DXMatrixRotationZ(&dd16, m_angels);
	D3DXMatrixTranslation(&T1, -m_x - m_Texture->w / 2, -m_y - m_Texture->h / 2, 0.f);
	D3DXMatrixTranslation(&T2, m_x + m_Texture->w / 2, m_y + m_Texture->h / 2, 0.f);
	//D3DXMatrixTranslation(&TInv, vec.x, vec.y, vec.z);
	TInv = T1*dd16*T2;
	return S_OK;
}

HRESULT Sprite::Render()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Sprite->SetTransform(&TInv);
	HRESULT s1 = m_Sprite->Draw(*m_Texture->ptexture9, &rect, NULL, &vec, 0xffffffff);
	HRESULT s= m_Sprite->End();
	return S_OK;
}
