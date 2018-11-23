#include "UserTileLayer.h"



UserTileLayer::UserTileLayer(const tmx::Map& map, std::size_t layerIdx)
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

		for (auto x = 0; x < mapSize.x; ++x)
		{
			for (auto y = 0; y < mapSize.y; ++y)
			{
				auto idx = y * mapSize.x + x;
				const auto& tileIDs = layer->getTiles();
				auto idz = tileIDs[idx].ID;
				const auto& ts = tilesets[getTiles(tilesets, idz)];
				shared_ptr<AnimationFrame> as = make_shared<AnimationFrame>();
				if(idz==0)continue;
				auto asa= &ts.getTile(idz)->animation.frames;
				if (ts.getTile(idz)->animation.frames.size() > 0) {
					for (int i = 0;i < ts.getTile(idz)->animation.frames.size();i++) {
							auto tileid = ts.getTile(idz)->animation.frames[i].tileID + ts.getFirstGID();
							as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(tileid)->imagePath), x*BOX_WIDTH, y*BOX_WIDTH, 0.0f, ts.getTile(tileid)->imagePosition.x, ts.getTile(tileid)->imagePosition.y, BOX_WIDTH, BOX_WIDTH,1,1);
					}
				}
				else {
					as->Add_AnimationSprite(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), x*BOX_WIDTH, y*BOX_WIDTH, 0.0f, ts.getTile(idz)->imagePosition.x, ts.getTile(idz)->imagePosition.y, BOX_WIDTH, BOX_WIDTH, 1, 1);
				}
				as->Start();
				Add(as);
			}
		}
	
}
int UserTileLayer::getTiles(const std::vector<tmx::Tileset>& tilesets,long ID)
{
	for (auto i = 0; i < tilesets.size(); ++i) {
		if (ID >= tilesets[i].getFirstGID() && ID <= tilesets[i].getLastGID())return i;
	}
	return S_OK;
}

UserTileLayer::~UserTileLayer()
{
}

HRESULT UserTileLayer::Add(shared_ptr<AnimationFrame> _sprite)
{
	bodys.add(_sprite);
	return S_OK;
}

HRESULT UserTileLayer::Update()
{
	for (int i = 0;i < bodys.size();i++)
	{
		bodys.find(i)->Update();
	}
	return S_OK;
}

HRESULT UserTileLayer::Render()
{
	for (int i = 0;i < bodys.size();i++)
	{
		bodys.find(i)->Render();
	}
	return S_OK;
}