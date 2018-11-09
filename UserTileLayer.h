#pragma once
#include "Seting.h"
#include "ListUser.h"
#include "BaseSprite.h"
#include "AnimationFrame.h"
#include "Sprite.h"
class Sprite;
class UserTileLayer: public BaseSprite
{
private:
	int snakeup = 0;
	ListUser<shared_ptr<Sprite>> bodys;
public:
	UserTileLayer(const tmx::Map& map, std::size_t layerIdx);
	~UserTileLayer();
	HRESULT Add(shared_ptr<Sprite> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	//TimerWithSprite<UserTileLayer>* timer;
public:
};

