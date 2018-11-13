#pragma once
#include "Seting.h"
#include "Observer.h"
#include "SystemInit.h"
class Achievements:public Observer
{
public:
	Achievements();
	~Achievements();
	// Í¨¹ý Observer ¼Ì³Ð
	virtual void onNotify(shared_ptr<BaseSprite>, Huangjianjian::Event event) override;
};

