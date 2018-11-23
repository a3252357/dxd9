#include "Box2DSystem.h"
#include "CreateBody.h"

HRESULT Box2DSystem::Box2DInit(float xf, float yf)
{
	gravity = b2Vec2(xf, 3);
	doSleep = true;
	world=new b2World(gravity);
	CreateBody::CreateRectangleDef(0, SCREEN_HEIGHT/2, 0, SCREEN_WIDTH, 10, b2_staticBody);
	return S_OK;
}

HRESULT Box2DSystem::Update(float delta)
{
	if (delta > 0) {
		world->Step(delta / 1000, 10, 10);
	}
	return S_OK;
}
