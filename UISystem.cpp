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
	rp->setResourceGroupDirectory("animations", "F:/ConsoleApplication2/x64/Debug/datafiles/animations");
//	CEGUI::ImageCodec::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::AnimationManager::setDefaultResourceGroup("animations");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::WidgetLookManager::getSingleton().parseLookNFeelSpecificationFromFile("AlfiskoSkin.looknfeel");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(&CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei33", 32, true, "simhei.ttf"));
	//CEGUI::FontManager::getSingleton().createFromFile("simhei32.font");	
	CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei30", 20, true, "simhei.ttf");
	//CEGUI::SchemeManager::getSingleton().createAll("*.scheme", "schemes");
	//CEGUI::SchemeManager::getSingleton().createAll("*.font", "fonts");
	/*
	CEGUI::WidgetLookManager::getSingleton().parseLookNFeelSpecificationFromFile("AlfiskoSkin.looknfeel");

	//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(&CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei33", 32, true, "simhei.ttf"));
	//CEGUI::FontManager::getSingleton().createFromFile("simhei32.font");

	//CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei30", 5, true, "simhei.ttf");
	//CEGUI::Font &defaultFont = CEGUI::FontManager::getSingleton().createFreeTypeFont("simhei33",12,true,"simhei.ttf");
	CEGUI::FontManager& ma = CEGUI::FontManager::getSingleton();
	Window* myRoot = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	System::getSingleton().createGUIContext(myRenderer->getDefaultRenderTarget());
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	FrameWindow* fWnd = (FrameWindow*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/FrameWindow","testWindow");
	fWnd->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(USize(UDim(0.5f, 0.0f), UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
	//myRoot->addChild(fWnd);
	//CEGUI::String fontSizeString = "12";
	//float fontSize = CEGUI::PropertyHelper<float>::fromString(fontSizeString);
	//if (fontSize != 0.0f)
	//defaultFont.setProperty<float>("PointSize", fontSize);
	CEGUI::DefaultWindow* quitBtn = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Label", (CEGUI::utf8*)"Quit");
	//quitBtn->setFont(&defaultFont);
	quitBtn->setText((CEGUI::utf8*)StringUtil::ConvertLPWSTRToLPSTR(L"贪吃蛇"));
	//((CEGUI::Font*)quitBtn->getFont())->setProperty<float>("PointSize", 12.0f);
	quitBtn->setPosition(UVector2(UDim(0.45f, 0.0f), UDim(0.45f, 0.0f)));
	// set size to be half the size of the parent
	quitBtn->setSize(USize(UDim(0.1f, 0.0f), UDim(0.1f, 0.0f)));
	myRoot->addChild(quitBtn);
	*/
	return S_OK;
}

HRESULT UISystem::Relese()
{
	CEGUI::Direct3D9Renderer::destroy(*myRenderer);
	return S_OK;
}

bool UISystem::get(const EventArgs& args)
{
	return E_NOTIMPL;
}


HRESULT UISystem::Update(float delta)
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
	return S_OK;
}

bool UISystem::getFocusedInputBoxCoord(POINT& point, float& height)
{
	//寻找到有输入焦点的EditBox的左上坐标
	//遍历所有窗口
	CEGUI::WindowManager::WindowIterator wit = CEGUI::WindowManager::getSingleton().getIterator();
	while (!wit.isAtEnd())
	{
		const CEGUI::Window* widget = (*wit)->getActiveChild();
		//如果是EditBox或者MultiLineEditBox
		if (widget)
		{
			CEGUI::String windowType = widget->getType();
			if (windowType =="AlfiskoSkin/Editbox")            //根据具体的scheme来修改。
			{
				float x=0;
				float y;
				CEGUI::Editbox * pEditbox = (CEGUI::Editbox*)(widget);

				CEGUI::String textBeforeCaret;
				if (pEditbox->isTextMasked())
					textBeforeCaret = CEGUI::String(pEditbox->getCaretIndex(), pEditbox->getMaskCodePoint());
				else
					textBeforeCaret = pEditbox->getTextVisual().substr(0, pEditbox->getCaretIndex());

				CEGUI::Rect<float> screenArea = CEGUI::CoordConverter::screenToWindow(*pEditbox->getParent(), pEditbox->getArea());
				/*
				x = screenArea.left();
				if (pEditbox->getFont()->getTextExtent(textBeforeCaret) <= pEditbox->getWidth().d_scale*SCREEN_HEIGHT) {
					x += pEditbox->getFont()->`	(textBeforeCaret);
				}
				else {
					x += pEditbox->getWidth().d_scale*SCREEN_HEIGHT;
				}
				x += -210;
				*/
				EditboxWindowRenderer* wr = (EditboxWindowRenderer*)pEditbox->getWindowRenderer(); //需修改CEGUI源码	
				y = screenArea.top();
				y += (screenArea.getHeight() - pEditbox->getFont()->getFontHeight()) / 2; //文字垂直居中显示
				point.x = x;
				point.y = y;
				return true;
			}
		}
		wit++;
	}

	return false;
}

bool UISystem::IMEFollow(HWND hWnd)
{
	//判断输入法是否打开
	if (!ImmIsIME(GetKeyboardLayout(0)))
		return false;

	//获得输入框左上坐标
	bool result;
	POINT point;
	float height;
	result = getFocusedInputBoxCoord(point, height);
	if (!result)
		return false;

	//获得客户区的坐标
	RECT rect;
	GetWindowRect(hWnd, &rect);
	point.x += rect.left;
	point.y += rect.top;

	//设置输入法位置
	HIMC hImc = ImmGetContext(hWnd);
	if (hImc == NULL) return false;
	COMPOSITIONFORM form;
	form.dwStyle = CFS_POINT;
	ImmGetCompositionWindow(hImc, &form);
	form.ptCurrentPos.x = point.x;
	form.ptCurrentPos.y = point.y;
	ImmSetCompositionWindow(hImc, &form);
	::ImmReleaseContext(hWnd, hImc);
	return true;
}