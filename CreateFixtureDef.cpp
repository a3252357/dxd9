#include "CreateFixtureDef.h"




b2FixtureDef* CreateFixtureDef::CreateRectangleDef(float32 hx,float32 hy,float32 density, float32 friction, float32 restitution)
{
	b2PolygonShape* paddleShape = new b2PolygonShape();
	paddleShape->SetAsBox(hx/ PTM_RATIO, hy/ PTM_RATIO);
	b2FixtureDef * fixtureDef = new b2FixtureDef();
	fixtureDef->density= density;//密度
	fixtureDef->shape = paddleShape;//形状
	fixtureDef->friction = friction;//摩擦力
	fixtureDef->restitution = restitution;//回复力

	return fixtureDef;
}


b2FixtureDef* CreateFixtureDef::CreateCircleDef(float32 radius, float32 density, float32 friction, float32 restitution)
{
	b2CircleShape* paddleShape = new b2CircleShape();
	paddleShape->m_radius = radius/ PTM_RATIO;
	b2FixtureDef * fixtureDef = new b2FixtureDef();
	fixtureDef->density = density;//密度
	fixtureDef->shape = paddleShape;//形状
	fixtureDef->friction = friction;//摩擦力
	fixtureDef->restitution = restitution;//回复力
	return fixtureDef;
}


b2FixtureDef* CreateFixtureDef::CreatePolygonDef(vector<b2Vec2>* vec,float32 density, float32 friction, float32 restitution)
{
	b2FixtureDef *fixtureDef = new b2FixtureDef();
	b2Separator* sep = new b2Separator();
	fixtureDef->restitution = restitution;
	fixtureDef->friction = friction;
	fixtureDef->density = density;

	if (sep->Validate(*vec) == 0)
	{
		DEBUG__LOG("Yay! Those vertices are good to go!");
	}
	else
	{
		DEBUG__LOG("Oh, I guess you effed something up :(");
	}

	sep->Separate(fixtureDef, vec, PTM_RATIO);
	return fixtureDef;
}


