#pragma once
#include "Seting.h"
#include "BaseSprite.h"
#include "Event.h"

class Observer {
public:
	virtual ~Observer()
	{

	}
	virtual void onNotify(shared_ptr<BaseSprite> sprite, Huangjianjian::Event event) = 0;
};
