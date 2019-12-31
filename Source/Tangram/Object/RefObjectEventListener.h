#pragma once

#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class RefObjectParams;

	class RefObjectEventListener : public IRefObjectEventListener
	{
	public:
		RefObjectEventListener() {};
		virtual ~RefObjectEventListener() {};

		// virtual void OnEventHandle(CString strEventType, RefObjectParams* pParams) = 0;
	};
}