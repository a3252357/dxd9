#pragma once
#include "Seting.h"
#include "BaseSprite.h"
#include "ListUser.h"
class Sprite;
class SnakeBody:public BaseSprite {
private:
	int snakeup=0;
	ListUser<shared_ptr<Sprite>> bodys;
public:
	SnakeBody();
	~SnakeBody();
	HRESULT Add(shared_ptr<Sprite> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	void snakenext();
	static SnakeBody* CurMy;//�洢�ص��������õĶ���  
	static void* callback();
	void setCurMy();
	//�ص�����  
};
