#pragma once

#include <stdint.h>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class RefObject;
	class RefObjectParams;
	class RefObjectCallback;

	class AbstractFactoryDelegate
	{
	public:
		AbstractFactoryDelegate() {};
		virtual ~AbstractFactoryDelegate() {};

		virtual CString GetName() = 0;
		virtual uint8_t GetHeaderOfHandle() = 0;
		virtual RefObject* Create(CString strConstructString) = 0;
		virtual RefObject* GetObjectFromHandle(Handle nHandle) = 0;

		// Invoke method
		virtual void Invoke(RefObject* pObj, CString strMethod) = 0;
		virtual void Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams) = 0;
		virtual void Invoke(RefObject* pObj, CString strMethod, RefObjectParams* pParams, RefObjectCallback* pCallback) = 0;
	};
}