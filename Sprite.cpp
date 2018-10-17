#include "Sprite.h"
HRESULT Sprite::Sprite_Init(LPCWSTR  path,float x, float y, float angels)
{
	D3DXCreateSprite(D3DUtil::getD3DDev(), &m_Sprite);
	m_Texture= D3DUtil::getTexture(path);
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	body = new SpriteBody();
	body->Init(&m_x, &m_y, &m_angels);
	return S_OK;
}
HRESULT Sprite::Sprite_Init(LPDIRECT3DTEXTURE9 * Texture, float x, float y, float angels)
{
	D3DXCreateSprite(D3DUtil::getD3DDev(), &m_Sprite);
	m_Texture = Texture;
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	return S_OK;
}

HRESULT Sprite::Set_State(float x, float y, int angels)
{
	n_x = x;
	n_y = y;
	//m_x = x;
	//m_y = y;
	m_angels = angels;
	return S_OK;
}

HRESULT Sprite::Update()
{
	body->Update(0);
	rect.left = 0;
	rect.right = BOX_WIDTH;
	rect.top = 0;
	rect.bottom = BOX_WIDTH;
	vec.x = m_x;
	vec.y = m_y;
	vec.z = 0;

	D3DXMatrixRotationZ(&dd16, m_angels);
	D3DXMatrixTranslation(&T1, -m_x - BOX_WIDTH / 2, -m_y - BOX_WIDTH / 2, 0.f);
	D3DXMatrixTranslation(&T2, m_x + BOX_WIDTH / 2, m_y + BOX_WIDTH / 2, 0.f);
	D3DXMatrixTranslation(&TInv, m_x, m_y, 0.f);
	TInv = T1*dd16*T2*TInv;
	return S_OK;
}

HRESULT Sprite::Render()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Sprite->SetTransform(&TInv);
	HRESULT s1 = m_Sprite->Draw(*m_Texture, &rect, NULL, &vec, 0xffffffff);
	HRESULT s= m_Sprite->End();
	return S_OK;
}
