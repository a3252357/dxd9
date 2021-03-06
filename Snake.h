#pragma once
#include "Seting.h"
#include "MapLoader.h"
#include "CallBackTimer.h"
#include "BaseGame.h"
#include "SnakeBody.h"
#include "Sprites.h"
#include "spine-sfml.h"
#include "SnakeGameMenuUI.h"
#include "PlayerLoader.h"
#include "CreateBody.h"
using namespace spine;

class Snake :public BaseGame
{
private:
	MapLoader * maps;
	shared_ptr<Sprites> spritesManager;
	shared_ptr<SnakeBody> snakeBody;
	//shared_ptr<Sprite> g_pSnake[200];
	Texture2d * 	g_pTexture = NULL;
	Texture2d *   	g_pTexturewall;
	SkeletonDrawable * a;
	PlayerLoader* asda;
	//shared_ptr<Sprite>           g_pSprite1wall[100];
	//shared_ptr<TimeWithSprite> timer;
	int snakenum = 10;
	int snakeup = 0;
	int wallnum = 200;

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
	int  currentTime = 0;//当前时间
	int  lastTime = 0;//持续时间
public:
	
	Snake();
	~Snake();
//	HRESULT Update() override;
//	HRESULT Render() override;
	HRESULT Init()	override;
};
void snakenext(shared_ptr<SnakeBody> sprite);