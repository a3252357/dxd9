
//=============================================================================
// Name:TerrainClass.cpp
//    Des: һ����װ����ά����ϵͳ�����Դ�ļ�
// 2013�� 3��17��  Create by ǳī
//=============================================================================

#include"TerrainClass.h"

//-----------------------------------------------------------------------------
// Desc: ���캯��
//-----------------------------------------------------------------------------
TerrainClass::TerrainClass()
{
	//��������Ա��������ֵ
	m_pTexture = NULL;
	m_pIndexBuffer = NULL;
	m_pVertexBuffer = NULL;
	m_nCellsPerRow = 0;
	m_nCellsPerCol = 0;
	m_nVertsPerRow = 0;
	m_nVertsPerCol = 0;
	m_nNumVertices = 0;
	m_fTerrainWidth = 0.0f;
	m_fTerrainDepth = 0.0f;
	m_fCellSpacing = 0.0f;
	m_fHeightScale = 0.0f;
}


//--------------------------------------------------------------------------------------
// Name:TerrainClass::LoadTerrainFromFile()
// Desc: ���ص��θ߶���Ϣ�Լ�����
//--------------------------------------------------------------------------------------
BOOL TerrainClass::getTerrain(int num,wchar_t *pTextureFile)
{
	FLOAT byte = 0;
	m_vHeightInfo.resize(num);
	for (int i = 0; i < num; i++) {          
		byte = byte+ rand() % 10 - 5;
		if (byte < 0)byte = 0;
		if (byte > 255)byte = 255;
		m_vHeightInfo[i] = byte;
		printf("%f\n", m_vHeightInfo[i]);
	}

		


	m_pTexture = D3DUtil::getTexture(pTextureFile);
	// ���ص�������

	return TRUE;
}

//--------------------------------------------------------------------------------------
// Name:TerrainClass::InitTerrain()
// Desc: ��ʼ�����εĸ߶�, ��䶥�����������
//--------------------------------------------------------------------------------------
BOOL TerrainClass::InitTerrain(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale)
{
	std::vector<BYTE>inData(nRows*nCols);
	m_nCellsPerRow = nRows; //ÿ�еĵ�Ԫ����Ŀ
	m_nCellsPerCol = nCols; //ÿ�еĵ�Ԫ����Ŀ
	m_fCellSpacing = fSpace;    //��Ԫ���ļ��
	m_fHeightScale = fScale; //�߶�����ϵ��
	m_fTerrainWidth = nRows * fSpace;  //���εĿ��
	m_fTerrainDepth = nCols * fSpace;  //���ε����
	m_nVertsPerRow = m_nCellsPerCol + 1;  //ÿ�еĶ�����
	m_nVertsPerCol = m_nCellsPerRow + 1; //ÿ�еĶ�����
	m_nNumVertices = m_nVertsPerRow * m_nVertsPerCol;  //��������

													   // ͨ��һ��forѭ��������ѵ���ԭʼ�߶ȳ�������ϵ�����õ����ź�ĸ߶�
	for (unsigned int i = 0; i < m_vHeightInfo.size(); i++)
		m_vHeightInfo[i] *= m_fHeightScale;
	//---------------------------------------------------------------
	// ������εĶ���
	//---------------------------------------------------------------
	//1���������㻺��
	if (FAILED(D3DUtil::getD3DDev()->CreateVertexBuffer(m_nNumVertices * sizeof(TERRAINVERTEX),
		D3DUSAGE_WRITEONLY, TERRAINVERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0)))
		return FALSE;
	//2������
	TERRAINVERTEX *pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//3�����ʣ���ֵ
	FLOAT fStartX = -m_fTerrainWidth / 2.0f, fEndX = m_fTerrainWidth / 2.0f;          //ָ����ʼ��ͽ������X����ֵ
	FLOAT fStartZ = m_fTerrainDepth / 2.0f, fEndZ = -m_fTerrainDepth / 2.0f;  //ָ����ʼ��ͽ������Z����ֵ
	FLOAT fCoordU = 3.0f / (FLOAT)m_nCellsPerRow;     //ָ������ĺ�����ֵ
	FLOAT fCoordV = 3.0f / (FLOAT)m_nCellsPerCol;           //ָ�������������ֵ

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z > fEndZ; z -= m_fCellSpacing, i++)          //Z���귽������ʼ���㵽���������м�ı���
	{
		j = 0;
		for (float x = fStartX; x < fEndX; x += m_fCellSpacing, j++)  //X���귽������ʼ���㵽���������м�ı���
		{
			nIndex = i * m_nCellsPerRow + j;         //ָ����ǰ�����ڶ��㻺���е�λ��
			pVertices[nIndex] = TERRAINVERTEX(x, m_vHeightInfo[nIndex], z, j*fCoordU, i*fCoordV); //�Ѷ���λ�������ڸ߶�ͼ�ж�Ӧ�ĸ�����������Լ��������긳ֵ��������ǰ�Ķ���
		//	printf("%f", m_vHeightInfo[nIndex]);
			nIndex++;                                                                          //�������Լ�1
		}
	}
	//4������
	m_pVertexBuffer->Unlock();

	//---------------------------------------------------------------
	// ������ε�����
	//---------------------------------------------------------------
	//1.������������
	if (FAILED(D3DUtil::getD3DDev()->CreateIndexBuffer(m_nNumVertices * 6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
		return FALSE;
	//2.����
	WORD* pIndices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	//3.���ʣ���ֵ
	nIndex = 0;
	for (int row = 0; row < m_nCellsPerRow - 1; row++)   //����ÿ��
	{
		for (int col = 0; col < m_nCellsPerCol - 1; col++)  //����ÿ��
		{
			//������ABC����������
			pIndices[nIndex] = row* m_nCellsPerRow + col;                  //����A
			pIndices[nIndex + 1] = row * m_nCellsPerRow + col + 1;  //����B
			pIndices[nIndex + 2] = (row + 1) *m_nCellsPerRow + col;      //����C
																		 //������CBD����������
			pIndices[nIndex + 3] = (row + 1) *m_nCellsPerRow + col;             //����C
			pIndices[nIndex + 4] = row * m_nCellsPerRow + col + 1;           //����B
			pIndices[nIndex + 5] = (row + 1) *m_nCellsPerRow + col + 1;//����D
																	   //������һ����Ԫ����������6
			nIndex += 6;  //�����Լ�6
		}
	}
	//4������
	m_pIndexBuffer->Unlock();

	return TRUE;
}

//--------------------------------------------------------------------------------------
// Name:TerrainClass::RenderTerrain()
// Desc: ���Ƴ����Σ�����ͨ���ڶ�������ѡ���Ƿ���Ƴ��߿�
//--------------------------------------------------------------------------------------
BOOL TerrainClass::RenderTerrain(D3DXMATRIX *pMatWorld, BOOL bRenderFrame)
{
	D3DUtil::getD3DDev()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TERRAINVERTEX));  ///�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ������� 
	D3DUtil::getD3DDev()->SetFVF(TERRAINVERTEX::FVF);//ָ������ʹ�õ������ʽ�ĺ�����
	D3DUtil::getD3DDev()->SetIndices(m_pIndexBuffer);//������������ 
	D3DUtil::getD3DDev()->SetTexture(0, *m_pTexture->ptexture9);//��������
	D3DUtil::getD3DDev()->SetTransform(D3DTS_WORLD, pMatWorld); //�����������
	D3DUtil::getD3DDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_nNumVertices, 0, m_nNumVertices * 2);              //���ƶ���
	D3DUtil::getD3DDev()->SetTexture(0, 0); //�����ÿ�

	if (bRenderFrame)  //���Ҫ��Ⱦ���߿�Ļ�
	{
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //�����ģʽ��Ϊ�߿����
		D3DUtil::getD3DDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
			m_nNumVertices, 0, m_nNumVertices * 2);       //���ƶ��� 
		D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);    //�����ģʽ����ʵ�����
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
// Desc: ��������
//-----------------------------------------------------------------------------
TerrainClass::~TerrainClass(void)
{
	//SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}