#include "Vibration.h"

Vibration::Vibration(BaseGame *_game)
{
	game = _game;
	game->ui = new VibrationUI(game);
}


Vibration::~Vibration()
{
}

HRESULT Vibration::Update()
{
	//HRESULT data=getData();
	//if (data != E_NOTIMPL) {

	//}
	return E_NOTIMPL;
}

HRESULT Vibration::ChangeState()
{
	return E_NOTIMPL;
}
