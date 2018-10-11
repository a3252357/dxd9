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
	//���ò���  
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
	// ��������ʼ������  
	//g_pTerrain = new TerrainClass();
	//g_pTerrain->getTerrain(64*100, L"img/wall/brick.png");      //���ļ����ظ߶�ͼ������  
	//g_pTerrain->InitTerrain(64, 100, 10.0f, 1.0f);  //�ĸ�ֵ�ֱ��Ƕ�������������������������࣬����ϵ��  
	//������֮һ������Alpha�ں�  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//������֮���������ں�����  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//������֮���������ں����㷽ʽ  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //����������㷽ʽΪD3DBLENDOP_ADD�Ĵ���Direct3DĬ��Ϊ����д�ˣ�����ע�͵����Ҳû�� 
	lastTime = timeGetTime()*0.01f; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
	return S_OK;
}