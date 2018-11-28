#include "AnimationFrame.h"
#include "CallBackTimer.h"
#include "SpriteBody.h"
#include "CreateBody.h"
HRESULT AnimationFrame::Add_AnimationSprite(LPCWSTR  path, float x, float y, float angels, float _sx, float _sy, float duration)
{
	shared_ptr <AFrame> frame = make_shared<AFrame>();
	frame->texture2d =D3DUtil::getTexture(path);
	frame->duration = duration;
	frames.add(frame);
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	sx = _sx;
	sy = _sy;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	if (curtexture2d == nullptr&&body->body == NULL) {
		curtexture2d = frame->texture2d;
		//body->Init(this,CreateBody::CreateRectangleDef(m_x,m_y, m_angels, sx*curtexture2d->w / 2, sy*curtexture2d->h / 2));
	}
	return S_OK;
}
HRESULT AnimationFrame::Add_AnimationSprite(Texture2d* Texture, float x, float y, float angels, float _sx, float _sy, float duration)
{
	shared_ptr <AFrame> frame = make_shared<AFrame>();
	frame->texture2d = Texture;
	frame->duration = duration;
	frames.add(frame);
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	sx = _sx;
	sy = _sy;
	m_angels = angels;
	if (curtexture2d == nullptr&&body->body == NULL) {
		curtexture2d = frame->texture2d;
		//body->Init(this, CreateBody::CreateRectangleDef(m_x,m_y, m_angels, sx*curtexture2d->w / 2, sy*curtexture2d->h / 2));
	}
	return S_OK;
}

HRESULT AnimationFrame::Add_AnimationSprite(LPCWSTR  path, float x, float y, float angels, int tx, int ty, int w, int h, float _sx, float _sy, float duration)
{
	shared_ptr <AFrame> frame= make_shared<AFrame>();
	frame->texture2d = D3DUtil::getTexture(path, tx, ty, w, h);
	frame->duration = duration;
	frames.add(frame);
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	sx = _sx;
	sy = _sy;
	m_angels = angels;
	//body = new SpriteBody();
	//body->Init(&m_x, &m_y, &m_angels);
	if (curtexture2d == nullptr&&body->body==NULL)
	{
		curtexture2d = frame->texture2d;
		//body->Init(this, CreateBody::CreateRectangleDef(m_x,m_y, m_angels, sx*curtexture2d->w / 2, sy*curtexture2d->h / 2));
	}
	return S_OK;
}

AnimationFrame::AnimationFrame()
{
	curtexture2d = nullptr;
	body = new SpriteBody();
}

HRESULT AnimationFrame::Set_State(float x, float y, int angels)
{
	n_x = m_x;
	n_y = m_y;
	m_x = x;
	m_y = y;
	m_angels = angels;
	return S_OK;
}


HRESULT AnimationFrame::Start()
{
	if (frames.size() > 1) {
		InvokeRepeating(&AnimationFrame::SetAnimationFrame, "SetAnimationFrame", 1, 4000,4000);
		//CancelInvoke("SetAnimationFrame");
		//CallBackTimer* snaketimer = new CallBackTimer(type, &AnimationFrame::callback);
		//
		//snaketimer->start(type->frames.getNow()->data->duration,0, 100);
		//start(frames.getNow()->data->duration,type,100);
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

bool AnimationFrame::SetAnimationFrame()
{
	if (frames.goNext() == NULL)
	{
		frames.setHeadToNow();
	}
	curtexture2d = frames.getNow()->data->texture2d;
	//start(frames.getNow()->data->duration);
	return true;
}


HRESULT AnimationFrame::Update()
{
	/*
	body->Update();
	if (InputInit::g_KeyboardState[DIK_LEFT] & 0x8000f) {
		body->body->SetLinearVelocity(b2Vec2(-3, 0));
	}
	if (InputInit::g_KeyboardState[DIK_RIGHT] & 0x8000f) { body->body->ApplyForce(b2Vec2(1, 0), body->body->GetWorldCenter(),true); }
	if (InputInit::g_KeyboardState[DIK_UP] & 0x8000f) {
		body->body->SetLinearVelocity(b2Vec2(0, -3));
	}
	if (InputInit::g_KeyboardState[DIK_DOWN] & 0x8000f) { body->body->SetLinearVelocity(b2Vec2(0,3)); }
	*/
	//m_angels+=0.5;
	//body->Update(0);
	rect.left = curtexture2d->x;
	rect.right = curtexture2d->x + curtexture2d->w;
	rect.top = curtexture2d->y;
	rect.bottom = curtexture2d->y + curtexture2d->h;
	vec.x = m_x;
	vec.y = m_y;
	vec.z = 0;

	D3DXMatrixTranslation(&T1, -m_x - curtexture2d->w / 2, -m_y - curtexture2d->h / 2, 0.f);
	D3DXMatrixRotationZ(&dd16, m_angels);
	D3DXMatrixTranslation(&T2, m_x + curtexture2d->w / 2, m_y + curtexture2d->h / 2, 0.f);
	D3DXMatrixScaling(&TInv, sx, sy, 1.0f);
	//D3DXMatrixTranslation(&TInv, vec.x, vec.y, vec.z);
	TInv *= T1 * dd16*T2;
	return S_OK;
}

HRESULT AnimationFrame::Render()
{
	curtexture2d->Render(TInv, rect, vec);
	return S_OK;
}
