#pragma once
#include <d3d9.h>
class BaseSprite
{
protected:
	int type=0;
public:
	virtual int getType();
	virtual HRESULT Update();
	virtual HRESULT Render();
};
	