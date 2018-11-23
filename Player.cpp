#include "Player.h"



Player::Player(vector<AnimationFrame*> _playeranimations)
{
	playeranimations = _playeranimations;
	cuanimations = playeranimations[0];
	cuanimations->Start();
//	as->Sprite_Init(StringUtil::ConvertstringToLPCWSTR(ts.getTile(tileid)->imagePath), x*BOX_WIDTH, y*BOX_WIDTH, 0.0f, ts.getTile(tileid)->imagePosition.x, ts.getTile(tileid)->imagePosition.y, BOX_WIDTH, BOX_WIDTH);
}


Player::~Player()
{
}

HRESULT Player::Update()
{
	cuanimations->Update();
	return E_NOTIMPL;
}

HRESULT Player::Render()
{
	cuanimations->Render();
	return E_NOTIMPL;
}


