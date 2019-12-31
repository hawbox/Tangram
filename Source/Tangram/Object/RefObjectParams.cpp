#include "../stdafx.h"
#include "RefObjectParams.h"

namespace RefObject
{
	void RefObjectParams::AddParam(CString strParam)
	{
		m_vecParams.push_back(strParam);
	}

	CString RefObjectParams::GetParam(uint32_t nIndex)
	{
		if (nIndex < m_vecParams.size())
		{
			return  m_vecParams.at(nIndex);
		}
		return _T("");
	}

	size_t RefObjectParams::Count()
	{
		return m_vecParams.size();
	}
}