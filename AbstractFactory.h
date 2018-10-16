#pragma once
#include <memory>
#include "BaseSprite.h"
#include "SpriteType.h"
using namespace std;
class AbstractFactory
{
public:
	virtual shared_ptr<BaseSprite> getSprite(SpriteType sprite)=0;
};

