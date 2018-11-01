#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class Texture2d;
class XFile:BaseSprite
{
	public:
		ID3DXMesh *m_Mesh;
		std::vector<D3DMATERIAL9> m_Mtrls;
		std::vector<Texture2d*> m_Textures;
		HRESULT XFile_Init(LPCWSTR path);
		HRESULT Update();
		HRESULT Render();
};
