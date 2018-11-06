#pragma once
#include <iostream>
#include <tmxlite/Map.hpp>
#include <locale>
#include <tmxlite/TileLayer.hpp>
#include "Seting.h"
#include "ListUser.h"
#include "AnimationFrame.h"
class Sprite;
class UserObejectLayer
{
public:
	UserObejectLayer(const tmx::Map& map, std::size_t layerIdx);
	~UserObejectLayer();
};

