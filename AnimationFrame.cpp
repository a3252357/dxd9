#include "AnimationFrame.h"
#include "Sprite.h"
HRESULT AnimationFrame::Add_AnimationSprite(LPCWSTR  path, float duration)
{
	shared_ptr <AFrame> frame = make_shared<AFrame>();
	frame->texture2d = make_shared<Texture2d>(*D3DUtil::getTexture(path));
	frame->duration = duration;
	frames.add(frame);
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	if (curtexture2d == nullptr)curtexture2d = frame->texture2d;
	return S_OK;
}
HRESULT AnimationFrame::Add_AnimationSprite(shared_ptr<Texture2d> Texture,float duration)
{
	shared_ptr <AFrame> frame = make_shared<AFrame>();
	frame->texture2d =Texture;
	frame->duration = duration;
	frames.add(frame);
	if (curtexture2d == nullptr)curtexture2d = frame->texture2d;
	return S_OK;
}

HRESULT AnimationFrame::Add_AnimationSprite(LPCWSTR  path,int tx, int ty, float duration=1000,int w, int h)
{
	shared_ptr <AFrame> frame= make_shared<AFrame>();
	frame->texture2d = make_shared<Texture2d>(*D3DUtil::getTexture(path, tx, ty, w, h));
	frame->duration = duration;
	frames.add(frame);
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	if(curtexture2d==nullptr)curtexture2d = frame->texture2d;
	return S_OK;
}

AnimationFrame::AnimationFrame(Sprite* _sprite)
{

	m_sprite = _sprite;
}

HRESULT AnimationFrame::Set_State(float x, float y, int angels)
{
	//n_x = m_x;
	//n_y = m_y;
	//m_x = x;
	//m_y = y;
	//m_angels = angels;
	return S_OK;
}

HRESULT AnimationFrame::Start(int type)
{
	if (frames.size() > 1) {
		start(frames.getNow()->data->duration,0,100);
	}
	return E_NOTIMPL;
}

HRESULT AnimationFrame::Stop()
{
	if (frames.size() > 1) {
		//start(frames.getNow()->data->duration,0,1);
	}
	return S_OK;
}

void AnimationFrame::callback()
{
	if (frames.goNext() == NULL)
	{
		frames.setHeadToNow();
	}
	curtexture2d = frames.getNow()->data->texture2d;
	start(frames.getNow()->data->duration);
}


HRESULT AnimationFrame::Update()
{
	//m_angels+=0.5;
	//body->Update(0);
	rect.left = curtexture2d->x;
	rect.right = curtexture2d->x + curtexture2d->w;
	rect.top = curtexture2d->y;
	rect.bottom = curtexture2d->y + curtexture2d->h;
	vec.x = m_sprite->m_x;
	vec.y = m_sprite->m_y;
	vec.z = 0;

	D3DXMatrixTranslation(&T1, -m_sprite->m_x - curtexture2d->w / 2, -m_sprite->m_y - curtexture2d->h / 2, 0.f);
	D3DXMatrixRotationZ(&dd16, m_sprite->m_angels);
	D3DXMatrixTranslation(&T2, m_sprite->m_x + curtexture2d->w / 2, m_sprite->m_y + curtexture2d->h / 2, 0.f);
	D3DXMatrixScaling(&TInv, m_sprite->sx, m_sprite->sy, 1.0f);
	//D3DXMatrixTranslation(&TInv, vec.x, vec.y, vec.z);
	TInv *= T1 * dd16*T2;
	return S_OK;
}

HRESULT AnimationFrame::Render()
{
	D3DUtil::getID3DXSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	D3DUtil::getID3DXSprite()->SetTransform(&TInv);
	D3DUtil::getID3DXSprite()->Draw(*curtexture2d->ptexture9, &rect, NULL, &vec, 0xffffffff);
	D3DUtil::getID3DXSprite()->End();
	return S_OK;
}
