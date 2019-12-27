#include "../stdafx.h"
#include "EndPoint.h"
#include "Broker.h"
#include "../TangramCore.h"

extern CTangram* g_pTangram;

namespace IPC
{
	EndPoint::EndPoint()
	{
		m_strId = g_pTangram->GetNewGUID();
	}

	EndPoint::~EndPoint()
	{
	}

	void EndPoint::OnIPCMessageReceived(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra)
	{
		// Fire COM event and notifies the C++ layer via "virtual function overload" 
		// or "delegate objects".
	}

	void EndPoint::AddChannelInternal(CString strChannel)
	{
		Broker* pBroker = GetBroker();
		if (pBroker != nullptr)
		{
			pBroker->AddIPCListener(strChannel, this);
		}
	}

	CString EndPoint::SendIPCMessageInternal(CString strTo, CString strPayload, CString strExtra, CString strMsgId)
	{
		// Do not call the Dispatch method directly. Use this method to route the
		// IPC message to specified Broker depending on the situation.

		Broker* pBroker = GetBroker();
		if (pBroker != nullptr)
		{
			if (strMsgId.IsEmpty())
			{
				strMsgId = g_pTangram->GetNewGUID();
			}
			// The strFrom must be current Endpoint's Id and the strTo can be 
			// a Channel name, or a ChannelName@EndpointId.
			pBroker->DispatchIPCMessage(m_strId, strTo, strMsgId, strPayload, strExtra);
			return strMsgId;
		}

		return NULL;
	}

	CString EndPoint::GetChannelFromAddress(CString strAddr)
	{
		int nIndex = strAddr.ReverseFind('@');
		if (nIndex == -1)
		{
			return strAddr;
		}
		return strAddr.Left(nIndex);
	}

	CString EndPoint::GetEpIdFromAddress(CString strAddr)
	{
		int nIndex = strAddr.ReverseFind('@');
		if (nIndex == -1)
		{
			return _T("");
		}
		return strAddr.Mid(nIndex + 1);
	}

}