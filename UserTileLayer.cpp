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

	auto bounds = map.getBounds();
	float verts[] =
	{
	  bounds.left, bounds.top, 0.f, 0.f, 0.f,
	  bounds.left + bounds.width, bounds.top, 0.f, 1.f, 0.f,
	  bounds.left, bounds.top + bounds.height, 0.f, 0.f, 1.f,
	  bounds.left + bounds.width, bounds.top + bounds.height, 0.f, 1.f, 1.f
	};

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
				//as->Sprite_Add(StringUtil::ConvertstringToLPCWSTR(ts.getTile((tileIDs[idx].ID - ts.getFirstGID()))->imagePath),((tileIDs[idx].ID - ts.getFirstGID())) % 64 * 16, ((tileIDs[idx].ID - ts.getFirstGID()) + 1) / 64 * 16, BOX_WIDTH, BOX_WIDTH);
				//as->Sprite_Add(StringUtil::ConvertstringToLPCWSTR(ts.getTile((tileIDs[idx].ID - ts.getFirstGID()))->imagePath), ((tileIDs[idx].ID - ts.getFirstGID())+2) % 64 * 16, ((tileIDs[idx].ID - ts.getFirstGID()) + 1) / 64 * 16, BOX_WIDTH, BOX_WIDTH);
				as->m_animationFrame->Start(1000);
				Add(as);
			}
		}
	}
	/*
	for (auto i = 0u; i < tilesets.size(); ++i)
	{
		//check each tile ID to see if it falls in the current tile set
		const auto& ts = tilesets[i];
		const auto& tileIDs = layer->getTiles();
		std::vector<std::uint16_t> pixelData;
		bool tsUsed = false;

		for (auto y = 0u; y < mapSize.y; ++y)
		{
			for (auto x = 0u; x < mapSize.x; ++x)
			{
				auto idx = y * mapSize.x + x;
				if (idx < tileIDs.size() && tileIDs[idx].ID >= ts.getFirstGID()
					&& tileIDs[idx].ID < (ts.getFirstGID() + ts.getTileCount()))
				{
					pixelData.push_back(static_cast<std::uint16_t>((tileIDs[idx].ID - ts.getFirstGID()) + 1)); //red channel - making sure to index relative to the tileset
					pixelData.push_back(static_cast<std::uint16_t>(tileIDs[idx].flipFlags)); //green channel - tile flips are performed on the shader
					tsUsed = true;
					string path = ts.getImagePath();
					shared_ptr<Sprite> as =make_shared<Sprite>();
					int x1 = x;
					int y1 = y;
					as->Sprite_Init(StringUtil::ConvertstringToLPCWSTR(path), x1*BOX_WIDTH, y1*BOX_WIDTH,0.0f, ts.getTile((tileIDs[idx].ID - ts.getFirstGID())+1)->imagePosition.x, ts.getTile((tileIDs[idx].ID - ts.getFirstGID())+1)->imagePosition.y+16, BOX_WIDTH, BOX_WIDTH);
					Add(as);
				}
				else
				{
					//pad with empty space
					pixelData.push_back(0);
					pixelData.push_back(0);
				}
			}
		}

		//if we have some data for this tile set, create the resources
		if (tsUsed)
		{
		}
	}
	*/
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