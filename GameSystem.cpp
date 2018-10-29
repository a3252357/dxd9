#include "GameSystem.h"

Box2DSystem * GameSystem::box2DSystem;

HRESULT GameSystem::Init()
{
	TimeInit::Time_Init();
	//box2DSystem = new Box2DSystem();
	//box2DSystem->Box2DInit(0, 0);
	return S_OK;
}

HRESULT GameSystem::Relese()
{
	//delete box2DSystem;
	return S_OK;
}


HRESULT GameSystem::Update(float delta)
{
	//box2DSystem->Update(delta);
	return S_OK;
}
