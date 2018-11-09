#include "Sprite.h"
HRESULT Sprite::Sprite_Init(LPCWSTR  path,float x, float y, float angels)
{
	m_animationFrame = make_shared<AnimationFrame>(this);
	m_animationFrame->Add_AnimationSprite(path,100);
	//m_Texture= make_shared<Texture2d>(*D3DUtil::getTexture(path));
	//n_x = m_x;
	//n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	return S_OK;
}
HRESULT Sprite::Sprite_Init(shared_ptr<Texture2d> Texture, float x, float y, float angels)
{
	m_animationFrame = make_shared<AnimationFrame>(this);
	m_animationFrame->Add_AnimationSprite(Texture, 100);
	//n_x = m_x;
	///n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	return S_OK;
}

HRESULT Sprite::Sprite_Init(LPCWSTR  path, float x, float y, float angels,int tx,int ty,int w=BOX_WIDTH,int h = BOX_WIDTH)
{
	m_animationFrame = make_shared<AnimationFrame>(this);
	m_animationFrame->Add_AnimationSprite(path,tx,ty,100,w,h);
	//n_x = m_x;
	//n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	return S_OK;
}

HRESULT Sprite::Sprite_Add(LPCWSTR path)
{
	m_animationFrame->Add_AnimationSprite(path, 100);
	return S_OK;
}

HRESULT Sprite::Sprite_Add(shared_ptr<Texture2d> Texture)
{
	m_animationFrame->Add_AnimationSprite(Texture, 100);
	return S_OK;
}

HRESULT Sprite::Sprite_Add(LPCWSTR path, int tx, int ty, int w, int h)
{
	m_animationFrame->Add_AnimationSprite(path, tx, ty, 100, w, h);
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
	m_animationFrame->Update();
	return S_OK;
}

HRESULT Sprite::Render()
{
	m_animationFrame->Render();
	return S_OK;
}
