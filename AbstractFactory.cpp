#include "AbstractFactory.h"

shared_ptr<BaseSprite> AbstractFactory::getSprite(SpriteType color)
{
	return make_shared<BaseSprite>();
}
