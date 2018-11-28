#include "GamingState.h"



GamingState::GamingState(BaseGame * _game)
{
	game = _game;
	maps = new MapLoader();
}


GamingState::~GamingState()
{

}

HRESULT GamingState::Update()
{
	maps->Update();
	return E_NOTIMPL;
}

HRESULT GamingState::ChangeState()
{
	return E_NOTIMPL;
}

HRESULT GamingState::Render()
{
	maps->Render();
	return E_NOTIMPL;
}

HRESULT GamingState::InputHandle(LPCWSTR name, LPCWSTR type, const CEGUI::EventArgs & e, CEGUI::Window * window)
{
	return E_NOTIMPL;
}
