#pragma once
#include "BaseSprite.h"
#include "Seting.h"
class Sprites{
	private:
		list<shared_ptr<BaseSprite>> sprites;
		HRESULT Update();
		HRESULT Init();
		HRESULT Render();
	public:
		Sprites();
		~Sprites();
		HRESULT AddSprite(shared_ptr<BaseSprite> _sprite);
};
