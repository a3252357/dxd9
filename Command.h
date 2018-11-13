#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class Command
{
public:
	virtual ~Command() {};
	virtual void execute() = 0;
	virtual void undo() = 0;
};

