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

HRESULT FristCommonTset::InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window)
{
	LPCWSTR type1 = StringUtil::ConvertLPSTRToLPWSTR(Window::EventMouseButtonDown.c_str());
	if (_wcsicmp(name,L"testWindow1") == 0 && _wcsicmp(type,StringUtil::ConvertLPSTRToLPWSTR(Window::EventMouseButtonDown.c_str())) == 0) {
		game->state = new Vibration(game);
	}
	return E_NOTIMPL;
}

HRESULT FristCommonTset::Render()
{
	return E_NOTIMPL;
}


HRESULT getData()
{
	return E_NOTIMPL;
}