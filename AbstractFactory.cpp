#include "AbstractFactory.h"

AbstractFactory::AbstractFactory()
{
}

AbstractFactory::~AbstractFactory()
{
}

shared_ptr<BaseSprite> AbstractFactory::getSprite(SpriteType color)
{
	return make_shared<BaseSprite>();
}
