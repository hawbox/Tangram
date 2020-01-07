#pragma once

#include <stdint.h>
#include <atomic>
#include <map>
#include "../CommonFile/IRefObject.h"
#include "../CommonFile/IGui.h"

namespace RefObject
{
	class CppFactoryDelegate : public IFactoryDelegate
	{
	public:
		CppFactoryDelegate() {};
		virtual ~CppFactoryDelegate() {};

		CString GetName() override;
		uint8_t GetHeaderOfHandle() override;
		IRefObject* Create(Gui::INode* pNode) override;

		void Invoke(IRefObject* pObj, CString strMethod) override;
		void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) override;
		void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) override;
	};
}