#pragma once
#include "Seting.h"
#include "b2Separator.h"
static class CreateFixtureDef
{
public:
	static b2FixtureDef * CreateRectangleDef(float32 hx, float32 hy, float32 density=10.0f, float32 friction=0.4f, float32 restitution=0.4f);
	static b2FixtureDef * CreateCircleDef(float32 radius, float32 density = 10.0f, float32 friction = 0.4f, float32 restitution = 0.4f);
	static b2FixtureDef * CreatePolygonDef(vector<b2Vec2>* vec, float32 density = 10.0f, float32 friction = 0.4f, float32 restitution = 0.4f);
};

