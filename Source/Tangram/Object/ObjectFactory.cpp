#include "../stdafx.h"
#include "ObjectFactory.h"

#include "CppFactoryDelegate.h"
#include "RefObject.h"
#include "RefObjectParams.h"

namespace RefObject
{
	ObjectFactory::ObjectFactory()
	{
		AddFactoryDelegate(new CppFactoryDelegate());
	}

	ObjectFactory::~ObjectFactory() 
	{
		for (auto it : m_mapFactoryDelegateWithHeader)
		{
			delete it.second;
			it.second = nullptr;
		}
		for (auto it : m_mapFactoryDelegateWithName)
		{
			it.second = nullptr;
		}
	}

	void ObjectFactory::AddFactoryDelegate(IFactoryDelegate* pFactoryDelegate)
	{
		if (pFactoryDelegate != nullptr)
		{
			m_mapFactoryDelegateWithName[pFactoryDelegate->GetName()] = pFactoryDelegate;
			m_mapFactoryDelegateWithHeader[pFactoryDelegate->GetHeaderOfHandle()] = pFactoryDelegate;
		}
	}

	IFactoryDelegate* ObjectFactory::GetFactoryDelegate(CString strFactoryName)
	{
		auto it = m_mapFactoryDelegateWithName.find(strFactoryName);
		if (it != m_mapFactoryDelegateWithName.end())
		{
			return it->second;
		}
		return nullptr;
	}

	IFactoryDelegate* ObjectFactory::GetFactoryDelegate(uint8_t nFactoryHeader)
	{
		auto it = m_mapFactoryDelegateWithHeader.find(nFactoryHeader);
		if (it != m_mapFactoryDelegateWithHeader.end())
		{
			return it->second;
		}
		return nullptr;
	}

	IRefObject* ObjectFactory::GetObjectFromHandle(Handle nHandle)
	{
		auto it = m_mapRefObjects.find(nHandle);
		if (it != m_mapRefObjects.end())
		{
			return it->second;
		}
		return nullptr;
	}

	IRefObject* ObjectFactory::Create(CString strFactoryName, uint64_t nRawHandle)
	{
		IFactoryDelegate* pFactoryDelegate = GetFactoryDelegate(strFactoryName);
		if (pFactoryDelegate != nullptr)
		{
			Handle nHandle = { pFactoryDelegate->GetHeaderOfHandle(), nRawHandle };
			IRefObject* pObj = GetObjectFromHandle(nHandle);
			if (pObj != nullptr)
			{
				return pObj;
			}
			pObj = new RefObject(pFactoryDelegate, nRawHandle);
			m_mapRefObjects[nHandle] = pObj;
			return pObj;
		}
		return nullptr;
	}

	IRefObject* ObjectFactory::Create(CString strFactoryName, CString strConstructString)
	{
		auto it = m_mapFactoryDelegateWithName.find(strFactoryName);
		if (it != m_mapFactoryDelegateWithName.end())
		{
			return it->second->Create(strConstructString);
		}
		return nullptr;
	}

	bool ObjectFactory::Delete(CString strFactoryName, uint64_t nRawHandle)
	{
		IFactoryDelegate* pFactoryDelegate = GetFactoryDelegate(strFactoryName);
		if (pFactoryDelegate == nullptr)
		{
			return false;
		}
		Handle nHandle = { pFactoryDelegate->GetHeaderOfHandle(), nRawHandle };
		IRefObject* pObj = GetObjectFromHandle(nHandle);
		if (pObj == nullptr)
		{
			return false;
		}
		m_mapRefObjects.erase(nHandle);
		delete pObj;
		return true;
	}

	IRefObjectParams* ObjectFactory::CreateParams()
	{
		return new RefObjectParams();
	}

}