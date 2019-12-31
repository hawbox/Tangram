#pragma once

#include <stdint.h>
#include <map>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class RefObject : public IRefObject
	{
	public:
		// Don't call it directly!
		RefObject(IFactoryDelegate* pFactoryDelegate, uint64_t nRawHandle);
		virtual ~RefObject() {};

		CString GetFactoryName() override;
		Handle GetHandle() override;
		void AddDelegate(IRefObjectDelegate* pDelegate) override;
		IRefObjectDelegate* GetDelegate() override;

		void Invoke(CString strMethod);
		void Invoke(CString strMethod, IRefObjectParams* pParams) override;
		void Invoke(CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) override;
		void AddEventListener(IRefObjectEventListener* pEvtListener) override;
		void RemoveEventListener(IRefObjectEventListener* pEvtListener) override;
		void DispatchEvent(CString strEventType, IRefObjectParams* pParams) override;

	private:
		Handle m_nHandle = { 0 };
		IFactoryDelegate* m_pFactoryDelegate;
		IRefObjectDelegate* m_pRefObjectDelegate;

		map<IRefObjectEventListener*, int> m_mapEventListeners;
	};
}