#pragma once
#include "Seting.h"
#include "Observer.h"
#include "SystemInit.h"
class Achievements:public Observer
{
public:
	Achievements();
	~Achievements();
	// ͨ�� Observer �̳�
	virtual void onNotify(shared_ptr<BaseSprite>, Huangjianjian::Event event) override;
};

