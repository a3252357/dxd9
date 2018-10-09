#pragma once
#include "Seting.h"
class Snake : BaseGame
{
private:
	shared_ptr<Sprites> spritesManager;
	shared_ptr<Sprite> g_pSnake[200];
	LPDIRECT3DTEXTURE9  	g_pTexture = NULL;
	LPDIRECT3DTEXTURE9  	g_pTexturewall;
	shared_ptr<Sprite>           g_pSprite1wall[200];
	int snakenum = 10;
	int snakeup = 0;
	int wallnum = 200;
	shared_ptr<SNAKE> last;
	shared_ptr<SNAKE> cur;
	shared_ptr<SNAKE> frist;
	shared_ptr<SNAKE> snake;
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
	int  currentTime = 0;//��ǰʱ��
	int  lastTime = 0;//����ʱ��
public:
	Snake();
	~Snake();
	HRESULT Update() override;
	HRESULT Render() override;
	HRESULT Init()	override;
};