#pragma once
#include "Seting.h"
#include "ListUser.h"
#include "BaseSprite.h"
#include "AnimationFrame.h"
class UserSixTileLayer : public BaseSprite
{
private:
	int snakeup = 0;
	ListUser<shared_ptr<AnimationFrame>> bodys;
public:
	UserSixTileLayer(const tmx::Map& map, std::size_t layerIdx);
	int getTiles(const std::vector<tmx::Tileset>& tilesets, long ID);
	~UserSixTileLayer();
	HRESULT Add(shared_ptr<AnimationFrame> _sprite);
	HRESULT Update() override;
	HRESULT Render() override;
	//TimerWithSprite<UserTileLayer>* timer;
public:
};

