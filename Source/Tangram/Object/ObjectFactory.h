#pragma once

#include <stdint.h>
#include <map>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class CppFactoryDelegate;
	class IFactoryDelegate;

	class ObjectFactory : public IObjectFactory
	{
	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		void AddFactoryDelegate(IFactoryDelegate* pFactoryDelegate) override;
		IFactoryDelegate* GetFactoryDelegate(CString strFactoryName) override;
		IFactoryDelegate* GetFactoryDelegate(uint8_t nFactoryHeader) override;
		IRefObject* GetObjectFromHandle(Handle nHandle) override;
		IRefObject* Create(CString strFactoryName, uint64_t nRawHandle) override;
		IRefObject* Create(CString strFactoryName, CString strConstructString) override;
		bool Delete(CString strFactoryName, uint64_t nRawHandle) override;
		IRefObjectParams* CreateParams() override;

	private:
		map<Handle, IRefObject*> m_mapRefObjects;
		map<uint8_t, IFactoryDelegate*> m_mapFactoryDelegateWithHeader;
		map<CString, IFactoryDelegate*> m_mapFactoryDelegateWithName;
	};
}