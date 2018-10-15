#pragma once
#include "Seting.h"
class BaseSprite;
class AbstractFactory
{
public:
	AbstractFactory();
	~AbstractFactory();
	virtual shared_ptr<BaseSprite> getSprite(SpriteType sprite);
};

