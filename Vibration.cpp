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

HRESULT Vibration::InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window)
{
	return E_NOTIMPL;
}

HRESULT Vibration::Render()
{
	return E_NOTIMPL;
}
