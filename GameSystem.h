#pragma once
#include "Seting.h"
class Box2DSystem;
static class GameSystem
{
public:
	static Box2DSystem* box2DSystem;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
};

