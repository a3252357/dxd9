#include "MapLoader.h"
#include "UserTileLayer.h"

MapLoader::MapLoader()
{
	tmx::Map map;
	if (map.load("F:/ConsoleApplication2/map/tileset/untitled.tmx"))
	{

		userTileLayer = new UserTileLayer(map, 0);
		userTileLayer1 = new UserTileLayer(map, 1);
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
