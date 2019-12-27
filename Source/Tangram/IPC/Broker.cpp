#include "../stdafx.h"
#include "Broker.h"
#include "EndPoint.h"

namespace IPC
{
	Broker::Broker()
	{
	}


	Broker::~Broker()
	{
		for (auto it : m_mapIPCListeners)
		{
			delete it.second;
		}
		m_mapIPCListeners.clear();
	}

	void Broker::AddIPCListener(CString strChannel, EndPoint* pEndPoint)
	{
		map<EndPoint*, int>* mapChannelListeners = nullptr;
		auto it = m_mapIPCListeners.find(strChannel);
		if (it == m_mapIPCListeners.end())
		{
			mapChannelListeners = new map<EndPoint*, int>();
			m_mapIPCListeners[strChannel] = mapChannelListeners;
		}
		else
		{
			mapChannelListeners = it->second;
		}
		(*mapChannelListeners)[pEndPoint] = 1;
	}

	void Broker::RemoveIPCListener(CString strChannel, EndPoint* pEndPoint)
	{
		map<EndPoint*, int>* mapChannelListeners = nullptr;
		auto it = m_mapIPCListeners.find(strChannel);
		if (it == m_mapIPCListeners.end())
		{
			mapChannelListeners = new map<EndPoint*, int>();
			m_mapIPCListeners[strChannel] = mapChannelListeners;
		}
		else
		{
			mapChannelListeners = it->second;
		}
		auto it2 = mapChannelListeners->find(pEndPoint);
		if (it2 != mapChannelListeners->end())
		{
			mapChannelListeners->erase(it2);
		}
	}

	void Broker::DispatchIPCMessage(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra)
	{
		// The strFrom must be current Endpoint's Id and the strTo can be 
		// a Channel name, or a ChannelName@EndpointId.

		map<EndPoint*, int>* mapChannelListeners = nullptr;
		CString strFromId = strFrom;
		CString strToChannel = EndPoint::GetChannelFromAddress(strTo);
		CString strToId = EndPoint::GetEpIdFromAddress(strTo);
		auto it = m_mapIPCListeners.find(strToChannel);
		if (it == m_mapIPCListeners.end())
		{
			mapChannelListeners = new map<EndPoint*, int>();
			m_mapIPCListeners[strToChannel] = mapChannelListeners;
		}
		else
		{
			mapChannelListeners = it->second;
		}
		for (auto it2 : (*mapChannelListeners))
		{
			if (strToId.IsEmpty() && strFromId.CompareNoCase(it2.first->Id()) != 0)
			{
				it2.first->OnIPCMessageReceived(strFrom, strTo, strMsgId, strPayload, strExtra);
			}
			else if (strToId.CompareNoCase(it2.first->Id()) == 0)
			{
				it2.first->OnIPCMessageReceived(strFrom, strTo, strMsgId, strPayload, strExtra);
			}
		}
		DispatchToOtherBrokers(strFrom, strTo, strMsgId, strPayload, strExtra);
	}
}