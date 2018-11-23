#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class Box2dContactListener:public b2ContactListener
{
private:
	//Åö×²¿ªÊ¼
	void BeginContact(b2Contact* contact) override;
	//Åö×²½áÊø
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)override;
};

