#include "Sprites.h"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
}
HRESULT Sprites::Update()
{
	list<shared_ptr<BaseSprite>>::iterator plist;
	for (plist = sprites.begin(); plist != sprites.end(); plist++) {
		shared_ptr<BaseSprite> base = *plist;
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
	list<shared_ptr<BaseSprite>>::iterator plist;
	for (plist = sprites.begin(); plist != sprites.end(); plist++) {
		shared_ptr<BaseSprite> base = *plist;
		if (base->getType() == 0) {
			base->Render();
		}
	}
	return S_OK;
}

HRESULT Sprites::AddSprite(shared_ptr<BaseSprite> _sprite)
{
	sprites.push_back(_sprite);
	return S_OK;
}
