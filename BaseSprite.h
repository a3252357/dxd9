#pragma once
#include "Seting.h"
class BaseSprite
{
protected:
	int type=0;
public:
	virtual int getType();
	virtual HRESULT Update();
	virtual HRESULT Render();
	virtual HRESULT OnTriggerStar(b2Contact* contact);
};
	