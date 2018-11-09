#pragma once
#include "Seting.h"
#include "BaseSprite.h"
#include "Texture2d.h"
#include "D3DUtil.h"
class XFile:BaseSprite
{
	public:
		ID3DXMesh *m_Mesh;
		std::vector<D3DMATERIAL9> m_Mtrls;
		std::vector<shared_ptr<Texture2d>> m_Textures;
		HRESULT XFile_Init(LPCWSTR path);
		HRESULT Update();
		HRESULT Render();
};
