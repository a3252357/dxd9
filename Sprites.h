#pragma once
#include "Seting.h"
class Sprites{
	private:
		list<Base> sprites;
		HRESULT Update();
		HRESULT Init();
		HRESULT Render();
	public:
		HRESULT AddSprite();
};
