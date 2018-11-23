#pragma once 
#define SCREEN_WIDTH	1300						//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define SCREEN_HEIGHT	900							//为窗口高度定义的宏，以方便在此处修改窗口高度
#define BOX_WIDTH	(int)16						//砖块宽度
#define WINDOW_TITLE	_T("huangjianjian的测试窗口") //为窗口标题定义的宏
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }      //自定义一个SAFE_RELEASE()宏,便于资源的释放
#define PTM_RATIO 64
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ |D3DFVF_TEX1)  
#define MAX_OBSERVERS 100
#define GET_NAME(x) #x
using namespace std;
//*****************************************************************************************
// Desc: 头文件定义部分  
//***************************************************************************************** 
#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <d3dx9.h>
#include <DInput.h>
#include <iostream>
#include <tchar.h>
#include "Box2D/Box2D.h"
#include <wchar.h>
#include <math.h>
#include <map>
#include <vector>
#include <list>
#include <codecvt>
//#include <atlconv.h>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h>
#include "tmxlite/Tileset.hpp"
#include "LogSystem.h"
#include "CEGUI/Base.h"
#include "CEGUI/System.h"
#include "CEGUI/RendererModules/Direct3D9/ViewportTarget.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/EventArgs.h"
#include "tmxlite/Map.hpp"
#include <iostream>
#include <imm.h>
#include <locale>
#include <tmxlite/TileLayer.hpp>
#include "StringUtil.h"
//*****************************************************************************************
// Desc: 库文件定义部分  
//***************************************************************************************** 
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"libtmxlite-s-d.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Imm32.lib")
struct CUSTOMVERTEX1
{
	FLOAT _x, _y, _z;               // 顶点的位置  
	FLOAT _u, _v;                   // 纹理坐标  
	CUSTOMVERTEX1(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
		:_x(x), _y(y), _z(z), _u(u), _v(v) {}
};