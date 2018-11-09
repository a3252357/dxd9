#pragma once
#include "Seting.h"
#include "MapLoader.h"
#include "D3Dutil.h"
using namespace CEGUI;
static class UISystem
{
public:
	static CEGUI::Direct3D9Renderer* myRenderer;
	static HRESULT Update(float delta);
	static HRESULT Init();
	static HRESULT Relese();
};
 
