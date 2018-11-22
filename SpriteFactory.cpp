#include "SpriteFactory.h"
#include "AnimationFrame.h"

SpriteFactory::SpriteFactory()
{
}


SpriteFactory::~SpriteFactory()
{
}

shared_ptr<BaseSprite> SpriteFactory::getSprite(SpriteType spritetype)
{
	switch (spritetype) {
	case SpriteType::TSprite: {return make_shared<AnimationFrame>();}
	}
}
