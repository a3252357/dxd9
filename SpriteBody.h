#pragma once
#include "Seting.h"
#include "GameSystem.h"
class SpriteBody {
	public:
		HRESULT Init(float* x, float *y, float* angle);
		HRESULT Update(float* delta);
		float* x_ptr;
		float* y_ptr;
		float* angle_ptr;
		b2BodyDef* bodyDef;
		b2Body* body;
};