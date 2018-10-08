#ifndef SETING_H
#define SETING_H
#define SCREEN_WIDTH	1300						//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define SCREEN_HEIGHT	900							//为窗口高度定义的宏，以方便在此处修改窗口高度
#define BOX_WIDTH	32						//砖块宽度
#define WINDOW_TITLE	_T("huangjianjian的测试窗口") //为窗口标题定义的宏
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }      //自定义一个SAFE_RELEASE()宏,便于资源的释放
using namespace std;
//*****************************************************************************************
// Desc: 头文件定义部分  
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
// Desc: 库文件定义部分  
//***************************************************************************************** 
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib, "winmm.lib")
struct CUSTOMVERTEX1
{
	FLOAT _x, _y, _z;               // 顶点的位置  
	FLOAT _u, _v;                   // 纹理坐标  
	CUSTOMVERTEX1(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
		:_x(x), _y(y), _z(z), _u(u), _v(v) {}
};
struct SNAKE
{
	int snakeup;               // 操作的方向  
	int x=0; 
	int y=0;// 纹理坐标  
	SNAKE * next;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ |D3DFVF_TEX1)  
#endif