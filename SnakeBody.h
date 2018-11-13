#pragma once
#include "string"
#include "BaseSprite.h"
#include "ListUser.h"
#include "Sprite.h"
#include "Subject.h"
#include "Achievements.h"
class Sprite;
class SnakeBody:public BaseSprite,public Subject{
private:
	int snakeup=0;
	ListUser<shared_ptr<Sprite>> bodys;
public:
	SnakeBody();
	~SnakeBody();
	HRESULT Add(shared_ptr<Sprite> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	bool snake();
	//»Øµ÷º¯Êý  
};
