#include "..\stdafx.h"
#include "RefObject.h"

#include "RefObjectEventListener.h"

namespace RefObject
{
	RefObject::RefObject(IFactoryDelegate* pFactoryDelegate, uint64_t nRawHandle)
	{
		m_pRefObjectDelegate = nullptr;
		m_pFactoryDelegate = pFactoryDelegate;
		if (pFactoryDelegate != nullptr)
		{
			uint8_t nHeader = pFactoryDelegate->GetHeaderOfHandle();
			m_nHandle = { nHeader, nRawHandle };
		}
	}

	CString RefObject::GetFactoryName()
	{
		if (m_pFactoryDelegate != nullptr)
		{
			return m_pFactoryDelegate->GetName();
		}
		return L"";
	}

	Handle RefObject::GetHandle()
	{
		return m_nHandle;
	}

	void RefObject::AddDelegate(IRefObjectDelegate* pDelegate)
	{
		m_pRefObjectDelegate = pDelegate;
	}

	IRefObjectDelegate* RefObject::GetDelegate()
	{
		return m_pRefObjectDelegate;
	}

	void RefObject::Invoke(CString strMethod)
	{
		if (m_pFactoryDelegate != nullptr)
		{
			m_pFactoryDelegate->Invoke(this, strMethod);
		}
	}

	void RefObject::Invoke(CString strMethod, IRefObjectParams* pParams)
	{
		if (m_pFactoryDelegate != nullptr)
		{
			m_pFactoryDelegate->Invoke(this, strMethod, pParams);
		}
	}

	void RefObject::Invoke(CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
	{
		if (m_pFactoryDelegate != nullptr)
		{
			m_pFactoryDelegate->Invoke(this, strMethod, pParams, pCallback);
		}
	}

	void RefObject::AddEventListener(IRefObjectEventListener* pEvtListener)
	{
		m_mapEventListeners[pEvtListener] = 1;
	}

	void RefObject::RemoveEventListener(IRefObjectEventListener* pEvtListener)
	{
		auto it = m_mapEventListeners.find(pEvtListener);
		if (it != m_mapEventListeners.end())
		{
			m_mapEventListeners.erase(it);
		}
	}

	void RefObject::DispatchEvent(CString strEventType, IRefObjectParams* pParams)
	{
		for (auto it = m_mapEventListeners.begin(); it != m_mapEventListeners.end(); ++it)
		{
			it->first->OnEventHandle(strEventType, pParams);
		}
	}
}