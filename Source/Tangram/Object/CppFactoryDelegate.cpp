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

	RefObject* CppFactoryDelegate::Create(CString strConstructString)
	{
		return nullptr;
	}

	RefObject* CppFactoryDelegate::GetObjectFromHandle(Handle nHandle)
	{
		uint64_t nRawHandle = nHandle.Header;
		RefObject* pRefObject = (RefObject*)nRawHandle;
		return pRefObject;
	}

	void CppFactoryDelegate::Invoke(RefObject* pObj, CString strMethod)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod);
		}
	}

	void CppFactoryDelegate::Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod, (IRefObjectParams*)pParams);
		}
	}

	void CppFactoryDelegate::Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams, RefObjectCallback* pCallback)
	{
		if (pObj->GetDelegate() != nullptr)
		{
			pObj->GetDelegate()->Invoke(pObj, strMethod, (IRefObjectParams*)pParams, (IRefObjectCallback*)pCallback);
		}
	}
}