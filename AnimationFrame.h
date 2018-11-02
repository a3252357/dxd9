#pragma once
#include "Seting.h"
#include "TimerWithSprite.h"
class Sprite;
class AnimationFrame {
public:
	AnimationFrame(Sprite* _sprite);
	struct AFrame final
	{
		shared_ptr<Texture2d> texture2d;
		float duration=100;
	};
	Sprite* m_sprite;
	shared_ptr<Texture2d> curtexture2d;
	ListUser<shared_ptr<AFrame>> frames;
	ID3DXSprite* m_Sprite;
	HRESULT Add_AnimationSprite(LPCWSTR  path, float duration);
	HRESULT Add_AnimationSprite(shared_ptr<Texture2d> Texture,float duration);
	HRESULT Add_AnimationSprite(LPCWSTR path,int tx, int ty, float duration, int w, int);
	HRESULT Set_State(float x, float y, int angels);
	HRESULT Start(int type);
	HRESULT Stop();
	void AnimationPlay();
	HRESULT Update();
	HRESULT Render();
	RECT rect;
	D3DXVECTOR3 vec;
	D3DXMATRIX dd16;
	D3DXMATRIX T1, T2, TInv;
	TimerWithSprite<AnimationFrame>* timer;
};