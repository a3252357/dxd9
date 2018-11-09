#pragma once
#include "Seting.h"
#include "TimeInit.h"
#include "Box2DSystem.h"
static class GameSystem
{
public:
	static Box2DSystem* box2DSystem;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
};
 
