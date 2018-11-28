#include "MapLoader.h"
#include "UserTileLayer.h"

MapLoader::MapLoader()
{
	tmx::Map map;
	if (map.load("F:/ConsoleApplication2/map/tileset/untitled.tmx"))
	{
		userTileLayer.push_back(new UserTileLayer(map, 0));
		userTileLayer.push_back(new UserTileLayer(map, 1));
		userTileLayer.push_back(new UserTileLayer(map, 2));

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

HRESULT MapLoader::Update()
{
	vector<BaseSprite *>::iterator plist;
	for (plist = userTileLayer.begin(); plist != userTileLayer.end(); plist++) {
		BaseSprite* base = *plist;
		if (base->getType() == 0) {
			base->Update();
		}
	}
	return S_OK;
}

HRESULT MapLoader::Render()
{
	vector<BaseSprite *>::iterator plist;
	for (plist = userTileLayer.begin(); plist != userTileLayer.end(); plist++) {
		BaseSprite* base = *plist;
		if (base->getType() == 0) {
			base->Render();
		}
	}
	return S_OK;
}
