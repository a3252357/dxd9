#pragma once
#include "Seting.h"
#include "AbstractFactory.h"
class BaseSprite;
class SpriteFactory:public AbstractFactory
{
public:
	SpriteFactory();
	~SpriteFactory();
	shared_ptr<BaseSprite> getSprite(SpriteType spritetype) override;
};

