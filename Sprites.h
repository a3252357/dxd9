#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class Sprites{
	private:
		list<shared_ptr<BaseSprite>> sprites;
	public:
		Sprites();
		~Sprites();
		HRESULT Update();
		HRESULT Init();
		HRESULT Render();
		HRESULT AddSprite(shared_ptr<BaseSprite> _sprite);
};
