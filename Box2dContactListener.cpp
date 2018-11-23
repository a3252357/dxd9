#include "Box2dContactListener.h"


void Box2dContactListener::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	BaseSprite* spriteA = (BaseSprite*)bodyA->GetUserData();
	spriteA->OnTriggerStar(contact);
	BaseSprite* spriteB = (BaseSprite*)bodyB->GetUserData();
	spriteB->OnTriggerStar(contact);
}

void Box2dContactListener::EndContact(b2Contact * contact)
{
}

void Box2dContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void Box2dContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}
