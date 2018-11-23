#pragma once
#include "Seting.h"
#include "GameSystem.h"
class AnimationFrame;
class SpriteBody {
	public:
		HRESULT Init(AnimationFrame * _sprite, b2Body* _body);
		HRESULT Update();
		b2Body* body=NULL;
		AnimationFrame * sprite = NULL;
};