#pragma once
#include "Seting.h"
#include "ListUser.h"
#include "BaseSprite.h"
#include "AnimationFrame.h"
class UserTileLayer: public BaseSprite
{
private:
	int snakeup = 0;
	ListUser<shared_ptr<AnimationFrame>> bodys;
public:
	UserTileLayer(const tmx::Map& map, std::size_t layerIdx);
	int getTiles(const std::vector<tmx::Tileset>& tilesets, long ID);
	~UserTileLayer();
	HRESULT Add(shared_ptr<AnimationFrame> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	//TimerWithSprite<UserTileLayer>* timer;
public:
};

