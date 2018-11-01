#include "D3DXFile.h"

HRESULT XFile::XFile_Init(LPCWSTR path)
{
	ID3DXBuffer * adjBuffer;
	ID3DXBuffer * mtrlBuffer;
	DWORD numMtrls;
	if (FAILED(D3DXLoadMeshFromX(path, D3DXMESH_MANAGED, D3DUtil::getD3DDev(), &adjBuffer, &mtrlBuffer, 0, &numMtrls, &m_Mesh)))
		return E_FAIL;
	if (mtrlBuffer != 0 && numMtrls != 0) {
		D3DXMATERIAL*mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
		for (int i = 0; i < numMtrls; i++) {
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			m_Mtrls.push_back(mtrls[i].MatD3D);
			if (mtrls[i].pTextureFilename != 0) {
				Texture2d*   tex = 0;
				char szBuf[1000];
				sprintf_s(szBuf, "%s%s", StringUtil::ConvertLPWSTRToLPSTR(L"C://Users/hanhaishao/Desktop/max/"), mtrls[i].pTextureFilename);
				tex =D3DUtil::getTexture(StringUtil::ConvertLPSTRToLPWSTR(szBuf));
				m_Textures.push_back(tex);
			}
			else {
				m_Textures.push_back(0);
			}
		}
	}
	return S_OK;
}

HRESULT XFile::Update()
{
	for (int i = 0; i < m_Mtrls.size(); i++) {
		D3DUtil::getD3DDev()->SetMaterial(&m_Mtrls[i]);
		D3DUtil::getD3DDev()->SetTexture(0,*m_Textures[i]->ptexture9);
		m_Mesh->DrawSubset(i);
	}
	return S_OK;
}

HRESULT XFile::Render()
{
	//throw std::logic_error("The method or operation is not implemented.");
	return S_OK;
}
