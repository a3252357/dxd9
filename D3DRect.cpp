#include "D3DRect.h"
D3DRect *D3DRect::getInstance(){
	return instance;
}
HRESULT D3DRect::initD3D(HWND hwnd){
	if(NULL==(D3DDirect = Direct3DCreate9(D3D_SDK_VERSION)))return -1;
	D3DCAPS9 caps;
	if (FAILED(D3DDirect->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))return -2;
	int vp = 0;
	if (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	d3dppInit(hwnd);
	if (FAILED(D3DDirect->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,hwnd, vp, &d3dpp, &device)))return -3;
	return 1;
	
}
D3DRect::D3DRect()
{
}
void D3DRect::d3dppInit(HWND hwnd)
{
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0; 
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
D3DRect::~D3DRect()
{
}