#include "../stdafx.h"
#include "CppFactoryDelegate.h"

#include "RefObject.h"

namespace RefObject
{
	CString CppFactoryDelegate::GetName()
	{
		return L"Cpp";
	}

	uint8_t CppFactoryDelegate::GetHeaderOfHandle()
	{
		return 1;
	}

	IRefObject* CppFactoryDelegate::Create(CString strConstructString)
	{
		return nullptr;
	}

	void CppFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod);
		}
	}

	void CppFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod, (IRefObjectParams*)pParams);
		}
	}

	void CppFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod, (IRefObjectParams*)pParams, (IRefObjectCallback*)pCallback);
		}
	}
}