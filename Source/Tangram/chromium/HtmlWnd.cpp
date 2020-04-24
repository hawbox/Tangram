/********************************************************************************
 *					Tangram Library - version 10.0.0
 **
 *********************************************************************************
 * Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.
 **
 *
 * THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
 * BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
 * WRITTEN CONSENT OF TANGRAM TEAM.
 *
 * THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
 * OUTLINED IN THE TANGRAM LICENSE AGREEMENT.TANGRAM TEAM
 * GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
 * THIS SOFTWARE ON A SINGLE COMPUTER.
 *
 * CONTACT INFORMATION:
 * mailto:tangramteam@outlook.com
 * https://www.tangram.dev
 *
 ********************************************************************************/

#include "../stdafx.h"
#include "../TangramApp.h"
#include "../WndNode.h"
#include "../TangramCloudSession.h"
#include "../Compositor.h"
#include "../NodeWnd.h"
#include "HtmlWnd.h"
#include "BrowserWnd.h"
#include "../Markup.h" 
#include "../Object/RefObjectParams.h"

namespace ChromePlus {
	CHtmlWnd::CHtmlWnd() {
		m_pWebWnd = nullptr;
		m_pDevToolWnd = nullptr;
		m_pDoc = nullptr;
		m_pBindWinForm = nullptr;
		m_pAppProxy = nullptr;
		m_bDevToolWnd = false;
		m_bWebContentVisible = true;
		m_strCurKey = _T("");
		m_strCurXml = _T("");
		m_strDocXml = _T("");
		m_pParentNode = nullptr;
		m_strAppProxyID = _T("");
		m_pBindNode = nullptr;
		m_pCompositorManager = nullptr;
		m_pCompositor = nullptr;
		m_hWebHostWnd = m_hExtendWnd = m_hChildWnd = NULL;
		m_pChromeRenderFrameHost = g_pTangram->m_pCreatingChromeRenderFrameHostBase;
		g_pTangram->m_pCreatingChromeRenderFrameHostBase = nullptr;
	}

	CHtmlWnd::~CHtmlWnd() {
		for (auto it : m_mapChildFormsInfo)
		{
			delete it.second;
		}
		//::RefObject::IObjectFactory* pObjectFactory = g_pTangram->m_pObjectFactory;
		//pObjectFactory->Delete(_T("Cpp"), (uint64_t)this);
	}

	LRESULT CHtmlWnd::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		CBrowserWnd* pParent = nullptr;
		auto it = g_pTangram->m_mapBrowserWnd.find(::GetParent(m_hWnd));
		if (it != g_pTangram->m_mapBrowserWnd.end())
		{
			pParent = (ChromePlus::CBrowserWnd*)it->second;
		}
		HWND hPWnd = ::GetParent(pParent->m_hWnd);
		if (hPWnd != NULL)
		{
			g_pTangram->m_pActiveHtmlWnd = this;
			g_pTangram->m_pCompositor = nullptr;
			g_pTangram->m_bWinFormActived = false;
			g_pTangram->m_hActiveWnd = nullptr;
			LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
			::PostMessage(m_hWnd, WM_TANGRAMMSG, 20190331, 1);
			return lRes;
		}
		else
			g_pTangram->m_pActiveHtmlWnd = nullptr;
		return DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT CHtmlWnd::OnTangramMsg(UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL&) {
		bool bChild = ::GetWindowLongPtr(::GetParent(m_hWnd), GWL_STYLE) & WS_CHILD;
		switch (wParam)
		{
		case 20200310:
		{
			CWndNode* pNode = (CWndNode*)lParam;
			if (pNode && pNode->m_pTangramCloudSession == nullptr)
			{
				pNode->m_pTangramCloudSession = (CTangramCloudSession*)((CTangramImpl*)g_pTangram)->CreateCloudSession(this);
				CTangramCloudSession* pSession = pNode->m_pTangramCloudSession;
				if (pSession)
				{
					pSession->InsertString(_T("msgID"), IPC_NODE_CREARED_ID);
					pSession->InsertLong(_T("autodelete"), 0);
					pSession->InsertLong(_T("nodetype"), pNode->m_nViewType);
					pSession->InsertLong(_T("rows"), pNode->m_nRows);
					pSession->InsertLong(_T("cols"), pNode->m_nCols);
					pSession->InsertLong(_T("row"), pNode->m_nRow);
					pSession->InsertLong(_T("col"), pNode->m_nCol);
					pSession->InsertString(_T("objtype"), pNode->m_strCnnID);
					pSession->InsertString(_T("name@page"), pNode->m_strName);
					pSession->Insertint64(_T("nodehandle"), (__int64)pNode->m_pHostWnd->m_hWnd);
					pSession->Insertint64(_T("compositorhandle"), (__int64)pNode->m_pTangramNodeCommonData->m_pCompositor->m_hWnd);
					pSession->Insertint64(_T("rootnodehandle"), (__int64)pNode->m_pRootObj->m_pHostWnd->m_hWnd);
					pSession->Insertint64(_T("domhandle"), (__int64)pNode->m_pTangramCloudSession);
					pSession->InsertString(_T("objID"), _T("wndnode"));
					if (pNode->m_pParentObj)
					{
						pSession->Insertint64(_T("parentnodehandle"), (__int64)pNode->m_pParentObj->m_pHostWnd->m_hWnd);
					}
					if (pNode->m_pParentWinFormWnd)
					{
						pSession->Insertint64(_T("parentFormHandle"), (__int64)pNode->m_pParentWinFormWnd->m_hWnd);
					}
					if (pNode->m_pDisp)
					{
						pNode->m_pTangramCloudSession->Insertint64(_T("objectdisp"), (__int64)pNode->m_pDisp);
						if (g_pTangram->m_pCLRProxy)
						{
							g_pTangram->m_pCLRProxy->ConnectNodeToWebPage(pNode, true);
						}
					}
					m_pChromeRenderFrameHost->SendTangramMessage(pSession->m_pSession);
				}
			}
		}
		break;
		case 20200311:
		{
			if (m_pCompositor)
			{
				if (m_pCompositor->m_pWorkNode->m_pTangramCloudSession)
				{
					m_pCompositor->m_pWorkNode->m_pTangramCloudSession->InsertString(_T("msgID"), _T("TANGRAMAPP_READY"));
					m_pCompositor->m_pWorkNode->m_pTangramCloudSession->SendMessage();
				}
			}
		}
		break;
		case 20200131:
		{
			if (bChild && m_pChromeRenderFrameHost)
			{
				m_pChromeRenderFrameHost->ShowWebPage(true);
			}
		}
		break;
		case 20200221:
		{
			IPCMsg* pMsg = (IPCMsg*)lParam;
			if (pMsg&& m_pChromeRenderFrameHost)
			{
				m_pChromeRenderFrameHost->SendTangramMessage(pMsg);
				g_pTangram->m_pCurrentIPCMsg = nullptr;
			}
		}
		break;
		case 20200213:
		{
			HWND hWnd = (HWND)lParam;
			if (::IsWindow(hWnd))
			{
				CTangramWinFormWnd* pWnd = (CTangramWinFormWnd*)::SendMessage(hWnd, WM_TANGRAMDATA, 0, 20190214);
				if (pWnd)
				{
					m_mapSubWinForm[hWnd] = pWnd;
					pWnd->m_pParentHtmlWnd = this;
				}
			}
		}
		break;
		case 20200214:
		{
			if (::IsWindow(m_hExtendWnd))
			{
				if (lParam == 0)
				{
					if (m_pChromeRenderFrameHost)
						m_pChromeRenderFrameHost->ShowWebPage(false);
					::SetParent(m_hExtendWnd, m_hWnd);
				}
				else
				{
					CBrowserWnd* pWnd = (CBrowserWnd*)lParam;
					pWnd->m_pVisibleWebWnd = this;
					::SetParent(m_hExtendWnd, pWnd->m_hWnd);
					if (::IsWindow(pWnd->m_hOldTab))
					{
						::SendMessage(pWnd->m_hOldTab, WM_TANGRAMMSG, 0, 20200214);
					}
					pWnd->BrowserLayout();
				}
			}
			else
			{
				CBrowserWnd* pWnd = (CBrowserWnd*)lParam;
				if(pWnd)
					::PostMessage(pWnd->m_hWnd, WM_BROWSERLAYOUT, 0, 2);
			}
		}
		break;
		case 19820911:
		{
			Show(_T(""));
		}
		break;
		case 20190115:
		{
			if (g_pTangram->m_mapCreatingWorkBenchInfo.size())
			{
				::PostAppMessage(::GetCurrentThreadId(), WM_TANGRAMMSG, 0, 20191114);
			}
		}
		break;
		case 20190407:
		{
			//TangramCommon::IPCMsg* pIPCInfo = (TangramCommon::IPCMsg*)lParam;
			//if (pIPCInfo && pIPCInfo->m_strType == _T("eclipse"))
			//{
			//	g_pTangram->CreateEclipseApp(pIPCInfo->m_strKey, pIPCInfo->m_strData);
			//}
			//if (pIPCInfo && pIPCInfo->m_strType == _T("atlmfc"))
			//{
			//	ITangramAppProxy* pProxy = nullptr;
			//	CString appid = pIPCInfo->m_strKey;
			//	auto it2 = g_pTangram->m_mapTangramAppProxy.find(appid);
			//	if (it2 == g_pTangram->m_mapTangramAppProxy.end())
			//	{

			//	}
			//	else
			//	{
			//		pProxy = it2->second;
			//	}
			//	g_pTangram->m_pActiveMDIChildWnd = nullptr;
			//	CMarkup xml;
			//	if (xml.SetDoc(pIPCInfo->m_strData))
			//	{
			//		g_pTangram->m_strCurrentFrameID = xml.GetChildAttrib(L"mainframeid");// "apptitle"m_Parse.attr(_T("mainframeid"), _T("default"));
			//		if (g_pTangram->m_strCurrentFrameID == _T(""))
			//			g_pTangram->m_strCurrentFrameID = _T("default");
			//		CString strAppTitle = xml.GetChildAttrib(L"apptitle");
			//		g_pTangram->m_strCurrentFrameID.MakeLower();
			//		g_pTangram->m_strCurrentDocTemplateXml = xml.GetSubDoc();
			//		pProxy->m_strCreatingFrameTitle = strAppTitle;
			//		auto it3 = g_pTangram->m_mapTemplateInfo.find(_T(".tangramdoc"));
			//		if (it3 != g_pTangram->m_mapTemplateInfo.end())
			//		{
			//			pProxy->CreateNewDocument(g_pTangram->m_strCurrentFrameID, strAppTitle, it3->second, false);
			//			g_pTangram->m_bNewFile = FALSE;
			//		}
			//	}
			//}
			//delete pIPCInfo;
			//return 0;
		}
		break;
		}
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CHtmlWnd::OnParentChanged(UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL&) {
		if (g_pTangram->m_bChromeNeedClosed == false&&lParam) {
			HWND hNewPWnd = (HWND)lParam;
			::GetClassName(hNewPWnd, g_pTangram->m_szBuffer, 256);
			CString strName = CString(g_pTangram->m_szBuffer);
			if (strName == _T("Chrome_WidgetWin_0"))
			{
				if (m_hExtendWnd)
				{
					::SetParent(m_hExtendWnd, m_hWnd);
					::ShowWindow(m_hExtendWnd, SW_HIDE);
				}
				HWND hNewPWnd2 = ::GetParent(m_hWnd);
				bool bNewParent = false;
				if (hNewPWnd != hNewPWnd2)
				{
					hNewPWnd = hNewPWnd2;
					bNewParent = true;
				}
				CBrowserWnd* pChromeBrowserWnd = nullptr;
				auto it = g_pTangram->m_mapBrowserWnd.find(hNewPWnd);
				if (it == g_pTangram->m_mapBrowserWnd.end())
				{
					if (::IsWindowVisible(hNewPWnd)) {
						pChromeBrowserWnd = new CComObject<CBrowserWnd>();
						pChromeBrowserWnd->SubclassWindow(hNewPWnd);
						g_pTangram->m_mapBrowserWnd[hNewPWnd] = pChromeBrowserWnd;
						pChromeBrowserWnd->m_pBrowser = g_pTangram->m_pActiveBrowser;
						if (pChromeBrowserWnd->m_pBrowser)
							pChromeBrowserWnd->m_pBrowser->m_pProxy = pChromeBrowserWnd;
						if (pChromeBrowserWnd && m_hExtendWnd) {
							::SetParent(m_hExtendWnd, hNewPWnd);
							if (::IsWindowVisible(m_hWnd)) {
								pChromeBrowserWnd->m_pVisibleWebWnd = this;
								if (bNewParent)
								{
									pChromeBrowserWnd->BrowserLayout();
									::PostMessageW(hNewPWnd, WM_BROWSERLAYOUT, 0, 2);
								}
							}
						}
					}
				}
			}
			else
			{
				if (m_hExtendWnd)
				{
					::SetParent(m_hExtendWnd, hNewPWnd);
					::ShowWindow(m_hExtendWnd, SW_SHOW);
				}
				HWND hNewPWnd2 = ::GetParent(m_hWnd);
				bool bNewParent = false;
				if (hNewPWnd != hNewPWnd2)
				{
					hNewPWnd = hNewPWnd2;
					bNewParent = true;
				}
				ChromePlus::CBrowserWnd* pChromeBrowserWnd = nullptr;
				auto it = g_pTangram->m_mapBrowserWnd.find(hNewPWnd);
				if (it != g_pTangram->m_mapBrowserWnd.end())
				{
					pChromeBrowserWnd = (ChromePlus::CBrowserWnd*)it->second;
					g_pTangram->m_pActiveBrowser = pChromeBrowserWnd->m_pBrowser;
					if (pChromeBrowserWnd && m_hExtendWnd) {
						if (::IsWindowVisible(m_hWnd)) {
							pChromeBrowserWnd->m_pVisibleWebWnd = this;
							if (bNewParent)
							{
								g_pTangram->m_pActiveBrowser->m_pProxy = pChromeBrowserWnd;
								pChromeBrowserWnd->BrowserLayout();
								::PostMessageW(hNewPWnd, WM_BROWSERLAYOUT, 0, 2);
							}
						}
					}
					if (pChromeBrowserWnd->m_pVisibleWebWnd && m_bDevToolWnd && pChromeBrowserWnd->m_pVisibleWebWnd->m_bDevToolWnd == false)
					{
						if (pChromeBrowserWnd->m_pVisibleWebWnd->m_pDevToolWnd == nullptr)
						{
							pChromeBrowserWnd->m_pVisibleWebWnd->m_pDevToolWnd = this;
							::ShowWindow(m_hWnd,SW_SHOW);
						}
					}
				}
				else
				{
					if (::IsWindowVisible(hNewPWnd)) {
						pChromeBrowserWnd = new CComObject<ChromePlus::CBrowserWnd>();
						pChromeBrowserWnd->SubclassWindow(hNewPWnd);
						g_pTangram->m_mapBrowserWnd[hNewPWnd] = pChromeBrowserWnd;
						pChromeBrowserWnd->m_pBrowser = g_pTangram->m_pActiveBrowser;
						pChromeBrowserWnd->m_pBrowser->m_pProxy = pChromeBrowserWnd;
						if (pChromeBrowserWnd && m_hExtendWnd) {
							::SetParent(m_hExtendWnd, hNewPWnd);
							if (::IsWindowVisible(m_hWnd)) {
								pChromeBrowserWnd->m_pVisibleWebWnd = this;
								if (bNewParent)
								{
									pChromeBrowserWnd->BrowserLayout();
									::PostMessageW(hNewPWnd, WM_BROWSERLAYOUT, 0, 2);
								}
							}
						}
					}
				}
			}
		}
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CHtmlWnd::OnDestroy(UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& /*bHandled*/) {
		if (m_hExtendWnd)
		{
			::DestroyWindow(m_hExtendWnd);
		}

		if (g_pTangram->m_pCLRProxy)
			g_pTangram->m_pCLRProxy->OnWebPageCreated(m_hWnd, (CChromeRenderFrameHostProxy*)this, (IChromeWebPage*)this, 1);

		m_hExtendWnd = nullptr;

		if (m_bDevToolWnd) {
			if (m_pWebWnd) {
				m_pWebWnd->m_pDevToolWnd = nullptr;
			}
		}
		for (auto it : m_mapSubWinForm)
		{
			::DestroyWindow(it.first);
		}
		m_mapSubWinForm.erase(m_mapSubWinForm.begin(), m_mapSubWinForm.end());
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CHtmlWnd::OnShowWindow(UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL&) {
		if (g_pTangram->m_bChromeNeedClosed == false&&::IsWindow(m_hExtendWnd))
		{
			if (wParam) {
				HWND hPWnd = ::GetParent(m_hWnd);
				if (!m_bDevToolWnd)
				{
					auto it = g_pTangram->m_mapBrowserWnd.find(hPWnd);
					if (it != g_pTangram->m_mapBrowserWnd.end()) {
						((ChromePlus::CBrowserWnd*)it->second)->m_pVisibleWebWnd = this;
					}
				}
				::ShowWindow(m_hExtendWnd, SW_SHOW);
				::SetParent(m_hExtendWnd, hPWnd);
				//for (auto it : m_mapSubWinForm)
				//{
				//	::ShowWindow(it.first,SW_SHOW);
				//}
			}
			else
			{
				::SetParent(m_hExtendWnd, m_hWnd);
				//for (auto it : m_mapSubWinForm)
				//{
				//	::ShowWindow(it.first, SW_HIDE);
				//}
			}
		}
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	void CHtmlWnd::OnFinalMessage(HWND hWnd) {
		CBrowserWnd* pPWnd = nullptr;
		auto it2 = g_pTangram->m_mapBrowserWnd.find(::GetParent(hWnd));
		if (it2 != g_pTangram->m_mapBrowserWnd.end())
		{
			pPWnd = (CBrowserWnd*)it2->second;
			if (pPWnd->m_pVisibleWebWnd == this)
				pPWnd->m_pVisibleWebWnd = nullptr;
		}
		auto it = g_pTangram->m_mapHtmlWnd.find(hWnd);
		if (it != g_pTangram->m_mapHtmlWnd.end())
		{
			g_pTangram->m_mapHtmlWnd.erase(it);
		}
		if (g_pTangram->m_pActiveHtmlWnd == this)
			g_pTangram->m_pActiveHtmlWnd = nullptr;
		CWindowImpl::OnFinalMessage(hWnd);
		delete this;
	}

	void CHtmlWnd::Show(CString strID2)
	{
		if (m_pDoc)
			return;
		LONG_PTR data = 0;
		if (::IsWindow(m_hChildWnd))
			data = ::GetWindowLongPtr(m_hChildWnd, GWLP_USERDATA);

		if (data == 0 && g_pTangram->m_pTangramAppProxy)
		{
			if (::IsChild(m_hExtendWnd, m_hChildWnd))
			{
				m_strAppProxyID = _T("");
				auto it = g_pTangram->m_mapWindowPage.find(m_hExtendWnd);
				if (it != g_pTangram->m_mapWindowPage.end())
					m_pCompositorManager = (CCompositorManager*)it->second;
				else
				{
					m_pCompositorManager = new CComObject<CCompositorManager>();
					m_pCompositorManager->m_hWnd = m_hWnd;
					g_pTangram->m_mapWindowPage[m_hWnd] = m_pCompositorManager;

					for (auto it : g_pTangram->m_mapTangramAppProxy)
					{
						CCompositorManagerProxy* pTangramProxy = it.second->OnCompositorManagerCreated(m_pCompositorManager);
						if (pTangramProxy)
							m_pCompositorManager->m_mapCompositorManagerProxy[it.second] = pTangramProxy;
					}
				}

				if (m_strAppProxyID != _T(""))
				{
					m_pAppProxy = nullptr;
					auto it = g_pTangram->m_mapTangramAppProxy.find(m_strAppProxyID.MakeLower());
					if (it != g_pTangram->m_mapTangramAppProxy.end())
						m_pAppProxy = it->second;
					else
					{
						CString strPath = g_pTangram->m_strAppPath;
						HMODULE hHandle = nullptr;
						CString strAppName = _T("");
						int nPos = m_strAppProxyID.Find(_T("."));
						if (nPos != -1)
							strAppName = m_strAppProxyID.Left(nPos);
						CString strdll = strPath + m_strAppProxyID + _T("\\") + strAppName + _T(".dll");
						if (::PathFileExists(strdll))
							hHandle = ::LoadLibrary(strdll);
						if (hHandle == nullptr)
						{
							strdll = g_pTangram->m_strAppCommonDocPath2 + m_strAppProxyID + _T("\\") + strAppName + _T(".dll");
							if (::PathFileExists(strdll))
								hHandle = ::LoadLibrary(strdll);
						}
						if (hHandle)
						{
							it = g_pTangram->m_mapTangramAppProxy.find(m_strAppProxyID.MakeLower());
							if (it != g_pTangram->m_mapTangramAppProxy.end())
							{
								m_pAppProxy = it->second;
							}
						}
					}
					if (m_pAppProxy)
					{
						g_pTangram->m_pActiveAppProxy = m_pAppProxy;
						m_pAppProxy->m_hCreatingView = m_hChildWnd;
						::SetWindowText(m_hChildWnd, g_pTangram->m_strAppKey);
						m_pDoc = (CTangramDoc*)m_pAppProxy->NewDoc();
						if (m_pDoc)
						{
							auto it = m_pCompositorManager->m_mapCompositor.find(m_hChildWnd);
							if (it != m_pCompositorManager->m_mapCompositor.end())
								m_pCompositor = it->second;
						}
					}
				}
				else
				{
					ICompositor* pCompositor = nullptr;
					m_pCompositorManager->CreateCompositor(CComVariant(0), CComVariant((LONGLONG)m_hChildWnd), CComBSTR(L"default"), &pCompositor);
					if (pCompositor)
					{
						m_pCompositor = (CCompositor*)pCompositor;
						m_pCompositorManager->m_mapNeedSaveCompositor[m_hChildWnd] = m_pCompositor;
						IWndNode* pNode = nullptr;
						pCompositor->Open(CComBSTR("default"), CComBSTR(L""), &pNode);
					}
				}
			}
		}
	}

	// DOM

	void CHtmlWnd::getElementById(CString strId, ::RefObject::RefObjectCallback* pCallback)
	{
		CString strMsgId = SendIPCMessageInternal(_T("system@") + Id(), strId, _T("__getElementById__"), _T(""));
		m_mapIPCCallback.insert(std::make_pair(strMsgId, pCallback));
	}

	// IPC

	IPC::Broker* CHtmlWnd::GetBroker()
	{
		return (IPC::Broker*)m_pCompositor;
	}

	void CHtmlWnd::OnIPCMessageReceived(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra)
	{
		auto it = m_mapIPCCallback.find(strMsgId);
		if (it != m_mapIPCCallback.end())
		{
			::RefObject::RefObjectParams pParams;
			pParams.AddParam(strPayload);
			it->second->Invoke(nullptr, &pParams);
			delete it->second;
			m_mapIPCCallback.erase(it);
		}
		else
		{
			SendChromeIPCMessage(_T("MESSAGE"), strFrom, strTo, strMsgId, strPayload, strExtra);
		}
	}

	void CHtmlWnd::SendChromeIPCMessage(CString strId, CString strParam1, CString strParam2, CString strParam3, CString strParam4, CString strParam5)
	{
		if (m_pChromeRenderFrameHost != nullptr)
		{
			IPCMsg pIPCInfo;
			pIPCInfo.m_strId = strId;
			pIPCInfo.m_strParam1 = strParam1;
			pIPCInfo.m_strParam2 = strParam2;
			pIPCInfo.m_strParam3 = strParam3;
			pIPCInfo.m_strParam4 = strParam4;
			pIPCInfo.m_strParam5 = strParam5;
			m_pChromeRenderFrameHost->SendTangramMessage(&pIPCInfo);
		}
		g_pTangram->m_pCurrentIPCMsg = nullptr;
	}

	LRESULT CHtmlWnd::OnChromeIPCMsgReceived(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (lParam)
		{
			if (wParam && m_pChromeRenderFrameHost == nullptr)
			{
				m_pChromeRenderFrameHost = (CChromeRenderFrameHost*)wParam;
				m_pChromeRenderFrameHost->m_pProxy = this;
			}
			
			IPCMsg* pIPCInfo = (IPCMsg*)lParam;
			CString strId = pIPCInfo->m_strId;
			CString strParam1 = pIPCInfo->m_strParam1;
			CString strParam2 = pIPCInfo->m_strParam2;
			CString strParam3 = pIPCInfo->m_strParam3;
			CString strParam4 = pIPCInfo->m_strParam4;
			CString strParam5 = pIPCInfo->m_strParam5;
			if (pIPCInfo->m_strId.CompareNoCase(_T("TANGRAM_CTRL_VALUE_MESSAGE")) == 0)
			{
				HWND hCtrl = (HWND)pIPCInfo->m_nHandleFrom;
				if (g_pTangram->m_pCLRProxy)
				{
					IDispatch* pCtrl = g_pTangram->m_pCLRProxy->GetCtrlFromHandle(hCtrl);
					if (pCtrl)
						g_pTangram->m_pCLRProxy->SetCtrlValueByName(pCtrl, CComBSTR(""), true, CComBSTR(strParam4));
				}
			}
			else
			{
				HandleChromeIPCMessage(strId, strParam1, strParam2, strParam3, strParam4, strParam5);
			}
			g_pTangram->m_pCurrentIPCMsg = nullptr;
		}

		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	CChromeBrowserBase* CHtmlWnd::GetChromeBrowserBase(HWND hHostWnd)
	{
		return nullptr;
	}

	void CHtmlWnd::LoadDocument2Viewport(CString strName, CString strXML)
	{
		CBrowserWnd* pWnd = nullptr;
		auto it = g_pTangram->m_mapBrowserWnd.find(::GetParent(m_hWnd));
		if (it != g_pTangram->m_mapBrowserWnd.end())
		{
			pWnd = (CBrowserWnd*)it->second;
		}

		if (m_hExtendWnd == nullptr)
		{
			HWND hParent = NULL;
			if (::IsWindowVisible(m_hWnd))
				hParent = ::GetParent(m_hWnd);
			else
				hParent = m_hWnd;
			
			m_hExtendWnd = ::CreateWindowEx(NULL, _T("Chrome Extended Window Class"), L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 0, 0, hParent, NULL, theApp.m_hInstance, NULL);
			m_hChildWnd = ::CreateWindowEx(NULL, _T("Chrome Extended Window Class"), L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 0, 0, m_hExtendWnd, (HMENU)1, theApp.m_hInstance, NULL);

			::SetWindowLongPtr(m_hExtendWnd, GWLP_USERDATA, (LONG_PTR)m_hChildWnd);
			::SetWindowLongPtr(m_hChildWnd, GWLP_USERDATA, (LONG_PTR)this);
		}
		if (m_hExtendWnd)
		{
			if (m_pCompositor == nullptr) {
				CCompositorManager* pCompositorManager = nullptr;
				auto it = g_pTangram->m_mapWindowPage.find(m_hExtendWnd);
				if (it != g_pTangram->m_mapWindowPage.end())
					pCompositorManager = (CCompositorManager*)it->second;
				else
				{
					pCompositorManager = new CComObject<CCompositorManager>();
					pCompositorManager->m_hWnd = m_hExtendWnd;
					g_pTangram->m_mapWindowPage[m_hExtendWnd] = pCompositorManager;

					for (auto it : g_pTangram->m_mapTangramAppProxy)
					{
						CCompositorManagerProxy* pTangramProxy = it.second->OnCompositorManagerCreated(pCompositorManager);
						if (pTangramProxy)
							pCompositorManager->m_mapCompositorManagerProxy[it.second] = pTangramProxy;
					}
				}
				if (pCompositorManager) {
					ICompositor* pCompositor = nullptr;
					pCompositorManager->CreateCompositor(CComVariant((__int64)0), CComVariant((__int64)m_hChildWnd), CComBSTR("default"), &pCompositor);
					if (pCompositor)
					{
						m_pCompositor = (CCompositor*)pCompositor;
						m_pCompositor->m_pWebPageWnd = this;
					}
				}
			}
			if (m_pCompositor)
			{
				IWndNode* pNode = nullptr;
				m_pCompositor->Open(CComBSTR(strName), CComBSTR(strXML), &pNode);
				if (pNode)
				{
					m_strCurKey = strName;
					m_hWebHostWnd = NULL;
					if (m_pCompositor->m_pBindingNode)
					{
						m_hWebHostWnd = m_pCompositor->m_pBindingNode->m_pHostWnd->m_hWnd;
					}
				}
			}
		}
		if (::IsWindowVisible(m_hWnd))
		{
			::SendMessage(::GetParent(m_hWnd), WM_BROWSERLAYOUT, 0, 2);
			::PostMessage(::GetParent(m_hWnd), WM_BROWSERLAYOUT, 0, 2);
		}
	}

	void CHtmlWnd::HandleChromeIPCMessage(CString strId, CString strParam1, CString strParam2, CString strParam3, CString strParam4, CString strParam5)
	{
		if (strId.CompareNoCase(_T("ADD_CHANNEL")) == 0)
		{
			AddChannelInternal(strParam1);
		}
		else if (strId.CompareNoCase(_T("REMOVE_CHANNEL")) == 0)
		{
			// TODO: RemoveChannelInternal
		}
		else if (strId.CompareNoCase(_T("RENDER_ELEMENT")) == 0)
		{
			RenderHTMLElement(strParam1, strParam2);
		}
		else if (strId.CompareNoCase(_T("AGGREGATED_MESSAGE")) == 0)
		{
			HandleAggregatedMessage(strParam1, strParam2);
			if (m_strDocXml != _T(""))
			{
				RenderHTMLDocElement(m_strDocXml);
			}
			if (g_pTangram->m_bAppInitFromWeb == false && g_pTangram->m_strAppXml != _T(""))
			{
				g_pTangram->m_bAppInitFromWeb = true;
				g_pTangram->TangramInitFromeWeb();
				if (g_pTangram->m_strMainWndXml != _T(""))
				{
					RenderHTMLMainWindowElement(g_pTangram->m_strMainWndXml);
				}
				auto t = create_task([this]()
				{
					SleepEx(200, true);
					try
					{
						::PostMessage(::GetParent(m_hWnd), WM_TANGRAMMSG, 20200214, 0);
					}
					catch (...)
					{
						ATLASSERT(false);
						return 0;
					}
					return 1;
				});
			}
		}
		else if (strId.CompareNoCase(_T("NEW_TAB_PAGE_LOADED")) == 0)
		{
			OnNTPLoaded();
			AddChannelInternal(_T("system"));
		}
		else if (strId.CompareNoCase(_T("MESSAGE")) == 0)
		{
			SendIPCMessageInternal(strParam1, strParam2, strParam3, strParam4);
		}
		else if (strId.CompareNoCase(_T("TANGRAM_UI_MESSAGE")) == 0)
		{
			// Param1: Frame Name, Param2: HWND, Param3: XML, Param4: BindWebObj Name
			HWND hWndSource = (HWND)_wtoi(LPCTSTR(strParam2));
			if (::IsWindow(hWndSource))
			{
				auto it = m_mapWinForm.find(hWndSource);
				if (it != m_mapWinForm.end())
				{
					LoadDocument2Viewport(strParam1, strParam3);
					return;
				}
				LRESULT lRes= ::SendMessage(hWndSource, WM_TANGRAMDATA, 0, 20190214);
				if (lRes)
				{
					LoadDocument2Viewport(strParam2, strParam3);
					return;
				}
			}
			auto it = m_mapBindWebObj.find(strParam4);
			if (it != m_mapBindWebObj.end())
			{
				BindWebObj* pObj = it->second;
				HWND hWnd = pObj->m_hWnd;
				switch (pObj->nType)
				{
				case 0:
				{
					ICompositor* pCompositor = nullptr;
					IWndNode* pNode = nullptr;
					m_pCompositor->m_pCompositorManager->CreateCompositor(CComVariant(0), CComVariant((__int64)hWnd), CComBSTR(pObj->m_strBindObjName), &pCompositor);
					pCompositor->Open(CComBSTR(strParam1 + _T("_") + strParam4), CComBSTR(strParam3), &pNode);
					if (pNode)
					{
						CWndNode* _pNode = (CWndNode*)pNode;
						_pNode->m_strLastIPCMsgID = strId;
						_pNode->m_strLastIPCParam1 = strParam1;
						_pNode->m_strLastIPCParam2 = strParam2;
						_pNode->m_strLastIPCParam3 = strParam3;
						_pNode->m_strLastIPCParam4 = strParam4;
						_pNode->m_strLastIPCParam5 = strParam5;
					}
				}
				break;
				case 1:
				{
					CWndNode* _pNode = (CWndNode*)pObj->m_pNode;
					IWndNode* pNode = nullptr;
					_pNode->Open(CComBSTR(strParam1 + _T("_") + strParam4), CComBSTR(strParam3), &pNode);
					if (pNode)
					{
						CWndNode* _pNode = (CWndNode*)pNode;
						if (_pNode->m_strLastIPCMsgID == _T("") || _pNode->m_strLastIPCMsgID != strId)
						{
							_pNode->m_strLastIPCMsgID = strId;
							_pNode->m_strLastIPCParam1 = strParam1;
							_pNode->m_strLastIPCParam2 = strParam2;
							_pNode->m_strLastIPCParam3 = strParam3;
							_pNode->m_strLastIPCParam4 = strParam4;
							_pNode->m_strLastIPCParam5 = strParam5;
						}
						else if (_pNode->m_strLastIPCMsgID == strId)
						{
							TangramCommon::IPCMsg pIPCInfo;
							pIPCInfo.m_strId = strId;
							pIPCInfo.m_strParam1 = _pNode->m_strLastIPCParam1;
							pIPCInfo.m_strParam2 = _pNode->m_strLastIPCParam2;
							pIPCInfo.m_strParam3 = _pNode->m_strLastIPCParam3;
							pIPCInfo.m_strParam4 = _pNode->m_strLastIPCParam4;
							pIPCInfo.m_strParam5 = _pNode->m_strLastIPCParam5;
							_pNode->m_strLastIPCMsgID = _T("");
							//_pNode->m_strLastIPCParam1 = strParam1;
							//_pNode->m_strLastIPCParam2 = strParam2;
							//_pNode->m_strLastIPCParam3 = strParam3;
							//_pNode->m_strLastIPCParam4 = strParam4;
							//_pNode->m_strLastIPCParam5 = strParam5;
							m_pChromeRenderFrameHost->SendTangramMessage(&pIPCInfo);
						}
						g_pTangram->m_pCurrentIPCMsg = nullptr;
					}
				}
				break;
				}
				return;
			}
		}
		else if (strId.CompareNoCase(_T("TO_TOPFRAME")) == 0)
		{
			LoadDocument2Viewport(strParam1, strParam2);
			return;
		}
		else if (strId.CompareNoCase(_T("TO_PARENTNODE")) == 0)
		{
			if (m_pParentNode == nullptr)
			{
				HWND hWnd = ::GetParent(::GetParent(m_hWnd));
				if (::IsWindow(hWnd))
				{
					LRESULT lRes = ::SendMessage(hWnd, WM_TANGRAMGETNODE, 0, 0);
					HWND _hWnd = (HWND)hWnd;
					if (lRes)
						m_pParentNode = (CWndNode*)lRes;
				}
				else
				{
					m_pParentNode = m_pCompositor->m_pBindingNode->m_pParentObj;
					if (m_pParentNode && m_pParentNode->m_nViewType == TabbedWnd)
					{
						//IWndNode* _pNode = nullptr;
						//m_pCompositor->m_pBindingNode->Open(CComBSTR(strParam2), CComBSTR(strParam1), &_pNode);
						return;
					}
				}
			}
			if (m_pParentNode)
			{
				IWndNode* _pNode = nullptr;
				m_pParentNode->Open(CComBSTR(strParam1), CComBSTR(strParam2), &_pNode);
			}
			return;
		}
		else if (strId.CompareNoCase(_T("TO_BINDNODE")) == 0)
		{
			HWND hWnd = ::GetParent(::GetParent(m_hWnd));
			if (::IsWindow(hWnd))
			{
				if (m_pBindNode == nullptr)
				{
					CWndNode* pNode = nullptr;
					LRESULT lRes = ::SendMessage(hWnd, WM_TANGRAMGETNODE, 0, 0);
					HWND _hWnd = (HWND)hWnd;
					if (lRes)
						pNode = (CWndNode*)lRes;
					if (pNode)
					{
						CComBSTR bstrName("");
						pNode->get_Attribute(CComBSTR("bindnode"), &bstrName);
						CString strName = OLE2T(bstrName);
						if (strName != _T(""))
						{
							CComPtr<IWndNodeCollection> pTangramNodeCollection;
							IWndNode* _pNode = nullptr;
							long nCount = 0;
							pNode->m_pRootObj->GetNodes(bstrName, &_pNode, &pTangramNodeCollection, &nCount);
							if (_pNode)
							{
								m_pBindNode = (CWndNode*)_pNode;
							}
						}
					}
				}
				if (m_pBindNode)
				{
					IWndNode* _pNode = nullptr;
					m_pBindNode->Open(CComBSTR(strParam1), CComBSTR(strParam2), &_pNode);
				}
			}
			return;
		}
		else if (strId.CompareNoCase(_T("TO_PARENTFORM")) == 0)
		{
			HWND hWnd = ::GetAncestor(m_hWnd, GA_ROOT);
			if (::IsWindow(hWnd))
			{
				m_pBindWinForm = (CTangramWinFormWnd*)::SendMessage(hWnd, WM_TANGRAMDATA, 0, 20190214);
				if (m_pBindWinForm)
				{
					//IWndNode* _pNode = nullptr;
					//m_pBindNode->Open(CComBSTR(strMsgId), CComBSTR(strParam1), &_pNode);
				}
			}
		}
		else
		{
			if(g_pTangram->m_pTangramDelegate)
				g_pTangram->m_pTangramDelegate->TangramIPCMsg(m_hWnd, strId, strParam1, strParam2); // TODO: Missing parameters
		}
	}

	void CHtmlWnd::HandleAggregatedMessage(CString strParam1, CString strParam2)
	{
		int nTokenPos = 0;
		CString strToken = strParam1.Tokenize(_T("$$$"), nTokenPos);
		while (!strToken.IsEmpty())
		{
			// Process a single message.
			HandleSingleMessage(strToken);
			strToken = strParam1.Tokenize(_T("$$$"), nTokenPos);
		}
	}

	CString CHtmlWnd::FindToken(CString pszContent, CString pszDelimiter, int& nStart)
	{
		if (nStart == -1)
		{
			return _T("");
		}
		int nNextDelimiter = pszContent.Find(pszDelimiter, nStart);
		if (nNextDelimiter == -1)
		{
			CString pszToken = pszContent.Mid(nStart);
			nStart = -1;
			return pszToken;
		}
		else
		{
			int nCount = nNextDelimiter - nStart;
			CString pszToken = pszContent.Mid(nStart, nCount);
			nStart = nNextDelimiter + pszDelimiter.GetLength();
			if (nStart >= pszContent.GetLength())
			{
				nStart = -1;
			}
			return pszToken;
		}
	}

	void CHtmlWnd::HandleSingleMessage(CString strParam)
	{
		int nStart = 0;
		CString strId = FindToken(strParam, _T("%%%"), nStart);
		CString strParam1 = FindToken(strParam, _T("%%%"), nStart);
		CString strParam2 = FindToken(strParam, _T("%%%"), nStart);
		CString strParam3 = FindToken(strParam, _T("%%%"), nStart);
		CString strParam4 = FindToken(strParam, _T("%%%"), nStart);
		CString strParam5 = FindToken(strParam, _T("%%%"), nStart);
		HandleChromeIPCMessage(strId, strParam1, strParam2, strParam3, strParam4, strParam5);
	}

	void CHtmlWnd::RenderHTMLElement(CString strRuleName, CString strHTML)
	{
		if (strRuleName.CompareNoCase(_T("application")) == 0)
		{
			if (g_pTangram->m_strAppXml == _T(""))
				g_pTangram->m_strAppXml = strHTML;
		}
		else if (strRuleName.CompareNoCase(_T("mainWindow")) == 0)
		{
			if (g_pTangram->m_strMainWndXml == _T(""))
				g_pTangram->m_strMainWndXml = strHTML;
		}
		else if (strRuleName.CompareNoCase(_T("webBrowser")) == 0)
		{
			RenderHTMLWebBrowserElement(strHTML);
		}
		else if (strRuleName.CompareNoCase(_T("indWindow")) == 0)
		{
			RenderHTMLIndWindowElement(strHTML);
		}
		else if (strRuleName.CompareNoCase(_T("object")) == 0)
		{
			RenderHTMLObjectElement(strHTML);
		}
		else if (strRuleName.CompareNoCase(_T("data")) == 0)
		{
			RenderHTMLDataElement(strHTML);
		}
		else if (strRuleName.CompareNoCase(_T("webViewPort")) == 0)
		{
			m_strDocXml = strHTML;
		}
		else if (strRuleName.CompareNoCase(_T("extra")) == 0)
		{
			RenderHTMLExtraElement(strHTML);
		}
		else
		{
			g_pTangram->m_pTangramDelegate->TangramRenderHTMLElement(m_hWnd, strRuleName, strHTML);
		}
	}

	void CHtmlWnd::RenderHTMLMainWindowElement(CString strHTML)
	{
		CTangramXmlParse xmlParse;
		if (xmlParse.LoadXml(strHTML))
		{
			CTangramXmlParse* pMdiChildXmlParse = xmlParse.GetChild(_T("mdichild"));
			if (pMdiChildXmlParse)
			{
				CTangramXmlParse* pMdiClientXmlParse = xmlParse.GetChild(_T("mdiclient"));
				int nCount = pMdiChildXmlParse->GetCount();
				if (nCount && pMdiClientXmlParse)
				{
					CMDIChildFormInfo* pInfo = new CMDIChildFormInfo();
					g_pTangram->m_pCurMDIChildFormInfo = pInfo;
					for (int i = 0; i < nCount; i++)
					{
						CString strName = pMdiChildXmlParse->GetChild(i)->name().MakeLower();
						if (pMdiClientXmlParse->GetChild(strName))
							pInfo->m_mapFormsInfo[strName] = pMdiChildXmlParse->GetChild(i)->xml();
					}
				}
			}
			if (g_pTangram->m_pCLRProxy == nullptr)
				g_pTangram->LoadCLR();
			if (g_pTangram->m_pCLRProxy)
			{
				CChromeRenderFrameHostProxy* pChromeRenderFrameHostProxyBase = (CChromeRenderFrameHostProxy*)this;
				xmlParse.put_attr(_T("renderframehostproxy"), (__int64)pChromeRenderFrameHostProxyBase);
				IDispatch* pDisp = g_pTangram->m_pCLRProxy->CreateCLRObj(xmlParse.xml());
			}
		}
	}

	void CHtmlWnd::RenderHTMLIndWindowElement(CString strHTML)
	{
		CTangramXmlParse xmlParse;
		if (xmlParse.LoadXml(strHTML))
		{
			CTangramXmlParse* pMdiChildXmlParse = xmlParse.GetChild(_T("mdichild"));
			if (pMdiChildXmlParse)
			{
				CTangramXmlParse* pMdiClientXmlParse = xmlParse.GetChild(_T("mdiclient"));
				int nCount = pMdiChildXmlParse->GetCount();
				if (nCount && pMdiClientXmlParse)
				{
					CMDIChildFormInfo* pInfo = new CMDIChildFormInfo();
					g_pTangram->m_pCurMDIChildFormInfo = pInfo;
					for (int i = 0; i < nCount; i++)
					{
						CString strName = pMdiChildXmlParse->GetChild(i)->name().MakeLower();
						if (pMdiClientXmlParse->GetChild(strName))
							pInfo->m_mapFormsInfo[strName] = pMdiChildXmlParse->GetChild(i)->xml();
					}
				}
			}
			if (g_pTangram->m_pCLRProxy == nullptr)
				g_pTangram->LoadCLR();
			if (g_pTangram->m_pCLRProxy)
			{
				CChromeRenderFrameHostProxy* pChromeRenderFrameHostProxyBase = (CChromeRenderFrameHostProxy*)this;
				xmlParse.put_attr(_T("renderframehostproxy"), (__int64)pChromeRenderFrameHostProxyBase);
				IDispatch* pDisp = g_pTangram->m_pCLRProxy->CreateCLRObj(xmlParse.xml());
			}
		}
	}

	void CHtmlWnd::RenderHTMLWebBrowserElement(CString strHTML)
	{
		CTangramXmlParse m_Parse;
		if (m_Parse.LoadXml(strHTML))
		{
			CString strUrls = _T("");
			int nCount = m_Parse.GetCount();
			if (nCount > 0)
			{
				for (int i = 0; i < nCount; i++)
				{
					CString strUrl = m_Parse.GetChild(i)->val();
					int nPos2 = strUrl.Find(_T(":"));
					if (nPos2 != -1)
					{
						CString strURLHeader = strUrl.Left(nPos2);
						if (strURLHeader.CompareNoCase(_T("host")) == 0)
						{
							strUrl = g_pTangram->m_strAppPath + strUrl.Mid(nPos2 + 1);
						}
					}
					strUrls = strUrls + strUrl + _T("|");
				}
			}
			else
			{
				strUrls = "chrome://newtab|";
			}

			g_pTangram->m_pBrowserFactory->CreateBrowser(NULL, strUrls);
		}
	}

	void CHtmlWnd::RenderHTMLObjectElement(CString strHTML)
	{
		CTangramXmlParse m_Parse;
		if (m_Parse.LoadXml(strHTML))
		{
			CString strType = m_Parse.attr(_T("type"), _T(""));
			if (strType.CompareNoCase(_T("winform")) == 0)
			{
				CString strStartup = _T("");
				CTangramXmlParse* pChild3 = m_Parse.GetChild(_T("mdichild"));
				CString strID = m_Parse.attr(_T("uikey"), _T("")).MakeLower();
				CString strName = m_Parse.name();
				if (strID != _T(""))
				{
					m_mapFormsInfo[strID] = m_Parse.xml();
				}
				if (m_Parse.attrBool(_T("showstartup")))
				{
					strStartup = strID;
				}
				if (pChild3)
				{
					CTangramXmlParse* pChild4 = m_Parse.GetChild(_T("mdiclient"));
					int nCount = pChild3->GetCount();
					if (nCount && pChild4)
					{
						CMDIChildFormInfo* pInfo = new CMDIChildFormInfo();
						g_pTangram->m_pCurMDIChildFormInfo = pInfo;
						for (int i = 0; i < nCount; i++)
						{
							CString strName = pChild3->GetChild(i)->name().MakeLower();
							if (pChild4->GetChild(strName))
								pInfo->m_mapFormsInfo[strName] = pChild3->GetChild(i)->xml();
						}
					}
				}
				if (strStartup != _T(""))
				{
					CString strID = strStartup.MakeLower();
					if (g_pTangram->m_pCLRProxy == nullptr)
						g_pTangram->LoadCLR();
					if (g_pTangram->m_pCLRProxy)
					{
						auto it = m_mapFormsInfo.find(strID);
						if (it != m_mapFormsInfo.end())
						{
							auto it2 = m_mapChildFormsInfo.find(strID);
							if (it2 != m_mapChildFormsInfo.end())
								g_pTangram->m_pCurMDIChildFormInfo = it2->second;
							IDispatch* pDisp = g_pTangram->m_pCLRProxy->CreateCLRObj(it->second);
							HWND hwnd = g_pTangram->m_pCLRProxy->GetCtrlHandle(pDisp);
							if (hwnd)
							{
								CTangramWinFormWnd* pForm = (CTangramWinFormWnd*)::SendMessage(hwnd, WM_TANGRAMDATA, 0, 20190214);
								if (pForm)
								{
									pForm->m_pOwnerHtmlWnd = this;
								}
							}
						}
					}
				}
			}
			else if (strType.CompareNoCase(_T("usercontrol")) == 0)
			{
				CString strID = m_Parse.attr(_T("uikey"), _T("")).MakeLower();
				if (strID != _T(""))
				{
					m_mapUserControlsInfo[strID] = m_Parse.xml();
				}
			}
			if (strType.CompareNoCase(_T("workbench")) == 0)
			{
				bool bSkip = false;
				if (::IsChild(g_pTangram->m_hHostBrowserWnd, m_hWnd))
				{
					if (g_pTangram->m_nAppType != TANGRAM_APP_ECLIPSE && g_pTangram->m_nAppType != TANGRAM_APP_BROWSER_ECLIPSE)
					{
						bSkip = true;
					}
				}
				if (bSkip == false)
				{
					CString strStartup = _T("");
					CString strID = m_Parse.attr(_T("workbenchkey"), _T(""));
					CString strName = m_Parse.name();
					if (strID != _T(""))
					{
						g_pTangram->m_mapCreatingWorkBenchInfo[strID] = m_mapWorkBenchInfo[strID] = m_Parse.xml();
					}
					if (m_Parse.attrBool(_T("showstartup")))
					{
						strStartup = strID;
					}
					if (strStartup != _T(""))
					{
						CString strID = strStartup;
						g_pTangram->m_strWorkBenchStrs = strID;
						g_pTangram->m_strWorkBenchStrs += _T("|");
						g_pTangram->m_nAppType = TANGRAM_APP_BROWSER_ECLIPSE;
					}
				}
			}
			else if (strType.CompareNoCase(_T("browser")) == 0)
			{
				CString strUrls = _T("");
				int nCount = m_Parse.GetCount();
				for (int i = 0; i < nCount; i++)
				{
					CString strUrl = m_Parse.GetChild(i)->attr(_T("url"), _T(""));
					int nPos2 = strUrl.Find(_T(":"));
					if (nPos2 != -1)
					{
						CString strURLHeader = strUrl.Left(nPos2);
						if (strURLHeader.CompareNoCase(_T("host")) == 0)
						{
							strUrl = g_pTangram->m_strAppPath + strUrl.Mid(nPos2 + 1);
						}
					}
					strUrls = strUrls + strUrl + _T("|");
				}
				g_pTangram->m_pBrowserFactory->CreateBrowser(NULL, strUrls);
			}
		}
	}

	void CHtmlWnd::RenderHTMLExtraElement(CString strHTML)
	{
		CMarkup rootXML;
		if (rootXML.SetDoc(strHTML) && rootXML.FindElem())
		{
			CString strTarget = rootXML.GetAttrib(_T("target"));
			if (strTarget.CompareNoCase(_T("ntp")) == 0)
			{
				g_pTangram->m_strNtpXml = strHTML;
			}
		}
	}

	void CHtmlWnd::RenderHTMLDataElement(CString strHTML)
	{
		CMarkup rootXML;
		if (rootXML.SetDoc(strHTML) && rootXML.FindElem())
		{
			CString strKey = rootXML.GetAttrib(_T("key"));
			g_pTangram->m_mapValInfo[strKey] = CComVariant(strHTML);
		}
	}

	void CHtmlWnd::RenderHTMLDocElement(CString strHTML)
	{
		CMarkup rootXML;
		if (rootXML.SetDoc(strHTML) && rootXML.FindElem())
		{
			CString strName = rootXML.GetAttrib(_T("name"));
			if (strName == _T(""))
			{
				strName = _T("__VIEWPORT_DEFAULT__");
			}
			LoadDocument2Viewport(strName, strHTML);
			::PostMessage(m_hWnd, WM_TANGRAMMSG, 20200311, 0);
		}
	}

	void CHtmlWnd::OnNTPLoaded()
	{
		if (g_pTangram->m_strNtpXml != _T(""))
		{
			LoadDocument2Viewport(_T("__NTP_DEFAULT__"), g_pTangram->m_strNtpXml);
		}
	}

	void CHtmlWnd::OnWinFormCreated(HWND hwnd)
	{
		if (hwnd)
		{
			LRESULT l = ::SendMessage(hwnd, WM_TANGRAMDATA, 0, 20190214);
			if (l == 0)
			{
				CTangramWinFormWnd* pWnd = new CTangramWinFormWnd();
				g_pTangram->m_hFormNodeWnd = NULL;
				g_pTangram->m_hFormNodeWnd = (HWND)hwnd;
				pWnd->SubclassWindow(hwnd);
				pWnd->m_pOwnerHtmlWnd = this;
				g_pTangram->m_mapFormWebPage[hwnd] = this;
				m_mapWinForm[hwnd] = pWnd;
				::PostMessage(g_pTangram->m_hFormNodeWnd, WM_WINFORMCREATED, 0, 0);
			}
		}
	}

	void CHtmlWnd::OnCloudMsgReceived(CTangramSession* pSession)
	{
		CString strMsgID = pSession->GetString(L"msgID");

		if (strMsgID == _T("CREATE_WINFORM"))
		{
			CString strFormXml = pSession->GetString(_T("formXml"));
			pSession->InsertString(_T("formXml"),_T(""));
			// formType: 0, normal form; 1 subform; 2: dlgform
			long formType = pSession->GetLong(_T("formType"));
			CTangramXmlParse xmlParse;
			if (xmlParse.LoadXml(strFormXml))
			{
				CTangramXmlParse* pMdiChildXmlParse = xmlParse.GetChild(_T("mdichild"));
				if (pMdiChildXmlParse)
				{
					CTangramXmlParse* pMdiClientXmlParse = xmlParse.GetChild(_T("mdiclient"));
					int nCount = pMdiChildXmlParse->GetCount();
					if (nCount && pMdiClientXmlParse)
					{
						CMDIChildFormInfo* pInfo = new CMDIChildFormInfo();
						g_pTangram->m_pCurMDIChildFormInfo = pInfo;
						for (int i = 0; i < nCount; i++)
						{
							CString strName = pMdiChildXmlParse->GetChild(i)->name().MakeLower();
							if (pMdiClientXmlParse->GetChild(strName))
								pInfo->m_mapFormsInfo[strName] = pMdiChildXmlParse->GetChild(i)->xml();
						}
					}
				}
				if (g_pTangram->m_pCLRProxy == nullptr)
					g_pTangram->LoadCLR();
				if (g_pTangram->m_pCLRProxy)
				{
					CChromeRenderFrameHostProxy* pProxyBase = (CChromeRenderFrameHostProxy*)this;
					xmlParse.put_attr(_T("renderframehostproxy"), (__int64)pProxyBase);
					xmlParse.put_attr(_T("ipcsession"), (__int64)pSession);
					pSession->Insertint64(_T("domhandle"), (__int64)pSession);
					pSession->InsertLong(_T("autodelete"), 0);
					IChromeWebPage* pChromeWebPage = (IChromeWebPage*)this;
					xmlParse.put_attr(_T("webpage"), (__int64)pChromeWebPage);
					xmlParse.put_attr(_T("webpagehandle"), (__int64)m_hWnd);
					if (formType == 2)
					{
						xmlParse.put_attr(_T("model"), 1);
					}
					pSession->m_pOwner = this;
					IDispatch* pDisp = g_pTangram->m_pCLRProxy->CreateCLRObj(xmlParse.xml());
				}
			}
		}
	}

	STDMETHODIMP CHtmlWnd::get_HostWnd(LONGLONG* Val)
	{
		*Val = (LONGLONG)m_hWebHostWnd;
		return S_OK;
	}

	STDMETHODIMP CHtmlWnd::put_HostWnd(LONGLONG newVal)
	{
		HWND hWnd = (HWND)newVal;
		if (::IsWindow(hWnd))
			m_hWebHostWnd = hWnd;
		return S_OK;
	}

	STDMETHODIMP CHtmlWnd::CreateForm(BSTR bstrKey, LONGLONG hParent, IDispatch** pRetForm)
	{
		if (g_pTangram->m_pCLRProxy == nullptr)
			g_pTangram->LoadCLR();
		if (hParent == 0)
			hParent = (__int64)m_hWnd;
		CString strKey = OLE2T(bstrKey);
		auto it = this->m_mapFormsInfo.find(strKey.MakeLower());
		if (it != m_mapFormsInfo.end())
		{
			*pRetForm = g_pTangram->m_pCLRProxy->CreateWinForm((HWND)hParent, CComBSTR(it->second));
		}
		return S_OK;
	}
}  // namespace ChromePlus




