#include "UISystem.h"
CEGUI::Direct3D9Renderer*  UISystem::myRenderer;
HRESULT UISystem::Init()
{
 myRenderer =
		&CEGUI::Direct3D9Renderer::create(D3DUtil::getD3DDev());
	CEGUI::System::create(*myRenderer);
	CEGUI::String d_usedFiles = CEGUI::String("F:/ConsoleApplication2/x64/Debug/datafiles/scheme");
	CEGUI::DefaultResourceProvider* rp =
		static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "F:/ConsoleApplication2/x64/Debug/datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets","F:/ConsoleApplication2/x64/Debug/datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "F:/ConsoleApplication2/x64/Debug/datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "F:/ConsoleApplication2/x64/Debug/datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels","F:/ConsoleApplication2/x64/Debug/datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts","F:/ConsoleApplication2/x64/Debug/datafiles/lua_scripts/");
//	CEGUI::ImageCodec::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::WidgetLookManager::getSingleton().parseLookNFeelSpecificationFromFile("TaharezLook.looknfeel");
	CEGUI::FontManager::getSingleton().createFromFile("Batang-18.font");
	Window* myRoot = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	System::getSingleton().createGUIContext(myRenderer->getDefaultRenderTarget());
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	FrameWindow* fWnd = (FrameWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow","testWindow");
	fWnd->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(USize(UDim(0.5f, 0.0f), UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
	myRoot->addChild(fWnd);
	CEGUI::PushButton* quitBtn = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", (CEGUI::utf8*)"Quit");
	quitBtn->setText((CEGUI::utf8*)"OK1");
	fWnd->addChild(quitBtn);
	return S_OK;
}

HRESULT UISystem::Relese()
{
	CEGUI::Direct3D9Renderer::destroy(*myRenderer);
	return S_OK;
}


HRESULT UISystem::Update(float delta)
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
	return S_OK;
}
