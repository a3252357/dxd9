#include "Snake.h"


Snake::Snake()
{
}

Snake::~Snake()
{
}

HRESULT Snake::Update()
{
	return S_OK;
}

HRESULT Snake::Render()
{
	int z = 0;
	for (int i = 0; i < SCREEN_WIDTH / BOX_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / BOX_WIDTH; j++) {
			if (i == 0 || j == 0 || (i + 1) >= SCREEN_WIDTH / BOX_WIDTH || (j + 1) >= SCREEN_HEIGHT / BOX_WIDTH)
			{
				g_pSprite1wall[z]->Set_State(i*BOX_WIDTH, j*BOX_WIDTH, 0);
				g_pSprite1wall[z]->Update();
				z++;
			}
		}
	}
	currentTime = timeGetTime()*0.01f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��
	printf("%d\n", currentTime);
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
				printf("%d", 32 * (currentTime - lastTime));
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
	}
	return S_OK;
}

HRESULT Snake::Init()
{
	spritesManager =make_shared<Sprites>();
	g_pTexturewall = *D3DUtil::getTexture(L"img\wall\brick.png");
	//���ò���  
	D3DMATERIAL9 mtrl;
	::ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.7f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	mtrl.Emissive = D3DXCOLOR(0.3f, 0.0f, 0.1f, 1.0f);
	D3DUtil::getD3DDev()->SetMaterial(&mtrl);
	for (int i = 0; i < wallnum; i++) {
		shared_ptr<Sprite> wall= make_shared<Sprite>();
		wall->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH, BOX_WIDTH, 0);
		spritesManager->AddSprite(wall);
	}
	for (int i = 0; i < wallnum; i++) {
		shared_ptr<Sprite> snake = make_shared<Sprite>();
		snake->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH*(5 - i), BOX_WIDTH * 5, 0);
		spritesManager->AddSprite(snake);
	}
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
