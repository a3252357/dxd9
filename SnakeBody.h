#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class SnakeBody:BaseSprite {
private:
	int snakeup;
	list<BaseSprite*> bodys;
public:
	HRESULT Add(BaseSprite* _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
};
