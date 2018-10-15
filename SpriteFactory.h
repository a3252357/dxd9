#pragma once
#include "AbstractFactory.h"
#include "Seting.h"
class BaseSprite;
class SpriteFactory:public AbstractFactory
{
public:
	SpriteFactory();
	~SpriteFactory();
	shared_ptr<BaseSprite> getSprite(SpriteType spritetype) override;
};

