#include "InputInit.h"
LPDIRECTINPUT8 InputInit::input8;
LPDIRECTINPUTDEVICE8   InputInit::g_pMouseDevice;
LPDIRECTINPUTDEVICE8   InputInit::g_pKeyboardDevice;
DIMOUSESTATE InputInit::mousestate;
char InputInit::g_KeyboardState[256];
char InputInit::l_KeyboardState[256];
HRESULT InputInit::InitInput(HINSTANCE hInstance)
{
	if (FAILED(DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (VOID **)&input8, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(input8->CreateDevice(GUID_SysMouse, &g_pMouseDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(input8->CreateDevice(GUID_SysKeyboard, &g_pKeyboardDevice, NULL)))
	{
		return E_FAIL;
	}
	g_pMouseDevice->SetDataFormat(&c_dfDIMouse);
	g_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	g_pMouseDevice->SetCooperativeLevel(D3DUtil::getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	g_pKeyboardDevice->SetCooperativeLevel(D3DUtil::getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	g_pMouseDevice->Acquire();
	g_pKeyboardDevice->Acquire();
		return S_OK;
}

HRESULT InputInit::ReadKeyAndMouse()
{
	
	::ZeroMemory(&mousestate, sizeof(mousestate));
	Device_Read(g_pMouseDevice, &mousestate, sizeof(mousestate));
	memcpy(l_KeyboardState, g_KeyboardState, sizeof(g_KeyboardState));
	::ZeroMemory(&g_KeyboardState, sizeof(g_KeyboardState));
	Device_Read(g_pKeyboardDevice, &g_KeyboardState, sizeof(g_KeyboardState));
	return E_NOTIMPL;
}
//*****************************************************************************************  
// Name: Device_Read();  
// Desc: 智能读取设备的输入数据  
//*****************************************************************************************  
BOOL InputInit::Device_Read(IDirectInputDevice8*pDIDevice, void* pBuffer, long lSize)
{
	HRESULT hr;
	while (true)
	{	
		pDIDevice->Poll();             // 轮询设备  
		pDIDevice->Acquire();          // 获取设备的控制权  
		if (SUCCEEDED(hr = pDIDevice->GetDeviceState(lSize, pBuffer))) break;
		if (hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED) return FALSE;
		if (FAILED(pDIDevice->Acquire())) return FALSE;
	}
	return TRUE;
}
