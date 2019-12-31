#pragma once

#include <stdint.h>
#include <map>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class AbstractFactoryDelegate;
	class RefObjectEventListener;
	class RefObjectParams;
	class RefObjectCallback;

	class RefObject : public IRefObject
	{
	public:
		RefObject();
		RefObject(AbstractFactoryDelegate* pFactoryDelegate, uint64_t nRawHandle);
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
		AbstractFactoryDelegate* m_pFactoryDelegate;
		IRefObjectDelegate* m_pRefObjectDelegate;

		map<RefObjectEventListener*, int> m_mapEventListeners;
	};
}