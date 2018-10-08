#ifndef D3DINIT_H
#define D3DINIT_H
#include "Seting.h"
class D3DRect {
public:
	IDirect3DDevice9* device;
	IDirect3D9 * D3DDirect;
	D3DPRESENT_PARAMETERS d3dpp;	
	D3DRect* getInstance();
	HRESULT  initD3D(HWND hwnd);
	D3DRect();  // ���ǹ��캯��
private:
	void d3dppInit(HWND hwnd);
	D3DRect * instance;
	~D3DRect();

};
#endif
