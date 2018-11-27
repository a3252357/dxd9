#include "UserSixTileLayer.h"



UserSixTileLayer::UserSixTileLayer(const tmx::Map& map, std::size_t layerIdx)
{
	const auto& layers = map.getLayers();

	if (layerIdx >= layers.size() || (layers[layerIdx]->getType() != tmx::Layer::Type::Tile))
	{
		std::cout << "Invalid layer index or layer type, layer will be empty" << std::endl;
		return;
	}
	const auto layer = dynamic_cast<const tmx::TileLayer*>(layers[layerIdx].get());

	//auto bounds = map.getBounds();
	/*
	float verts[] =
	{
	  bounds.left, bounds.top, 0.f, 0.f, 0.f,
	  bounds.left + bounds.width, bounds.top, 0.f, 1.f, 0.f,
	  bounds.left, bounds.top + bounds.height, 0.f, 0.f, 1.f,
	  bounds.left + bounds.width, bounds.top + bounds.height, 0.f, 1.f, 1.f
	};
	*/

	const auto& mapSize = map.getTileCount();
	const auto& tilesets = map.getTilesets();

	for (auto y = 0; y < mapSize.y; ++y)
	{
		for (auto x = 0; x < mapSize.x; ++x)
		{
			auto idx = y * mapSize.x + x;
			const auto& tileIDs = layer->getTiles();
			auto idz = tileIDs[idx].ID;
			const auto& ts = tilesets[getTiles(tilesets, idz)];
			shared_ptr<AnimationFrame> as = make_shared<AnimationFrame>();
			if (idz == 0)continue;
			auto asa = &ts.getTile(idz)->animation.frames;
			if (ts.getTile(idz)->animation.frames.size() > 0) {
				if (x % 2 == 0)
				for (int i = 0; i < ts.getTile(idz)->animation.frames.size(); i++) {
					auto tileid = ts.getTile(idz)->animation.frames[i].tileID + ts.getFirstGID();
					as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), (int)(map.getTileSize().x*x) * 3 / 4 - (int)map.getTileSize().x / 4, (int)map.getTileSize().y*y - (int)map.getTileSize().y * 5 / 4, 0.0f, (int)ts.getTile(idz)->imagePosition.x, (int)ts.getTile(idz)->imagePosition.y, (int)ts.getTile(idz)->imageSize.x, ts.getTile(idz)->imageSize.y, 1, 1);
				}
			}
			else {
				if (x % 2 == 0) {
					as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), (int)(map.getTileSize().x*x) * 3 / 4-(int)map.getTileSize().x / 4, (int)map.getTileSize().y*y - (int)map.getTileSize().y*5/4, 0.0f, (int)ts.getTile(idz)->imagePosition.x, (int)ts.getTile(idz)->imagePosition.y, (int)ts.getTile(idz)->imageSize.x, ts.getTile(idz)->imageSize.y, 1, 1);
				}
				else {
					//		as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), (map.getTileSize().x*x) * 3 / 4 - 1, map.getTileSize().y*y + map.getTileSize().y / 2, 0.0f, ts.getTile(idz)->imagePosition.x, ts.getTile(idz)->imagePosition.y, ts.getTile(idz)->imageSize.x, ts.getTile(idz)->imageSize.y, 1, 1);
				}
			}
			if (x % 2 == 0) {
				//as->Start();
				Add(as);
			}
		}

		for (auto x = 0; x < mapSize.x; ++x)
		{
			auto idx = y * mapSize.x + x;
			const auto& tileIDs = layer->getTiles();
			auto idz = tileIDs[idx].ID;
			const auto& ts = tilesets[getTiles(tilesets, idz)];
			shared_ptr<AnimationFrame> as = make_shared<AnimationFrame>();
			if (idz == 0)continue;
			auto asa = &ts.getTile(idz)->animation.frames;
			if (x % 2 != 0)
			if (ts.getTile(idz)->animation.frames.size() > 0) {
				for (int i = 0; i < ts.getTile(idz)->animation.frames.size(); i++) {
					auto tileid = ts.getTile(idz)->animation.frames[i].tileID + ts.getFirstGID();
					as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), (int)(map.getTileSize().x*x) * 3 / 4 - (int)map.getTileSize().x / 4, (int)map.getTileSize().y*y - (int)map.getTileSize().y * 3 / 4, 0.0f, (int)ts.getTile(idz)->imagePosition.x, (int)ts.getTile(idz)->imagePosition.y, (int)ts.getTile(idz)->imageSize.x, ts.getTile(idz)->imageSize.y, 1, 1);
				}
			}
			else {
				if (x % 2 != 0) {
					as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), (int)(map.getTileSize().x*x) * 3 / 4- (int) map.getTileSize().x/4, (int)map.getTileSize().y*y - (int)map.getTileSize().y*3/4, 0.0f, (int)ts.getTile(idz)->imagePosition.x, (int)ts.getTile(idz)->imagePosition.y, (int)ts.getTile(idz)->imageSize.x, ts.getTile(idz)->imageSize.y, 1, 1);
				}
			}
			if (x % 2 != 0) {
				//as->Start();
				Add(as);
			}
		}

	}

}
int UserSixTileLayer::getTiles(const std::vector<tmx::Tileset>& tilesets, long ID)
{
	for (auto i = 0; i < tilesets.size(); ++i) {
		if (ID >= tilesets[i].getFirstGID() && ID <= tilesets[i].getLastGID())return i;
	}
	return S_OK;
}

UserSixTileLayer::~UserSixTileLayer()
{
}

HRESULT UserSixTileLayer::Add(shared_ptr<AnimationFrame> _sprite)
{
	bodys.add(_sprite);
	return S_OK;
}

HRESULT UserSixTileLayer::Update()
{
	bodys.setHeadToNow();
	for (int i = 0; i < bodys.size(); i++)
	{
		bodys.getNow()->data->Update();
		bodys.goNext();
	}
	return S_OK;
}

HRESULT UserSixTileLayer::Render()
{
	bodys.setHeadToNow();
	for (int i = 0; i < bodys.size(); i++)
	{
		bodys.getNow()->data->Render();
		bodys.goNext();
	}
	return S_OK;
}