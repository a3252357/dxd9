#pragma once  

//Tobject:���ö�������ͣ�Tparam�ص���������������    
template<typename Tobject, typename Tparam>
class CCallbackProxy
{
	typedef void (Tobject::*CbFun)(Tparam*);

public:
	void Set(Tobject *pInstance, CbFun pFun);
	bool Exec(Tparam* pParam);

private:
	CbFun       pCbFun;     //�ص�����ָ��    
	Tobject*    m_pInstance;    //���ö���    
};

//���õ��ö�����ص�����    
template<typename Tobject, typename Tparam>
void CCallbackProxy<Tobject, Tparam>::Set(Tobject *pInstance, CbFun pFun)
{
	m_pInstance = pInstance;
	pCbFun = pFun;
};

//���ûص�����    
template<typename Tobject, typename Tparam>
bool CCallbackProxy<Tobject, Tparam>::Exec(Tparam* pParam)
{
	(m_pInstance->*pCbFun)(pParam);
	return true;
}
