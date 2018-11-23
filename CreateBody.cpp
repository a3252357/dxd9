#include "CreateBody.h"



CreateBody::CreateBody()
{
}


CreateBody::~CreateBody()
{
}

b2Body * CreateBody::CreateRectangleDef(float32 x, float32 y, float32 angle, float32 hx, float32 hy, b2BodyType type, float32 density, float32 friction, float32 restitution)
{
		b2BodyDef* bodyDef = new b2BodyDef();
		bodyDef->type = type;
		bodyDef->position.x = x/ PTM_RATIO;
		bodyDef->position.y = y / PTM_RATIO;
		bodyDef->angle = angle;
		b2Body *body = GameSystem::box2DSystem->world->CreateBody(bodyDef);
		body->CreateFixture(CreateFixtureDef::CreateRectangleDef(hx, hy, density, friction, restitution));
		return body;
}

b2Body * CreateBody::CreateCircleDef(float32 x, float32 y, float32 angle, float32 radius, b2BodyType type, float32 density, float32 friction, float32 restitution)
{
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = type;
	bodyDef->position.x = x / PTM_RATIO;
	bodyDef->position.y = y / PTM_RATIO;
	bodyDef->angle = angle;
	b2Body *body = GameSystem::box2DSystem->world->CreateBody(bodyDef);
	body->CreateFixture(CreateFixtureDef::CreateCircleDef(radius, density, friction, restitution));
	return body;
}

b2Body * CreateBody::CreatePolygonDef(float32 x, float32 y, float32 angle, vector<b2Vec2>* vec, b2BodyType type, float32 density, float32 friction, float32 restitution)
{
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = type;
	bodyDef->position.x = x / PTM_RATIO;
	bodyDef->position.y = y / PTM_RATIO;
	bodyDef->angle = angle;
	b2Body *body = GameSystem::box2DSystem->world->CreateBody(bodyDef);
	body->CreateFixture(CreateFixtureDef::CreatePolygonDef(vec, density, friction, restitution));
	return body;
}
