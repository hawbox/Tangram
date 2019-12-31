#pragma once

#include <vector>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
	class RefObjectParams : public IRefObjectParams
	{
	public:
		RefObjectParams() {};
		virtual ~RefObjectParams() {};

		void AddParam(CString strParam) override;
		CString GetParam(uint32_t nIndex) override;
		size_t Count() override;

	private:
		vector<CString> m_vecParams;
	};
}