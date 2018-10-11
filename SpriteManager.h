#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class SpriteManager :public BaseSprite
{
public:
	Sprite m_Sprite[100];
	int Sprite_Insert(LPCWSTR  path, int x, int y, int angels);
	int Sprite_Insert(LPDIRECT3DTEXTURE9 * Texture, int x, int y, int angels);
	Sprite* Sprite_Select(int id);
	HRESULT Sprite_Update(int id,float x, float y, int angels);
private:
	void OUpdate() override;
	void ORender() override;

};
