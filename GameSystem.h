#pragma once
#include "Seting.h"
#include "MapLoader.h"
class Box2DSystem;
class MapLoader;
static class GameSystem
{
public:
	static Box2DSystem* box2DSystem;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
};
 
