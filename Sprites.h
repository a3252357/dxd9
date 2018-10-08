#pragma once
#include "BaseSprite.h"
#include "Seting.h"
class Sprites{
	private:
		list<BaseSprite*> sprites;
		HRESULT Update();
		HRESULT Init();
		HRESULT Render();
	public:
		Sprites();
		~Sprites();
		HRESULT AddSprite(BaseSprite* _sprite);
};
