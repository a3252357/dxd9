#pragma once
#include <iostream>
#include <tmxlite/Map.hpp>
#include <locale>
#include <tmxlite/TileLayer.hpp>
#include "Seting.h"
#include "ListUser.h"
class Sprite;
class UserTileLayer:BaseSprite
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

