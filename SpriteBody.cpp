#include "SpriteBody.h"
#include "AnimationFrame.h"
HRESULT SpriteBody::Init(AnimationFrame * _sprite, b2Body* _body)
{
	body = _body;
	sprite = _sprite;
	body->SetUserData(sprite);
	//x_ptr = x;
	//y_ptr = y;
	//angle_ptr = angle;
	//bodyDef = new b2BodyDef();
	//bodyDef->type = b2BodyType::b2_dynamicBody;
	//c->position.x = *x_ptr;
	//bodyDef->position.y = *y_ptr;
	//bodyDef->angle = *angle_ptr;
	//body = GameSystem::box2DSystem->world->CreateBody(bodyDef);
	return S_OK;
}

HRESULT SpriteBody::Update()
{
	sprite->m_x = body->GetPosition().x*PTM_RATIO;
	sprite->m_y = body->GetPosition().y*PTM_RATIO;
	sprite->m_angels = body->GetAngle();
	//*x_ptr = body->GetPosition().x;
	//*y_ptr = body->GetPosition().y;
	//*angle_ptr = body->GetAngle();
	return S_OK;
}
