#pragma once
#include "Seting.h"
#include "CEGUI/Base.h"
#include "CEGUI/System.h"
#include "CEGUI/RendererModules/Direct3D9/ViewportTarget.h"
#include "CEGUI/CEGUI.h"
class MapLoader;
using namespace CEGUI;
static class UISystem
{
public:
	static CEGUI::Direct3D9Renderer* myRenderer;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
};
 
