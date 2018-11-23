#include "BaseSprite.h"

int BaseSprite::getType()
{
	return type;
}

HRESULT BaseSprite::Update()
{
	return S_OK;
}

HRESULT BaseSprite::Render()
{
	return S_OK;
}

HRESULT BaseSprite::OnTriggerStar(b2Contact * contact)
{
	return E_NOTIMPL;
}
