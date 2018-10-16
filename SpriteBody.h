#pragma once
#include <d3d9.h>
#include "Box2D/Box2D.h"
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