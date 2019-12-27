#pragma once

namespace IPC
{
	class Broker;

	class EndPoint
	{
	public:
		EndPoint();
		virtual ~EndPoint();

		CString Id() { return m_strId; };
		virtual Broker* GetBroker() = 0;
		virtual void OnIPCMessageReceived(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra = NULL);

		void AddChannelInternal(CString strChannel);
		CString SendIPCMessageInternal(CString strTo, CString strPayload, CString strExtra = NULL, CString strMsgId = NULL);

		static CString GetChannelFromAddress(CString strAddr);
		static CString GetEpIdFromAddress(CString strAddr);

	private:
		CString m_strId;
	};
}
