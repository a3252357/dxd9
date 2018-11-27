#pragma once
#include "string"
#include "BaseSprite.h"
#include "ListUser.h"
#include "Subject.h"
#include "Achievements.h"
#include "AnimationFrame.h"
class Sprite;
class SnakeBody:public BaseSprite,public Subject{
private:
	int snakeup=0;
public:
	SnakeBody();
	~SnakeBody();
	ListUser<shared_ptr<AnimationFrame>> bodys;
	HRESULT Add(shared_ptr<AnimationFrame> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	bool snake();
	//�ص�����  
};
