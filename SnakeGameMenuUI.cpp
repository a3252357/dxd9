#include "SnakeGameMenuUI.h"



SnakeGameMenuUI::SnakeGameMenuUI(BaseGame * _game)
{
	game = _game;
	Init();
}

SnakeGameMenuUI::~SnakeGameMenuUI()
{
}

HRESULT SnakeGameMenuUI::Update()
{
	return E_NOTIMPL;
}

HRESULT SnakeGameMenuUI::Init()
{
	//CEGUI::Font &defaultFont = CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei33",12,true,"simhei.ttf");
	CEGUI::FontManager& ma = CEGUI::FontManager::getSingleton();
	myRoot = (CEGUI::Window*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	System::getSingleton().createGUIContext(UISystem::myRenderer->getDefaultRenderTarget());
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	DefaultWindow* fWnd = (DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Label", "testWindow");
	fWnd->subscribeEvent(Editbox::EventMouseButtonDown, CEGUI::Event::Subscriber(&SnakeGameMenuUI::onMouseButtonDown, this));
	fWnd->setPosition(UVector2(UDim(0.4f, 0.0f), UDim(0.2f, 0.0f)));
	// set size to be half the size of the parent
	Font& font=CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei30", 100, true, "simhei.ttf");
	fWnd->setSize(USize(UDim(0.2f, 0.0f), UDim(0.2f, 0.0f)));
	fWnd->setFont(&font);
	fWnd->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"械羽"));
	myRoot->addChild(fWnd);

	PushButton* fWnd1 = (PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "testWindow1");
	fWnd1->subscribeEvent(PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&SnakeGameMenuUI::onMouseButtonDown, this));
	fWnd1->setPosition(UVector2(UDim(0.425f, 0.0f), UDim(0.4f, 0.0f)));
	//fWnd1->setProperty("name");
	// set size to be half the size of the parent
	fWnd1->setSize(USize(UDim(0.15f, 0.0f), UDim(0.1f, 0.0f)));
	fWnd1->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"开始游戏"));
	myRoot->addChild(fWnd1);

	PushButton* fWnd2 = (PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "testWindow2");
	fWnd2->subscribeEvent(PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&SnakeGameMenuUI::onMouseButtonDown, this));
	fWnd2->setPosition(UVector2(UDim(0.425f, 0.0f), UDim(0.55f, 0.0f)));
	//fWnd1->setProperty("name");
	// set size to be half the size of the parent
	fWnd2->setSize(USize(UDim(0.15f, 0.0f), UDim(0.1f, 0.0f)));
	fWnd2->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"继续游戏"));
	myRoot->addChild(fWnd2);

	PushButton* fWnd3 = (PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "testWindow3");
	fWnd3->subscribeEvent(PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&SnakeGameMenuUI::onMouseButtonDown, this));
	fWnd3->setPosition(UVector2(UDim(0.425f, 0.0f), UDim(0.70f, 0.0f)));
	//fWnd1->setProperty("name");
	// set size to be half the size of the parent
	fWnd3->setSize(USize(UDim(0.15f, 0.0f), UDim(0.1f, 0.0f)));
	fWnd3->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"退出游戏"));
	myRoot->addChild(fWnd3);
	//CEGUI::String fontSizeString = "12";
	//float fontSize = CEGUI::PropertyHelper<float>::fromString(fontSizeString);
	//if (fontSize != 0.0f)
	//defaultFont.setProperty<float>("PointSize", fontSize);
	//CEGUI::DefaultWindow* quitBtn = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Label", (CEGUI::utf8*)"Quit");
	//quitBtn->setFont(&defaultFont);
	//quitBtn->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"贪吃蛇"));
	//((CEGUI::Font*)quitBtn->getFont())->setProperty<float>("PointSize", 12.0f);
	//quitBtn->setPosition(UVector2(UDim(0.45f, 0.0f), UDim(0.45f, 0.0f)));
	// set size to be half the size of the parent
	//quitBtn->setSize(USize(UDim(0.1f, 0.0f), UDim(0.1f, 0.0f)));
	//myRoot->addChild(quitBtn);
	return E_NOTIMPL;
}
bool SnakeGameMenuUI::onMouseButtonDown(const EventArgs & e)
{
	const MouseEventArgs & eMouse = static_cast<const MouseEventArgs &>(e);
	Window* window = eMouse.window;
	game->InputHandle(StringUtil::ConvertLPSTRToLPWSTR(window->getName().c_str()), StringUtil::ConvertLPSTRToLPWSTR(PushButton::EventMouseButtonDown.c_str()), eMouse, window);
	//((TestManger *)game)->state = new Vibratiom();

	return true;
}

HRESULT SnakeGameMenuUI::Relese()
{
	return E_NOTIMPL;
}

HRESULT SnakeGameMenuUI::Render()
{
	return E_NOTIMPL;
}
