#pragma once

#include <stdint.h>
#include <atomic>
#include <map>

#include "AbstractFactoryDelegate.h"

namespace RefObject
{
	class RefObject;

	class CppFactoryDelegate : public AbstractFactoryDelegate
	{
	public:
		CppFactoryDelegate() {};
		virtual ~CppFactoryDelegate() {};

		CString GetName() override;
		uint8_t GetHeaderOfHandle() override;
		RefObject* Create(CString strConstructString) override;
		RefObject* GetObjectFromHandle(Handle nHandle) override;

		void Invoke(RefObject* pObj, CString strMethod) override;
		void Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams) override;
		void Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams, RefObjectCallback* pCallback) override;
	};
}