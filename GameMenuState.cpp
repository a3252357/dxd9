#include "GameMenuState.h"
#include "SnakeGameMenuUI.h"
#include "GamingState.h"

GameMenuState::GameMenuState(BaseGame *_game)
{
	game = _game;
	background = new AnimationFrame();
	Texture2d * back = D3DUtil::getTexture(L"C:/Users/musi/Documents/Games/Project1/img/parallaxes/Ocean1.png");
	float sx = (float)SCREEN_WIDTH / (float)back->w;
	float sy = (float)SCREEN_HEIGHT / (float)back->h;
	background->Add_AnimationSprite(back, 0, 0, 0,sx, sy);
	Texture2d * back1 = D3DUtil::getTexture(L"C:/Users/musi/Documents/Games/Project1/img/parallaxes/SeaofClouds.png");
	float sx1 = (float)SCREEN_WIDTH / (float)back1->w;
	float sy1 = (float)SCREEN_HEIGHT / (float)back1->h;
	background->Add_AnimationSprite(back1, 0, 0, 0, sx1, sy1);
	background->Start();
}


GameMenuState::~GameMenuState()
{
}

HRESULT GameMenuState::Update()
{
	background->Update();
	return E_NOTIMPL;
}

HRESULT GameMenuState::ChangeState()
{
	return E_NOTIMPL;
}

HRESULT GameMenuState::InputHandle(LPCWSTR name, LPCWSTR type, const EventArgs & e, Window * window)
{
	LPCWSTR type1 = StringUtil::ConvertLPSTRToLPWSTR(Window::EventMouseButtonDown.c_str());
	if (_wcsicmp(name, L"testWindow1") == 0 && _wcsicmp(type, StringUtil::ConvertLPSTRToLPWSTR(Window::EventMouseButtonDown.c_str())) == 0) {
		game->state = new GamingState(game);
		CEGUI::Window* myRoot = (CEGUI::Window*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
		System::getSingleton().createGUIContext(UISystem::myRenderer->getDefaultRenderTarget());
		System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);
	}
	return E_NOTIMPL;
}

HRESULT GameMenuState::Render()
{
	background->Render();
	D3DUtil::getID3DXSprite()->End();
	return E_NOTIMPL;
}
