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
	for (auto i = 0; i < tilesets.size(); ++i)
	{
		for (auto x = 0; x < mapSize.x; ++x)
		{
			for (auto y = 0; y < mapSize.y; ++y)
			{
				auto idx = y * mapSize.x + x;
				const auto& ts = tilesets[i];
				const auto& tileIDs = layer->getTiles();
				auto idz= (tileIDs[idx].ID - ts.getFirstGID()) + 1;
				shared_ptr<Sprite> as = make_shared<Sprite>();
				if (ts.getTile(idz)->animation.frames.size() > 0) {
					for (int i = 0;i < ts.getTile(idz)->animation.frames.size();i++) {
						auto tileid = ts.getTile(idz)->animation.frames[i].tileID + ts.getFirstGID();
						if (i == 0) {
							as->Sprite_Init(StringUtil::ConvertstringToLPCWSTR(ts.getTile(tileid)->imagePath), x*BOX_WIDTH, y*BOX_WIDTH, 0.0f, ts.getTile(tileid)->imagePosition.x, ts.getTile(tileid)->imagePosition.y, BOX_WIDTH, BOX_WIDTH);
						}
						else {
							as->Sprite_Add(StringUtil::ConvertstringToLPCWSTR(ts.getTile(tileid)->imagePath), ts.getTile(tileid)->imagePosition.x, ts.getTile(tileid)->imagePosition.y, BOX_WIDTH, BOX_WIDTH);
						}
					}
				}
				else {
					as->Sprite_Init(StringUtil::ConvertstringToLPCWSTR(ts.getTile(idz)->imagePath), x*BOX_WIDTH, y*BOX_WIDTH, 0.0f, ts.getTile(idz)->imagePosition.x, ts.getTile(idz)->imagePosition.y, BOX_WIDTH, BOX_WIDTH);
				}
				as->m_animationFrame->Start(1000);
				Add(as);
			}
		}
	}
}


UserTileLayer::~UserTileLayer()
{
}

HRESULT UserTileLayer::Add(shared_ptr<Sprite> _sprite)
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