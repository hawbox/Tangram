#pragma once

#include <map>

namespace IPC
{
	class EndPoint;

	class Broker
	{
	public:
		Broker();
		virtual ~Broker();

		virtual void AddIPCListener(CString strChannel, EndPoint* pEndPoint);
		virtual void RemoveIPCListener(CString strChannel, EndPoint* pEndPoint);
		virtual void DispatchIPCMessage(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra = NULL);
		virtual void DispatchToOtherBrokers(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra = NULL) {};

	private:
		map<CString, map<EndPoint*, int>*> m_mapIPCListeners; // TODO: Need to removed when destructuring?
	};
}
