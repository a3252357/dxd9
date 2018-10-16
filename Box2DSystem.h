#pragma once
#include "Seting.h"
class Box2DSystem {
public:
	HRESULT Box2DInit(float xf,float yf);
	HRESULT Update(float delta);
	b2World* world;
private:
	b2Vec2 gravity;
	bool doSleep;
};
