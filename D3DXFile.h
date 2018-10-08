#ifndef D3DXFILE_H
#define D3DXFILE_H
#include "Seting.h"
#include "Base.h"
class XFile:Base
{
	public:
		ID3DXMesh *m_Mesh;
		std::vector<D3DMATERIAL9> m_Mtrls;
		std::vector<LPDIRECT3DTEXTURE9> m_Textures;
		HRESULT XFile_Init(LPCWSTR path);
		void OUpdate();
		void ORender();
};
#endif
