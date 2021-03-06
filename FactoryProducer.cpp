#include "FactoryProducer.h"
#include "SpriteFactory.h"

shared_ptr<AbstractFactory> FactoryProducer::getFactory(string choice)
{
	if (choice == "sprite") {
		return make_shared<SpriteFactory>();
	}
}
