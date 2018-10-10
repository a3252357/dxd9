#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class SnakeBody:BaseSprite {
private:
	int snakeup;
	list<shared_ptr<Sprite>> bodys;
public:
	HRESULT Add(shared_ptr<Sprite> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	void snakenext();
};
