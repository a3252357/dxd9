#pragma once
#include "Seting.h"
class SpriteBody {
	public:
		HRESULT Init(int x,int y);
	private:
		b2BodyDef bodyDef;
		b2Body body;
};