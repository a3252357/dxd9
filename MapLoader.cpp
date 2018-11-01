#include "MapLoader.h"
#include <codecvt>

MapLoader::MapLoader()
{
	tmx::Map map;
	if (map.load("map/tileset/untitled.tmx"))
	{
		userTileLayer = new UserTileLayer(map, 0);
	}
	else
	{
		std::cout << "Failed loading map" << std::endl;
	}
}


MapLoader::~MapLoader()
{
}
