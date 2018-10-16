#include "SystemInit.h"
HWND SystemInit::hwnd;
IDirect3DDevice9 * SystemInit::d3d9dev;
HRESULT SystemInit::init_D3D()
{
	D3DRect *d3d=new D3DRect();
	HRESULT hr=d3d->initD3D(hwnd);
	if (FAILED(hr)) {
		return hr;
	}
	else {
		d3d9dev = d3d->device;
	}
}

HRESULT SystemInit::init_Sys(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd,WNDPROC WndProc)
{
	//��ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };				//��WINDCLASSEX������һ�������࣬����wndClassʵ������WINDCLASSEX������֮�󴰿ڵĸ����ʼ��    
	wndClass.cbSize = sizeof(WNDCLASSEX);	//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;				//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;				//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon = (HICON)::LoadImage(NULL, _T("icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); //��ȫ�ֵ�::LoadImage�����ӱ��ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //ΪhbrBackground��Աָ��һ����ɫ��ˢ���
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = _T("ForTheDreamOfGameDevelop");		//��һ���Կ���ֹ���ַ�����ָ������������֡�

	if (!RegisterClassEx(&wndClass))				//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
		return -1;

	hwnd = CreateWindow(_T("ForTheDreamOfGameDevelop"), WINDOW_TITLE,			//ϲ���ּ��Ĵ������ں���CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH,
		SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	init_D3D();
	Light_Set(1);
	Matrix_Set();
	InputInit::InitInput(hInstance);
	GameSystem::Init();
	return S_OK;
}

VOID SystemInit::Light_Set(UINT nType)
{
	static D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	switch (nType)
	{
	case 1:     //���Դ  
		light.Type = D3DLIGHT_POINT;
		light.Ambient = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		light.Range = 300.0f;
		break;
	case 2:     //ƽ�й�  
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	case 3:     //�۹��  
		light.Type = D3DLIGHT_SPOT;
		light.Position = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
		light.Direction = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		light.Range = 300.0f;
		light.Falloff = 0.1f;
		light.Phi = D3DX_PI / 3.0f;
		light.Theta = D3DX_PI / 6.0f;
		break;
	}

	d3d9dev->SetLight(0, &light); //���ù�Դ  
	d3d9dev->LightEnable(0, true);//���ù���  
	d3d9dev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(36, 36, 36));   //����һ�»�����  
	return VOID();
}

VOID SystemInit::Matrix_Set()
{
	//--------------------------------------------------------------------------------------
	//���Ĵ�任֮һ��������任���������
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matWorld, Rx, Ry, Rz;
	D3DXMatrixIdentity(&matWorld);                  // ��λ���������  
	D3DXMatrixRotationX(&Rx, D3DX_PI *(::timeGetTime() / 1000.0f));    // ��X����ת  
	D3DXMatrixRotationY(&Ry, D3DX_PI *(::timeGetTime() / 1000.0f / 2));    // ��Y����ת  
	D3DXMatrixRotationZ(&Rz, D3DX_PI *(::timeGetTime() / 1000.0f / 3));   // ��Z����ת  
	matWorld = Rx * Ry * Rz * matWorld;             // �õ����յ���Ͼ���  
	d3d9dev->SetTransform(D3DTS_WORLD, &matWorld);  //��������任����  

	//--------------------------------------------------------------------------------------
	//���Ĵ�任֮������ȡ���任���������
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matView; //����һ������
	D3DXVECTOR3 vEye(0.0f, 0.0f, -5.0f);  //�������λ��
	D3DXVECTOR3 vAt(0.0f, 0.0f, 0.0f); //�۲���λ��
	D3DXVECTOR3 vUp(0.0f, 0.0f, 5.0f);//���ϵ�����
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp); //�����ȡ���任����
	d3d9dev->SetTransform(D3DTS_VIEW, &matView); //Ӧ��ȡ���任����

													  //--------------------------------------------------------------------------------------
													  //���Ĵ�任֮������ͶӰ�任���������
													  //--------------------------------------------------------------------------------------
	D3DXMATRIX matProj; //����һ������
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, SCREEN_WIDTH/ SCREEN_HEIGHT, 1.0f, 1000.0f); //����ͶӰ�任����
	d3d9dev->SetTransform(D3DTS_PROJECTION, &matProj);  //����ͶӰ�任����

															 //--------------------------------------------------------------------------------------
															 //���Ĵ�任֮�ġ����ӿڱ任������
															 //--------------------------------------------------------------------------------------
	D3DVIEWPORT9 vp; //ʵ����һ��D3DVIEWPORT9�ṹ�壬Ȼ��������������������ֵ�Ϳ�����
	vp.X = 0;		//��ʾ�ӿ�����ڴ��ڵ�X����
	vp.Y = 0;		//�ӿ���ԶԴ��ڵ�Y����
	vp.Width = SCREEN_WIDTH;	//�ӿڵĿ��
	vp.Height = SCREEN_HEIGHT; //�ӿڵĸ߶�
	vp.MinZ = 0.0f; //�ӿ�����Ȼ����е���С���ֵ
	vp.MaxZ = 1.0f;	//�ӿ�����Ȼ����е�������ֵ
	d3d9dev->SetViewport(&vp); //�ӿڵ�����

}