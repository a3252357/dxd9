#pragma once
#include "Seting.h"
#include "BaseSprite.h"
#include "ListUser.h"
#include "Sprite.h"
#include "TimerData.h"
class Sprite;
class SnakeBody:public BaseSprite,public TimerData{
private:
	int snakeup=0;
	ListUser<shared_ptr<Sprite>> bodys;
public:
	SnakeBody();
	~SnakeBody();
	HRESULT Add(shared_ptr<Sprite> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	void callback() override;
	//»Øµ÷º¯Êý  
};
