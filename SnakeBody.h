#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class SnakeBody:BaseSprite {
private:
	int snakeup;
public:
	list<BaseSprite*> bodys;
	HRESULT Update() override;
	HRESULT Render() override;
};
