#include "Snake.h"


Snake::Snake()
{
}

Snake::~Snake()
{
}

HRESULT Snake::Update()
{
	spritesManager->Update();
	return S_OK;
}

HRESULT Snake::Render()
{
	spritesManager->Render();
	return S_OK;
}
void snakenext(shared_ptr<SnakeBody> sprite) {
	sprite->snakenext();
}

HRESULT Snake::Init()
{
	snakeBody = make_shared<SnakeBody>();
	spritesManager =make_shared<Sprites>();
	g_pTexturewall = *D3DUtil::getTexture(L"img\wall\brick.png");
	//设置材质  
	D3DMATERIAL9 mtrl;
	::ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.7f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	mtrl.Emissive = D3DXCOLOR(0.3f, 0.0f, 0.1f, 1.0f);
	int z = -1;
	int j = 0;
	D3DUtil::getD3DDev()->SetMaterial(&mtrl);
	for (int i = 0; i < wallnum;) {
		if (z+1 < SCREEN_WIDTH / BOX_WIDTH)
		{
			z++;
		}
		else {
			j++;z = 0;
		}
		if (z == 0 || j == 0 || (z + 1) >= SCREEN_WIDTH / BOX_WIDTH || (j + 1) >= SCREEN_HEIGHT / BOX_WIDTH)
		{
			shared_ptr<Sprite> wall = make_shared<Sprite>();
			wall->Sprite_Init(L"img/wall/brick.png", z*BOX_WIDTH, j * BOX_WIDTH, 0);
			spritesManager->AddSprite(wall);
			i++;
		}
	}
	for (int i = 0; i < snakenum; i++) {
		shared_ptr<Sprite> snake = make_shared<Sprite>();
		snake->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH*(5 - i), BOX_WIDTH * 5, 0);
		snakeBody->Add(snake);
	}
	spritesManager->AddSprite(snakeBody);
	shared_ptr<Timer> timer = make_shared<Timer>(1000);
	snakeBody->setCurMy();
	timer->cb_func = snakeBody->callback;
	TimeInit::time->add_timer(timer);
	// 创建并初始化地形  
	//g_pTerrain = new TerrainClass();
	//g_pTerrain->getTerrain(64*100, L"img/wall/brick.png");      //从文件加载高度图和纹理  
	//g_pTerrain->InitTerrain(64, 100, 10.0f, 1.0f);  //四个值分别是顶点行数，顶点列数，顶点间间距，缩放系数  
	//三步曲之一，开启Alpha融合  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//三步曲之二，设置融合因子  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//三步曲之三，设置融合运算方式  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //这句设置运算方式为D3DBLENDOP_ADD的代码Direct3D默认为我们写了，所以注释掉这句也没大碍 
	lastTime = timeGetTime()*0.01f; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
	return S_OK;
}