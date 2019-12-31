#pragma once

#include <stdint.h>
#include <map>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class CppFactoryDelegate;
	class AbstractFactoryDelegate;

	class ObjectFactory : public IObjectFactory
	{
	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		void AddFactoryDelegate(AbstractFactoryDelegate* pFactoryDelegate);
		CppFactoryDelegate* GetCppFactoryDelegate();

		IRefObject* Create(CString strFactoryName, CString strConstructString) override;
		IRefObjectParams* CreateParams() override;

	private:
		CppFactoryDelegate* m_pCppFactoryDelegate;

		map<uint8_t, AbstractFactoryDelegate*> m_mapFactoryDelegateWithHeader;
		map<CString, AbstractFactoryDelegate*> m_mapFactoryDelegateWithName;
	};
}