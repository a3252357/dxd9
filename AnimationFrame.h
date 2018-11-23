#pragma once
#include "Seting.h"
#include "D3DUtil.h"
#include "ListUser.h"
#include "Texture2d.h"
#include "Timerutil.h"
class Sprite;
class SpriteBody;
class AnimationFrame : public BaseSprite,public Timerutil<AnimationFrame> {
public:
	AnimationFrame();
	struct AFrame final
	{
		Texture2d* texture2d;
		float duration=100;
	};
	Texture2d* curtexture2d=nullptr;
	ListUser<shared_ptr<AFrame>> frames;
	HRESULT Add_AnimationSprite(LPCWSTR path, float x, float y, float angels, float _sx=1, float _sy=1, float duration=1000);
	HRESULT Add_AnimationSprite(Texture2d* Texture, float x, float y, float angels, float _sx=1, float _sy=1, float duration=1000);
	HRESULT Add_AnimationSprite(LPCWSTR path, float x, float y, float angels, int tx, int ty, int w=BOX_WIDTH, int h = BOX_WIDTH, float _sx=1, float _sy=1, float duration=1000);
	HRESULT Set_State(float x, float y, int angels);
	HRESULT Start();
	HRESULT Stop();
	bool SetAnimationFrame();
	HRESULT Update() override;
	HRESULT Render() override;
	RECT rect;
	D3DXVECTOR3 vec;
	D3DXMATRIX dd16;
	D3DXMATRIX T1, T2, TInv;
	SpriteBody* body;
	float m_x, m_y, m_angels, n_x, n_y, sx = 1, sy = 1;
};