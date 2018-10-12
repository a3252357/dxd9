
//*****************************************************************************************
//
//【Visual C++】游戏开发笔记系列配套源码 三十四 浅墨DirectX提高班之三 起承转合的艺术：Direct3D渲染五步曲
//		 VS2010版
// 2012年 11月25日  Create by 浅墨 
//图标素材： 古剑奇谭 红玉
//此刻心情：多年以后，当你回忆往昔，唯一让你觉得真实，和骄傲的，是你现在昂首挺胸、用力走过的人生。
//
//***************************************************************************************** 



//*****************************************************************************************
// Desc: 头文件定义部分  
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
// Desc: 全局变量声明部分  
//*****************************************************************************************
int    frameCount = -1;//帧数
float  fps = 0; //我们需要计算的FPS值
int  currentTime = 0;//当前时间
int  lastTime = 0;//持续时间
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; //Direct3D设备对象
ID3DXFont*				g_pFont = NULL;    //字体COM接口
float					g_FPS = 0.0f;       //一个浮点型的变量，代表帧速率
wchar_t					g_strFPS[50];    //包含帧速率的字符数组
RECT					g_FontPosition = { 0, 0, 0, 0 };//定义一个矩形，用于字体位置的设定
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
LPD3DXMESH g_teapot = NULL;     //茶壶对象  //在窗口右上角处，显示每秒帧数
XFile xfile = XFile();
TerrainClass*                               g_pTerrain;      //地形类的指针实例  
b2MouseJoint* mouse;												//*****************************************************************************************
																	// Desc: 全局函数声明部分 
																	//***************************************************************************************** 
LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT				Direct3D_Init(HWND hwnd);
HRESULT				Objects_Init();
void				Direct3D_Render(HWND hwnd);
void				Direct3D_CleanUp();
float				Get_FPS();
//*****************************************************************************************
// Name: WinMain( )
// Desc: Windows应用程序入口函数
//*****************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TimeInit::Time_Init();
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	SystemInit::init_Sys(hInstance, hPrevInstance, lpCmdLine, nShowCmd, WndProc);

	if (!(S_OK == Objects_Init())) return E_FAIL;
	MoveWindow(D3DUtil::getHWND(), 200, 50, SCREEN_WIDTH, SCREEN_HEIGHT, true);   //调整窗口显示时的位置，窗口左上角位于屏幕坐标（200，50）处
	ShowWindow(D3DUtil::getHWND(), nShowCmd);    //调用Win32函数ShowWindow来显示窗口
	UpdateWindow(D3DUtil::getHWND());  //对窗口进行更新，就像我们买了新房子要装修一样
	UnregisterClass(_T("ForTheDreamOfGameDevelop"), hInstance);
	MSG msg = { 0 };  //初始化msg
	while (msg.message != WM_QUIT)			//使用while循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);		//该函数分发一个消息给窗口程序。
		}
		else
		{
			Direct3D_Render(D3DUtil::getHWND());			//调用渲染函数，进行画面的渲染
		}
	}
	return 0;
}

//*****************************************************************************************
// Name: WndProc()
// Desc: 对窗口消息进行处理
//*****************************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //窗口过程函数WndProc
{

	switch (message)				//switch语句开始
	{
	case WM_PAINT:					 // 客户区重绘消息
		Direct3D_Render(hwnd);          //调用Direct3D_Render函数，进行画面的绘制
		ValidateRect(hwnd, NULL);   // 更新客户区的显示
		break;									//跳出该switch语句
	case WM_DESTROY:				//窗口销毁消息
		Direct3D_CleanUp();     //调用Direct3D_CleanUp函数，清理COM接口对象
		PostQuitMessage(0);		//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;						//跳出该switch语句

	default:						//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程来为应用程序没有处理的窗口消息提供缺省的处理。
	}


	return 0;					//正常退出
}
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;    //顶点缓冲区对象  
												   //--------------------------------------------------------------------------------------  
												   // Name: Light_Set()  
												   // Desc: 设置光源类型  
												   //--------------------------------------------------------------------------------------  
LPDIRECT3DTEXTURE9      g_pTexture1 = NULL;   // 纹理接口对象  
shared_ptr<TimeS> time3=make_shared<TimeS>();
void func(shared_ptr<TimerData> timedate) {
	//AllocConsole();//打开控制台窗口
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
	//创建字体
	if (FAILED(D3DXCreateFont(D3DUtil::getD3DDev(), 30, 0, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("宋体"), &g_pFont)))
		return E_FAIL;
	//g_pTexture1 = *TextureManager::getTexture(L"D://Chrysanthemum.jpg");
	if (FAILED(D3DXCreateTeapot(D3DUtil::getD3DDev(), &g_teapot, NULL))) //茶壶的创建  
	{
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//printf("fasfa");
	}
	//初始化字体位置
	g_FontPosition.top = 0;
	g_FontPosition.left = 0;
	g_FontPosition.right = SCREEN_WIDTH;
	g_FontPosition.bottom = SCREEN_HEIGHT;
	xfile.XFile_Init(L"F:/max/max.x");
	meshBox = xfile.m_Mesh;
	//设置材质  
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
	// 创建并初始化地形  
	//g_pTerrain = new TerrainClass();
	//g_pTerrain->getTerrain(64*100, L"img/wall/brick.png");      //从文件加载高度图和纹理  
	//g_pTerrain->InitTerrain(64, 100, 10.0f, 1.0f);  //四个值分别是顶点行数，顶点列数，顶点间间距，缩放系数  
	// 三步曲之一，开启Alpha融合  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//三步曲之二，设置融合因子  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//三步曲之三，设置融合运算方式  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //这句设置运算方式为D3DBLENDOP_ADD的代码Direct3D默认为我们写了，所以注释掉这句也没大碍 

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	lastTime = timeGetTime()*0.01f; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
	return S_OK;
}




//*****************************************************************************************
// Name: Direct3D_Render()
// Desc: 进行图形的渲染操作
// Point:【Direct3D渲染五步曲】
//		1.渲染五步曲之一，清屏操作
//		2.渲染五步曲之二，开始绘制
//		3.渲染五步曲之三，正式绘制
//		4.渲染五步曲之四，结束绘制
//		5.渲染五步曲之五，翻转显示
//*****************************************************************************************
//*****************************************************************************************
// Name: Direct3D_Render()
// Desc: 使用Direct3D进行渲染
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
	// 【Direct3D渲染五步曲之一】：清屏操作
	//--------------------------------------------------------------------------------------
	D3DUtil::getD3DDev()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//定义一个矩形，用于获取主窗口矩形
	RECT formatRect;
	GetClientRect(hwnd, &formatRect);
	// 创建并初始化虚拟摄像机  
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
	currentTime = timeGetTime()*0.01f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间
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
		lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
	}
	for (int j = 0; j < snakenum; j++) {
		g_pSnake[j]->Update();
		g_pSnake[j]->Render();
	}
	*/
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之二】：开始绘制
	//--------------------------------------------------------------------------------------
	snake->Update();
	D3DUtil::getD3DDev()->BeginScene();
	snake->Render();
	InputInit::ReadKeyAndMouse();
	// 获取键盘消息并给予设置相应的填充模式  
	if (InputInit::g_KeyboardState[DIK_1] & 0x8000f)         // 若数字键1被按下，进行线框填充  
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if (InputInit::g_KeyboardState[DIK_2] & 0x8000f)         // 若数字键2被按下，进行实体填充  
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// 开始绘制
	// 沿摄像机各分量移动视角  
	if (InputInit::g_KeyboardState[DIK_A] & 0x8000f) {
		g_pCamera->MoveAlongRightVec(-0.03f);
	}
	if (InputInit::g_KeyboardState[DIK_D] & 0x8000f)  g_pCamera->MoveAlongRightVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_W] & 0x8000f) g_pCamera->MoveAlongLookVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_S] & 0x8000f)  g_pCamera->MoveAlongLookVec(-0.03f);
	if (InputInit::g_KeyboardState[DIK_I] & 0x8000f)  g_pCamera->MoveAlongUpVec(0.03f);
	if (InputInit::g_KeyboardState[DIK_K] & 0x8000f)  g_pCamera->MoveAlongUpVec(-0.03f);

	//沿摄像机各分量旋转视角  
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
	//计算并设置取景变换矩阵  
	D3DXMATRIX matView;
	g_pCamera->CalculateViewMatrix(&matView);
	D3DUtil::getD3DDev()->SetTransform(D3DTS_VIEW, &matView);
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之三】：正式绘制，在这里我们写了四段文字
	//--------------------------------------------------------------------------------------
	//在纵坐标100处，写第一段文字


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
	//绘制地形  
	//D3DXMatrixTranslation(&g_WorldMatrix[1], 1.0f, 0.0f, 1.0f);
	//g_pTerrain->RenderTerrain(&g_WorldMatrix[1], true);  //渲染地形，且第二个参数设为false，表示不渲染出地形的线框 
	D3DUtil::getD3DDev()->EndScene();
	//设置自定义的FVF
	// 结束绘制
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之五】：显示翻转
	//--------------------------------------------------------------------------------------
	D3DUtil::getD3DDev()->Present(NULL, NULL, NULL, NULL);  // 翻转与显示													
}


//*****************************************************************************************
// Name：Get_FPS（）函数
// Desc: 用于计算帧速率
//*****************************************************************************************
float Get_FPS()
{

	//定义四个静态变量
	lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
	frameCount++;//每调用一次Get_FPS()函数，帧数自增1
	currentTime = timeGetTime()*0.001f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

									   //如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
	if (currentTime - lastTime > 1.0f) //将时间控制在1秒钟
	{
		fps = (float)frameCount / (currentTime - lastTime);//计算这1秒钟的FPS值
		lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
		frameCount = 0;//将本次帧数frameCount值清零
	}




	// This is our little game loop.
	/*

	for (int32 i = 0; i < 1; ++i)
	{
	//设置力的循序渐进
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
// Desc: 对Direct3D的资源进行清理，释放COM接口对象
//*****************************************************************************************
void Direct3D_CleanUp()
{
	//释放COM接口对象
	SAFE_RELEASE(g_pFont)
		SAFE_RELEASE(g_pd3dDevice)
}


