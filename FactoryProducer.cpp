#include "FactoryProducer.h"

AbstractFactory FactoryProducer::getFactory(string choice)
{
	if (choice == "sprite") {
		return SpriteFactory();
	}
}
