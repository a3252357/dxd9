#include "FristCommonTset.h"



FristCommonTset::FristCommonTset(BaseGame * _game)
{
	game = _game;
	game->ui = new CommonTestUI(game);
}


FristCommonTset::~FristCommonTset()
{
}

HRESULT FristCommonTset::Update()
{
	//game->Update();
	//game->Render();
	//HRESULT data=getData();
	//if (data != E_NOTIMPL) {

	//}
	return E_NOTIMPL;
}

HRESULT FristCommonTset::ChangeState()
{
	return E_NOTIMPL;
}


HRESULT getData()
{
	return E_NOTIMPL;
}