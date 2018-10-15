#pragma once
#include "Seting.h"
static class Box2DSystem {
public:
	HRESULT Box2DInit(float xf,float yf);
	HRESULT Update(float delta);
private:
	b2Vec2 gravity;
	b2World world;
	bool doSleep;
};
