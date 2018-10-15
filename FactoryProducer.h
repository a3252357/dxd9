#pragma once
#include "Seting.h"
#include "AbstractFactory.h"
 class FactoryProducer {
 public:
	 static AbstractFactory getFactory(string choice);
};
