#pragma once
#include "Seting.h"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <locale>
#include "UserMap.h"
#include "UserTileLayer.h"
class UserTileLayer;
class MapLoader
{
public:
	UserTileLayer* userTileLayer;
	MapLoader();
	~MapLoader();
};

