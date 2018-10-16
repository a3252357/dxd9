#pragma once
#include "Seting.h"
#include "AbstractFactory.h"
 class FactoryProducer {
 public:
	 static shared_ptr<AbstractFactory> getFactory(string choice);
};
