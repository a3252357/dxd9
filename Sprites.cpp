#include "Sprites.h"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
}
HRESULT Sprites::Update()
{
	list<BaseSprite*>::iterator plist;
	for (plist = sprites.begin(); plist != sprites.end(); plist++) {
		BaseSprite* base = *plist;
		if (base->getType()==0) {
			base->Update();
		}
	}
	return S_OK;
}

HRESULT Sprites::Init()
{
	return S_OK;
}

HRESULT Sprites::Render()
{
	list<BaseSprite*>::iterator plist;
	for (plist = sprites.begin(); plist != sprites.end(); plist++) {
		BaseSprite* base = *plist;
		if (base->getType() == 0) {
			base->Render();
		}
	}
	return S_OK;
}

HRESULT Sprites::AddSprite(BaseSprite* _sprite)
{
	sprites.push_back(_sprite);
	return S_OK;
}
