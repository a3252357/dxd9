#include "VibrationUI.h"



VibrationUI::VibrationUI(BaseGame *_game)
{
	game = _game;
	Init();
}


VibrationUI::~VibrationUI()
{
}

HRESULT VibrationUI::Update()
{
	return E_NOTIMPL;
}

HRESULT VibrationUI::Init()
{
	//CEGUI::Font &defaultFont = CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei33",12,true,"simhei.ttf");
	CEGUI::FontManager& ma = CEGUI::FontManager::getSingleton();
	myRoot = (CEGUI::Window*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	System::getSingleton().createGUIContext(UISystem::myRenderer->getDefaultRenderTarget());
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	Editbox* fWnd = (Editbox*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Editbox", "testWindow");
	fWnd->subscribeEvent(PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&VibrationUI::onMouseButtonDown, this));
	fWnd->setPosition(UVector2(UDim(0.4f, 0.0f), UDim(0.4f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(USize(UDim(0.2f, 0.0f), UDim(0.2f, 0.0f)));
	fWnd->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"�yԇ"));
	myRoot->addChild(fWnd);

	PushButton* fWnd1 = (PushButton*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Button", "testWindow1");
	fWnd1->subscribeEvent(PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&VibrationUI::onMouseButtonDown, this));
	fWnd1->setPosition(UVector2(UDim(0.2f, 0.0f), UDim(0.2f, 0.0f)));
	// set size to be half the size of the parent
	fWnd1->setSize(USize(UDim(0.2f, 0.0f), UDim(0.2f, 0.0f)));
	fWnd1->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"�yԇ"));
	myRoot->addChild(fWnd1);
	//CEGUI::String fontSizeString = "12";
	//float fontSize = CEGUI::PropertyHelper<float>::fromString(fontSizeString);
	//if (fontSize != 0.0f)
	//defaultFont.setProperty<float>("PointSize", fontSize);
	//CEGUI::DefaultWindow* quitBtn = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Label", (CEGUI::utf8*)"Quit");
	//quitBtn->setFont(&defaultFont);
	//quitBtn->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"̰����"));
	//((CEGUI::Font*)quitBtn->getFont())->setProperty<float>("PointSize", 12.0f);
	//quitBtn->setPosition(UVector2(UDim(0.45f, 0.0f), UDim(0.45f, 0.0f)));
	// set size to be half the size of the parent
	//quitBtn->setSize(USize(UDim(0.1f, 0.0f), UDim(0.1f, 0.0f)));
	//myRoot->addChild(quitBtn);
	return E_NOTIMPL;
}
bool VibrationUI::onMouseButtonDown(const EventArgs & e)
{
	const MouseEventArgs & eMouse = static_cast<const MouseEventArgs &>(e);

	//((TestManger *)game)->state = new Vibratiom();

	return true;
}

HRESULT VibrationUI::Relese()
{
	return E_NOTIMPL;
}

HRESULT VibrationUI::Render()
{
	return E_NOTIMPL;
}
