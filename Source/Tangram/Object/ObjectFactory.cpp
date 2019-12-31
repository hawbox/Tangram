#include "../stdafx.h"
#include "ObjectFactory.h"

#include "AbstractFactoryDelegate.h"
#include "CppFactoryDelegate.h"
#include "RefObject.h"
#include "RefObjectParams.h"

namespace RefObject
{
	ObjectFactory::ObjectFactory()
	{
		m_pCppFactoryDelegate = new CppFactoryDelegate();
		AddFactoryDelegate(m_pCppFactoryDelegate);
	}

	ObjectFactory::~ObjectFactory() 
	{
		delete m_pCppFactoryDelegate;
	}

	void ObjectFactory::AddFactoryDelegate(AbstractFactoryDelegate* pFactoryDelegate)
	{
		if (pFactoryDelegate != nullptr)
		{
			m_mapFactoryDelegateWithName[pFactoryDelegate->GetName()] = pFactoryDelegate;
			m_mapFactoryDelegateWithHeader[pFactoryDelegate->GetHeaderOfHandle()] = pFactoryDelegate;
		}
	}

	CppFactoryDelegate* ObjectFactory::GetCppFactoryDelegate()
	{
		return m_pCppFactoryDelegate;
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

	IRefObjectParams* ObjectFactory::CreateParams()
	{
		return new RefObjectParams();
	}

}