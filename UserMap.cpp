#include "UserMap.h"

UserMap::UserMap(const tmx::Map& map, std::size_t layerIdx)
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
}


UserMap::~UserMap()
{
}
