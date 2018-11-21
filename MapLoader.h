#pragma once
#include "Seting.h"
#include "UserMap.h"
#include "UserObejectLayer.h"
#include "BaseSprite.h"
class UserTileLayer;
class MapLoader:public BaseSprite
{
public:
	vector<BaseSprite *> userTileLayer;
	MapLoader();
	~MapLoader();
	HRESULT Update() override;
	HRESULT Render() override;
};

