#ifndef SETING_H
#define SETING_H
#define SCREEN_WIDTH	1300						//Ϊ���ڿ�ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڿ��
#define SCREEN_HEIGHT	900							//Ϊ���ڸ߶ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڸ߶�
#define BOX_WIDTH	32						//ש����
#define WINDOW_TITLE	_T("huangjianjian�Ĳ��Դ���") //Ϊ���ڱ��ⶨ��ĺ�
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }      //�Զ���һ��SAFE_RELEASE()��,������Դ���ͷ�
using namespace std;
//*****************************************************************************************
// Desc: ͷ�ļ����岿��  
//*****************************************************************************************    
#include <d3d9.h>
#include <d3dx9.h>
#include <DInput.h>
#include <tchar.h>
#include "Box2D/Box2D.h"
#include <wchar.h>
#include <math.h>
#include <map>
#include <vector>
#include <list>
//#include <atlconv.h>
#include <string>
#include <cstring>
#include <fstream>
#include "D3DRect.h"
#include "SystemInit.h"
#include "TextureManager.h"
#include "InputInit.h"
#include "D3DXFile.h"
#include "Sprite.h"
#include "TerrainClass.h"
#include "CameraClass.h"
#include "D3DUtil.h"
#include "StringUtil.h"
#include "BaseGame.h"
//*****************************************************************************************
// Desc: ���ļ����岿��  
//***************************************************************************************** 
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib, "winmm.lib")
struct CUSTOMVERTEX1
{
	FLOAT _x, _y, _z;               // �����λ��  
	FLOAT _u, _v;                   // ��������  
	CUSTOMVERTEX1(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
		:_x(x), _y(y), _z(z), _u(u), _v(v) {}
};
struct SNAKE
{
	int snakeup;               // �����ķ���  
	int x=0; 
	int y=0;// ��������  
	SNAKE * next;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ |D3DFVF_TEX1)  
#endif