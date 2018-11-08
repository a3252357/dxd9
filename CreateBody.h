#pragma once
#include "Seting.h"
#include "CreateFixtureDef.h"
static class CreateBody
{
public:
	CreateBody();
	~CreateBody();
	static b2Body * CreateRectangleDef(float32 x, float32 y, float32 angle,float32 hx, float32 hy, b2BodyType type = b2BodyType::b2_dynamicBody, float32 density = 10.0f, float32 friction = 0.4f, float32 restitution = 0.4f);
	static b2Body * CreateCircleDef(float32 x, float32 y, float32 angle,float32 radius, b2BodyType type = b2BodyType::b2_dynamicBody, float32 density = 10.0f, float32 friction = 0.4f, float32 restitution = 0.4f);
	static b2Body * CreatePolygonDef(float32 x, float32 y, float32 angle,vector<b2Vec2>* vec, b2BodyType type = b2BodyType::b2_dynamicBody, float32 density = 10.0f, float32 friction = 0.4f, float32 restitution = 0.4f);
};

