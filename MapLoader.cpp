#include "MapLoader.h"
#include <codecvt>
#include "UserObejectLayer.h"

MapLoader::MapLoader()
{
	tmx::Map map;
	if (map.load("map/tileset/untitled.tmx"))
	{
		userTileLayer = new UserTileLayer(map, 0);
		//UserObejectLayer * box = new UserObejectLayer(map,1);
	}
	else
	{
		std::cout << "Failed loading map" << std::endl;
	}
}


MapLoader::~MapLoader()
{
}
