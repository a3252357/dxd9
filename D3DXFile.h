#pragma once
#include "Seting.h"
#include "BaseSprite.h"
class XFile:BaseSprite
{
	public:
		ID3DXMesh *m_Mesh;
		std::vector<D3DMATERIAL9> m_Mtrls;
		std::vector<LPDIRECT3DTEXTURE9> m_Textures;
		HRESULT XFile_Init(LPCWSTR path);
		HRESULT Update();
		HRESULT Render();
};
