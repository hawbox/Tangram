#include "stdafx.h"
#include "TangramCore.h"
#include "TangramApp.h"
#include "TangramCloudSession.h"

CTangramCloudSession::CTangramCloudSession()
{
	m_pSession = nullptr;
}

CTangramCloudSession::~CTangramCloudSession()
{
}

void CTangramCloudSession::InsertString(CString key, CString value)
{
	m_pOwner->m_pChromeRenderFrameHost->InsertString(m_pSession, key, value);
}

void CTangramCloudSession::InsertLong(CString key, long value)
{
	m_pOwner->m_pChromeRenderFrameHost->InsertLong(m_pSession, key, value);
}

void CTangramCloudSession::Insertint64(CString key, __int64 value)
{
	m_pOwner->m_pChromeRenderFrameHost->Insertint64(m_pSession, key, value);
}

void CTangramCloudSession::InsertFloat(CString key, float value)
{
	m_pOwner->m_pChromeRenderFrameHost->InsertFloat(m_pSession, key, value);
}

CString CTangramCloudSession::GetString(CString key)
{
	return m_pOwner->m_pChromeRenderFrameHost->GetString(m_pSession, key);
}

long CTangramCloudSession::GetLong(CString key)
{
	return m_pOwner->m_pChromeRenderFrameHost->GetLong(m_pSession, key);
}

__int64 CTangramCloudSession::Getint64(CString key)
{
	return m_pOwner->m_pChromeRenderFrameHost->Getint64(m_pSession, key);
}

float CTangramCloudSession::GetFloat(CString key)
{
	return m_pOwner->m_pChromeRenderFrameHost->GetFloat(m_pSession, key);
}

void CTangramCloudSession::SendMessage()
{
	if (m_pOwner)
	{
		m_pOwner->m_pChromeRenderFrameHost->SendTangramMessage(m_pSession);
	}
}

void CTangramCloudSession::addEventListener(CString ListenerName)
{
}

void CTangramCloudSession::removeEventListener(CString ListenerName) {
}

