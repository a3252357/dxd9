#pragma once 
#include "Seting.h"
#include "D3DUtil.h"
#define INITGUID
static class InputInit {
	public:
		static LPDIRECTINPUT8 input8;
		static LPDIRECTINPUTDEVICE8   g_pMouseDevice;
		static LPDIRECTINPUTDEVICE8   g_pKeyboardDevice;
		static DIMOUSESTATE mousestate;
		static char g_KeyboardState[256];
		static char l_KeyboardState[256];
		static HRESULT InitInput(HINSTANCE hInstance);
		static HRESULT ReadKeyAndMouse();
		static BOOL Device_Read(IDirectInputDevice8*pDIDevice, void* pBuffer, long lSize);
};
