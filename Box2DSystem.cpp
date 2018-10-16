#include "Box2DSystem.h"

HRESULT Box2DSystem::Box2DInit(float xf, float yf)
{
	gravity = b2Vec2(xf, yf);
	doSleep = true;
	world=new b2World(gravity);
	return S_OK;
}

HRESULT Box2DSystem::Update(float delta)
{
	world->Step(delta/1000, 10, 10);
	return S_OK;
}
