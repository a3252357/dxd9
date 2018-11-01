#pragma once
#include <iostream>
#include <tmxlite/Map.hpp>
#include <locale>
#include <tmxlite/TileLayer.hpp>
class UserMap
{
public:
	UserMap(const tmx::Map& map, std::size_t layerIdx);
	~UserMap();
};

