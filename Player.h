#pragma once
#include "Seting.h"
#include "AnimationFrame.h"
class Player:public BaseSprite
{
public:
	vector<AnimationFrame*> playeranimations;
	AnimationFrame* cuanimations;
	Player(vector<AnimationFrame*> _playeranimations);
	~Player();
	virtual HRESULT Update() override;
	virtual HRESULT Render() override;
};
