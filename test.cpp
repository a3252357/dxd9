
//*****************************************************************************************
//
//��Visual C++����Ϸ�����ʼ�ϵ������Դ�� ��ʮ�� ǳīDirectX��߰�֮�� ���ת�ϵ�������Direct3D��Ⱦ�岽��
//		 VS2010��
// 2012�� 11��25��  Create by ǳī 
//ͼ���زģ� �Ž���̷ ����
//�˿����飺�����Ժ󣬵������������Ψһ���������ʵ���ͽ����ģ��������ڰ���ͦ�ء������߹���������
//
//***************************************************************************************** 



//*****************************************************************************************
// Desc: ͷ�ļ����岿��  
//*****************************************************************************************                                                                                       
#include "Seting.h"
#include "TimeInit.h"
#define dDOUBLE

extern long g_lMouseMoveX, g_lMouseMoveY;
extern BOOL InitMouse();
extern void CaptureMouse();
extern BOOL IsLButtonPressed();
extern BOOL IsRButtonPressed();
extern BOOL IsMButtonPressed();
extern void ReleaseCOMObject();

//*****************************************************************************************
// Desc: ȫ�ֱ�����������  
//*****************************************************************************************
int    frameCount = -1;//֡��
float  fps = 0; //������Ҫ�����FPSֵ
int  currentTime = 0;//��ǰʱ��
int  lastTime = 0;//����ʱ��
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; //Direct3D�豸����
ID3DXFont*				g_pFont = NULL;    //����COM�ӿ�
float					g_FPS = 0.0f;       //һ�������͵ı���������֡����
wchar_t					g_strFPS[50];    //����֡���ʵ��ַ�����
RECT					g_FontPosition = { 0, 0, 0, 0 };//����һ�����Σ���������λ�õ��趨
b2World * mWorld;
//ID3DXSprite*            g_pSprite = NULL;
//ID3DXSprite*            g_pSpriteBoss = NULL;
//ID3DXSprite*            g_pSpritePlayer = NULL;
//ID3DXSprite*            g_pSprite1[100];
//LPDIRECT3DTEXTURE9  	g_pTexture = NULL;
LPDIRECT3DTEXTURE9  	g_pTexturewall;
//LPDIRECT3DTEXTURE9  	g_pTextureBoss;
//LPDIRECT3DTEXTURE9  	g_pTexturePlayer;
ID3DXMesh* meshBox;
shared_ptr<SNAKE>last;
shared_ptr<SNAKE>cur;
shared_ptr<SNAKE>frist;
CameraClass*                            g_pCamera = NULL;
int xp = 0;
int yp = 0;
int wallnum = 200;
int snakenum = 10;
int snakeup = 0;
int x = 0;
int x1[100];
int y2[100];
int y = 0;
int wall[10][10] =
{
	{ 1,1,1,1,1,1,1,1,1,1 },
{ 1,2,2,2,3,4,3,0,0,1 },
{ 1,0,0,0,3,3,3,1,0,1 },
{ 1,0,0,0,2,0,0,1,0,1 },
{ 1,0,0,0,0,0,0,1,0,1 },
{ 1,0,0,0,0,0,0,1,0,1 },
{ 1,0,0,1,0,1,1,1,0,1 },
{ 1,0,0,1,0,0,0,1,0,1 },
{ 1,0,0,1,0,0,5,0,0,1 },
{ 1,1,1,1,1,1,1,1,1,1 },
};

// Define the gravity vector.
b2Vec2 gravity(0.0f, 1.0f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World world(gravity);
b2BodyDef bodyDef;
b2Body* body;
b2Body* body1[20];
b2Body* body2[100];
b2Body* bodyC[100];
float32 angelsC[100];
ID3DXSprite*            g_pSprite1C[100];
b2Body* bodyBoss;
b2Body* bodyPlayer;
int bodynum = 0;
float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;
b2Vec2 force = b2Vec2();
float32 angels = 0.0f;
float32 angels1[100];
RECT rect = RECT();
D3DXVECTOR3 vec = D3DXVECTOR3();
shared_ptr<TimeWheel> time1;
shared_ptr<Timer> timer;
D3DXMATRIX dd16;
D3DXMATRIX T1, T2, TInv;
LPD3DXMESH g_teapot = NULL;     //�������  //�ڴ������ϽǴ�����ʾÿ��֡��
XFile xfile = XFile();
TerrainClass*                               g_pTerrain;      //�������ָ��ʵ��  
b2MouseJoint* mouse;												//*****************************************************************************************
																	// Desc: ȫ�ֺ����������� 
																	//***************************************************************************************** 
LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT				Direct3D_Init(HWND hwnd);
HRESULT				Objects_Init();
void				Direct3D_Render(HWND hwnd);
void				Direct3D_CleanUp();
float				Get_FPS();
//*****************************************************************************************
// Name: WinMain( )
// Desc: WindowsӦ�ó�����ں���
//*****************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TimeInit::Time_Init();
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	SystemInit::init_Sys(hInstance, hPrevInstance, lpCmdLine, nShowCmd, WndProc);

	if (!(S_OK == Objects_Init())) return E_FAIL;
	MoveWindow(D3DUtil::getHWND(), 200, 50, SCREEN_WIDTH, SCREEN_HEIGHT, true);   //����������ʾʱ��λ�ã��������Ͻ�λ����Ļ���꣨200��50����
	ShowWindow(D3DUtil::getHWND(), nShowCmd);    //����Win32����ShowWindow����ʾ����
	UpdateWindow(D3DUtil::getHWND());  //�Դ��ڽ��и��£��������������·���Ҫװ��һ��
	UnregisterClass(_T("ForTheDreamOfGameDevelop"), hInstance);
	MSG msg = { 0 };  //��ʼ��msg
	while (msg.message != WM_QUIT)			//ʹ��whileѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);		//�ú����ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			Direct3D_Render(D3DUtil::getHWND());			//������Ⱦ���������л������Ⱦ
		}
	}
	return 0;
}

//*****************************************************************************************
// Name: WndProc()
// Desc: �Դ�����Ϣ���д���
//*****************************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //���ڹ��̺���WndProc
{

	switch (message)				//switch��俪ʼ
	{
	case WM_PAINT:					 // �ͻ����ػ���Ϣ
		Direct3D_Render(hwnd);          //����Direct3D_Render���������л���Ļ���
		ValidateRect(hwnd, NULL);   // ���¿ͻ�������ʾ
		break;									//������switch���
	case WM_DESTROY:				//����������Ϣ
		Direct3D_CleanUp();     //����Direct3D_CleanUp����������COM�ӿڶ���
		PostQuitMessage(0);		//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;						//������switch���

	default:						//������case�����������ϣ���ִ�и�default���
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д���Ĵ�����Ϣ�ṩȱʡ�Ĵ���
	}


	return 0;					//�����˳�
}
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;    //���㻺��������  
												   //--------------------------------------------------------------------------------------  
												   // Name: Light_Set()  
												   // Desc: ���ù�Դ����  
												   //--------------------------------------------------------------------------------------  
LPDIRECT3DTEXTURE9      g_pTexture1 = NULL;   // ����ӿڶ���  
shared_ptr<TimeS> time3=make_shared<TimeS>();
void func(shared_ptr<TimerData> timedate) {
	//AllocConsole();//�򿪿���̨����
	//freopen("CONOUT$", "w", stdout);
	//printf("%s", time3->time);
	//cout << "This is a test info" << std::endl;
}
shared_ptr<Snake>snake;
HRESULT Objects_Init()
{
	//time1 = make_shared<time_wheel>();
	//g_pTexturewall->Release();
	//timer= make_shared<Timer>(5000);
	//timer->cb_func = func;
	//time1->add_timer(timer);
	snake = make_shared<Snake>();
	snake->Init();
	//g_pTexturewall = *D3DUtil::getTexture(L"img\wall\brick.png");
	//world.SetAllowSleeping(true);
	//��������
	if (FAILED(D3DXCreateFont(D3DUtil::getD3DDev(), 30, 0, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("����"), &g_pFont)))
		return E_FAIL;
	//g_pTexture1 = *TextureManager::getTexture(L"D://Chrysanthemum.jpg");
	if (FAILED(D3DXCreateTeapot(D3DUtil::getD3DDev(), &g_teapot, NULL))) //����Ĵ���  
	{
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//printf("fasfa");
	}
	//��ʼ������λ��
	g_FontPosition.top = 0;
	g_FontPosition.left = 0;
	g_FontPosition.right = SCREEN_WIDTH;
	g_FontPosition.bottom = SCREEN_HEIGHT;
	xfile.XFile_Init(L"F:/max/max.x");
	meshBox = xfile.m_Mesh;
	//���ò���  
	D3DMATERIAL9 mtrl;
	::ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.7f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	mtrl.Emissive = D3DXCOLOR(0.3f, 0.0f, 0.1f, 1.0f);
	D3DUtil::getD3DDev()->SetMaterial(&mtrl);
	g_pCamera = new CameraClass(D3DUtil::getD3DDev());
	/*
	for (int i = 0; i < wallnum; i++) {
		g_pSprite1wall[i] = new Sprite();
		g_pSprite1wall[i]->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH, BOX_WIDTH, 0);
	}
	for (int i = 0; i < wallnum; i++) {
		g_pSnake[i] = new Sprite();
		g_pSnake[i]->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH*(5 - i), BOX_WIDTH * 5, 0);
	}
	*/
	// ��������ʼ������  
	//g_pTerrain = new TerrainClass();
	//g_pTerrain->getTerrain(64*100, L"img/wall/brick.png");      //���ļ����ظ߶�ͼ������  
	//g_pTerrain->InitTerrain(64, 100, 10.0f, 1.0f);  //�ĸ�ֵ�ֱ��Ƕ�������������������������࣬����ϵ��  
	// ������֮һ������Alpha�ں�  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//������֮���������ں�����  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//������֮���������ں����㷽ʽ  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //����������㷽ʽΪD3DBLENDOP_ADD�Ĵ���Direct3DĬ��Ϊ����д�ˣ�����ע�͵����Ҳû�� 

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	lastTime = timeGetTime()*0.01f; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
	return S_OK;
}




//*****************************************************************************************
// Name: Direct3D_Render()
// Desc: ����ͼ�ε���Ⱦ����
// Point:��Direct3D��Ⱦ�岽����
//		1.��Ⱦ�岽��֮һ����������
//		2.��Ⱦ�岽��֮������ʼ����
//		3.��Ⱦ�岽��֮������ʽ����
//		4.��Ⱦ�岽��֮�ģ���������
//		5.��Ⱦ�岽��֮�壬��ת��ʾ
//*****************************************************************************************
//*****************************************************************************************
// Name: Direct3D_Render()
// Desc: ʹ��Direct3D������Ⱦ
//*****************************************************************************************
long long start = 0;
long  long start_1 = 0;
long long end1 = 0;
int z = 0;
void Direct3D_Render(HWND hwnd)
{
	if (start == 0) {
		time3->start();
		start = time3->getStart();
		start_1 = time3->getStart();
	}
	else {
		end1 = time3->getEnd();
		if (end1 - start_1 < 30) {
			if ((end1 - start_1) >= 20) {
				char s[40];
				//sprintf(s, "@%d@", end1 - start_1);
				//printf(s);
				TimeInit::time->tick();
				start_1 += 20;
			}
		}
		else {
			start_1 = time3->getStart();
		}
		long sd = end1 - start;
		char s[40];
		//sprintf(s, "@%d@", end1 - start);
		//printf(s);
		time3->start();
		start = time3->getStart();
	}

	D3DXMATRIX R;
	D3DXMATRIX g_WorldMatrix[4];
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮һ������������
	//--------------------------------------------------------------------------------------
	D3DUtil::getD3DDev()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//����һ�����Σ����ڻ�ȡ�����ھ���
	RECT formatRect;
	GetClientRect(hwnd, &formatRect);
	// ��������ʼ�����������  
	/*
	int z = 0;
	for (int i = 0; i < SCREEN_WIDTH / BOX_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / BOX_WIDTH; j++) {
			if (i == 0 || j == 0 || (i + 1) >= SCREEN_WIDTH / BOX_WIDTH || (j + 1) >= SCREEN_HEIGHT / BOX_WIDTH)
			{
				g_pSprite1wall[z]->Set_State(i*BOX_WIDTH, j*BOX_WIDTH, 0);
				g_pSprite1wall[z]->Update();
				g_pSprite1wall[z]->Render();
				z++;
			}
		}
	}
	currentTime = timeGetTime()*0.01f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��
	if (currentTime - lastTime >= 1) {
		for (int j = 0; j < snakenum; j++) {
			shared_ptr<SNAKE> list;
			if (j == 0) {
				snake = make_shared<SNAKE>();
				snake->snakeup = snakeup;
				if (snakeup == 0) {
					g_pSnake[j]->Set_State(g_pSnake[j]->m_x + 32, g_pSnake[j]->m_y, 0);
					snake->x = 32 * (currentTime - lastTime);
				}
				if (snakeup == 1) {
					g_pSnake[j]->Set_State(g_pSnake[j]->m_x, g_pSnake[j]->m_y - 32, 0);
					snake->y = -32 * (currentTime - lastTime);
				}
				if (snakeup == 2) {
					g_pSnake[j]->Set_State(g_pSnake[j]->m_x - 32, g_pSnake[j]->m_y, 0);
					snake->x = 32 * (currentTime - lastTime);
				}
				if (snakeup == 3) {
					g_pSnake[j]->Set_State(g_pSnake[j]->m_x, g_pSnake[j]->m_y + 32, 0);
					snake->y = 32 * (currentTime - lastTime);
				}
				//printf("%d", 32 * (currentTime - lastTime));
				if (last == NULL)
				{
					cur = snake;
					frist = snake;
					last = snake;
					//	g_pSnake[j]->Update();
					//	break;
				}
				else {
					snake->next = last;
					last = snake;
				}
				//	if (last->next != NULL)
				//		list = last->next;
			}
			else {

				g_pSnake[j]->Set_State(g_pSnake[j - 1]->n_x, g_pSnake[j - 1]->n_y, 0);

				//				if (list->next != NULL)
				//			list = list->next;
			}
		}
		lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
	}
	for (int j = 0; j < snakenum; j++) {
		g_pSnake[j]->Update();
		g_pSnake[j]->Render();
	}
	*/
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʼ����
	//--------------------------------------------------------------------------------------
	snake->Update();
	D3DUtil::getD3DDev()->BeginScene();
	snake->Render();
	InputInit::ReadKeyAndMouse();
	// ��ȡ������Ϣ������������Ӧ�����ģʽ  
	if (InputInit::g_KeyboardState[DIK_1] & 0x8000f)         // �����ּ�1�����£������߿����  
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if (InputInit::g_KeyboardState[DIK_2] & 0x8000f)         // �����ּ�2�����£�����ʵ�����  
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// ��ʼ����
	// ��������������ƶ��ӽ�  
	if (InputInit::g_KeyboardState[DIK_A] & 0x8000f) {
		g_pCamera->MoveAlongRightVec(-0.03f);
	}
	if (InputInit::g_KeyboardState[DIK_D] & 0x8000f)  g_pCamera->MoveAlongRightVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_W] & 0x8000f) g_pCamera->MoveAlongLookVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_S] & 0x8000f)  g_pCamera->MoveAlongLookVec(-0.03f);
	if (InputInit::g_KeyboardState[DIK_I] & 0x8000f)  g_pCamera->MoveAlongUpVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_K] & 0x8000f)  g_pCamera->MoveAlongUpVec(-0.03f);

	//���������������ת�ӽ�  
	if (InputInit::g_KeyboardState[DIK_LEFT] & 0x8000f) {
		g_pCamera->RotationUpVec(-0.003f); snakeup = 2;
	}
	if (InputInit::g_KeyboardState[DIK_RIGHT] & 0x8000f) { g_pCamera->RotationUpVec(0.003f); snakeup = 0; }
	if (InputInit::g_KeyboardState[DIK_UP] & 0x8000f) {
		g_pCamera->RotationRightVec(-0.003f); snakeup = 1;
	}
	if (InputInit::g_KeyboardState[DIK_DOWN] & 0x8000f) { g_pCamera->RotationRightVec(0.003f); snakeup = 3; }
	if (InputInit::g_KeyboardState[DIK_J] & 0x8000f) g_pCamera->RotationLookVec(-0.001f);
	if (InputInit::g_KeyboardState[DIK_L] & 0x8000f) g_pCamera->RotationLookVec(0.001f);
	//���㲢����ȡ���任����  
	D3DXMATRIX matView;
	g_pCamera->CalculateViewMatrix(&matView);
	D3DUtil::getD3DDev()->SetTransform(D3DTS_VIEW, &matView);
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʽ���ƣ�����������д���Ķ�����
	//--------------------------------------------------------------------------------------
	//��������100����д��һ������


	//D3DXMatrixRotationY(&R, ::timeGetTime() / 720.0f);
	//D3DXMatrixTranslation(&g_WorldMatrix[0], 0.0f, 0.0f, 0.0f);
	//g_WorldMatrix[0] = g_WorldMatrix[0];
	//D3DUtil::getD3DDev()->SetTransform(D3DTS_WORLD, &g_WorldMatrix[0]);
	D3DUtil::getD3DDev()->SetTexture(0, g_pTexture1);
	//meshBox->DrawSubset(0);
	//meshBox->DrawSubset(1);
	//meshBox->DrawSubset(2);
	//meshBox->DrawSubset(3);
	//meshBox->DrawSubset(4);
	//xfile.Update();
	//xfile.Render();
	//���Ƶ���  
	//D3DXMatrixTranslation(&g_WorldMatrix[1], 1.0f, 0.0f, 1.0f);
	//g_pTerrain->RenderTerrain(&g_WorldMatrix[1], true);  //��Ⱦ���Σ��ҵڶ���������Ϊfalse����ʾ����Ⱦ�����ε��߿� 
	D3DUtil::getD3DDev()->EndScene();
	//�����Զ����FVF
	// ��������
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮�塿����ʾ��ת
	//--------------------------------------------------------------------------------------
	D3DUtil::getD3DDev()->Present(NULL, NULL, NULL, NULL);  // ��ת����ʾ													
}


//*****************************************************************************************
// Name��Get_FPS��������
// Desc: ���ڼ���֡����
//*****************************************************************************************
float Get_FPS()
{

	//�����ĸ���̬����
	lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
	frameCount++;//ÿ����һ��Get_FPS()������֡������1
	currentTime = timeGetTime()*0.001f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��

									   //�����ǰʱ���ȥ����ʱ�������1���ӣ��ͽ���һ��FPS�ļ���ͳ���ʱ��ĸ��£�����֡��ֵ����
	if (currentTime - lastTime > 1.0f) //��ʱ�������1����
	{
		fps = (float)frameCount / (currentTime - lastTime);//������1���ӵ�FPSֵ
		lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
		frameCount = 0;//������֡��frameCountֵ����
	}




	// This is our little game loop.
	/*

	for (int32 i = 0; i < 1; ++i)
	{
	//��������ѭ�򽥽�
	//	bodyPlayer->SetLinearVelocity(force);
	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world.Step(timeStep, velocityIterations, positionIterations);
	for (int i = 0; i < (sizeof(body1) / sizeof(body1[0])); i++) {
	x1[i]=body1[i]->GetPosition().x;
	y2[i] = body1[i]->GetPosition().y;
	angels1[i]= body1[i]->GetAngle();
	}

	// Now print the position and angle of the body.
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	//xp = bodyPlayer->GetPosition().x;
	//yp = bodyPlayer->GetPosition().y;
	x = position.x;
	y = position.y;
	angels = angle;
	//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);


	//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	*/

	return fps;
}


//*****************************************************************************************
// Name: Direct3D_CleanUp()
// Desc: ��Direct3D����Դ���������ͷ�COM�ӿڶ���
//*****************************************************************************************
void Direct3D_CleanUp()
{
	//�ͷ�COM�ӿڶ���
	SAFE_RELEASE(g_pFont)
		SAFE_RELEASE(g_pd3dDevice)
}


