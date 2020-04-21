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
#include "../NodeWnd.h"
#include "../Compositor.h"
#include "BrowserWnd.h"
#include "HtmlWnd.h"

namespace ChromePlus {
	CBrowserWnd::CBrowserWnd() {
		m_hDrawWnd = 0;
		m_heightfix = 0;
		m_hOldTab = NULL;
		m_bTabChange = false;
		m_pBrowser = nullptr;
		m_pParentNode = nullptr;
		m_fdevice_scale_factor = 1.0f;
		m_strCurKey = _T("");
		m_pVisibleWebWnd = nullptr;
		m_pOmniboxViewViews = nullptr;
		if (g_pTangram->m_pCreatingOmniboxViewViews) {
			m_pOmniboxViewViews = g_pTangram->m_pCreatingOmniboxViewViews;
			g_pTangram->m_pCreatingOmniboxViewViews = nullptr;
		}
	}

	CBrowserWnd::~CBrowserWnd() {}

	void CBrowserWnd::ActiveChromeTab(HWND hActive, HWND hOldWnd)
	{
		m_bTabChange = true;
		if (g_pTangram->m_bChromeNeedClosed == false && m_pBrowser)
		{
			if (::IsWindow(hOldWnd))
			{
				m_hOldTab = hOldWnd;
				::PostMessage(hOldWnd, WM_TANGRAMMSG, 20200214, 0);
			}
			::PostMessage(hActive, WM_TANGRAMMSG, 20200214, (LPARAM)this);
		}
	}

	LRESULT CBrowserWnd::OnChromeTabChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		g_pTangram->m_pActiveHtmlWnd = m_pVisibleWebWnd;
		if (m_pVisibleWebWnd && g_pTangram->m_pActiveHtmlWnd->m_pChromeRenderFrameHost)
		{
			g_pTangram->m_pCompositor = nullptr;
			g_pTangram->m_bWinFormActived = false;
		}

		m_pBrowser->LayoutBrowser();

		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	void CBrowserWnd::UpdateContentRect(HWND hWnd, RECT& rc, int nTopFix) {
		if (hWnd==0||::IsWindowVisible(m_hWnd) == false || g_pTangram->m_bChromeNeedClosed == TRUE || g_pTangram->m_bOMNIBOXPOPUPVISIBLE) {
			return;
		}
		//return;
		if (m_hOldTab)
		{
			RECT rc;
			::GetWindowRect(m_hOldTab, &rc);
			ScreenToClient(&rc);
			::SetWindowPos(m_hOldTab, HWND_BOTTOM, rc.left, rc.top, 1, 1, SWP_NOREDRAW | SWP_NOACTIVATE);
			m_hOldTab = NULL;
		}

		if (m_bTabChange == true || ::IsWindowVisible(hWnd) == FALSE ||
			(m_pVisibleWebWnd && m_pVisibleWebWnd->m_hWnd != hWnd))
		{
			auto it = g_pTangram->m_mapHtmlWnd.find(hWnd);
			if (it != g_pTangram->m_mapHtmlWnd.end())
			{
				m_pVisibleWebWnd = (CHtmlWnd*)it->second;
				if (m_pVisibleWebWnd->m_pChromeRenderFrameHost)
					m_pVisibleWebWnd->m_pChromeRenderFrameHost->ShowWebPage(true);
				if (m_bTabChange)
					::PostMessage(m_hWnd, WM_TANGRAMMSG, 20200205, 1);
				return;
			}
		}
		//if (m_pVisibleWebWnd&&m_pVisibleWebWnd->m_pDevToolWnd)
		//	m_pVisibleWebWnd = m_pVisibleWebWnd->m_pDevToolWnd;
		//BrowserLayout();
		if (m_pVisibleWebWnd)
		{
			if (m_pVisibleWebWnd->m_hExtendWnd == nullptr)
			{
				m_pVisibleWebWnd->m_hExtendWnd = ::CreateWindowEx(NULL, _T("Chrome Extended Window Class"), L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 0, 0, m_hWnd, NULL, theApp.m_hInstance, NULL);
				m_pVisibleWebWnd->m_hChildWnd = ::CreateWindowEx(NULL, _T("Chrome Extended Window Class"), L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 0, 0, m_pVisibleWebWnd->m_hExtendWnd, (HMENU)2, theApp.m_hInstance, NULL);

				::SetWindowLongPtr(m_pVisibleWebWnd->m_hExtendWnd, GWLP_USERDATA, (LONG_PTR)m_pVisibleWebWnd->m_hChildWnd);
				::SetWindowLongPtr(m_pVisibleWebWnd->m_hChildWnd, GWLP_USERDATA, (LONG_PTR)m_pVisibleWebWnd);
			}
			HWND hExtendWnd = m_pVisibleWebWnd->m_hExtendWnd;
			if (::IsChild(hWnd, hExtendWnd))
				::SetParent(hExtendWnd, m_hWnd);

			::SetWindowPos(hExtendWnd, HWND_BOTTOM,
				rc.left,
				nTopFix * m_fdevice_scale_factor,
				rc.right * m_fdevice_scale_factor,
				(rc.bottom - rc.top) * m_fdevice_scale_factor,
				SWP_SHOWWINDOW | SWP_NOREDRAW | SWP_NOACTIVATE);
			HWND hWebHostWnd = m_pVisibleWebWnd->m_hWebHostWnd;
			if (hWebHostWnd == NULL)
				hWebHostWnd = m_pVisibleWebWnd->m_hChildWnd;
			if (::IsWindowVisible(hWebHostWnd) == false) {
				m_pVisibleWebWnd->m_bWebContentVisible = false;
				rc.right = rc.left + 1;
				rc.bottom = rc.top + 1;
			}
			else {
				RECT rc2;
				::GetWindowRect(hWebHostWnd, &rc2);
				if (::ScreenToClient(hExtendWnd, (LPPOINT)&rc2))
				{
					::ScreenToClient(hExtendWnd, ((LPPOINT)&rc2) + 1);
					RECT rect;
					::GetClientRect(hExtendWnd, &rect);

					rc.left += rc2.left / m_fdevice_scale_factor;
					rc.right -= (rect.right - rc2.right) / m_fdevice_scale_factor;
					rc.top += (rc2.top - rect.top) / m_fdevice_scale_factor;
					rc.bottom -= (rect.bottom - rc2.bottom) / m_fdevice_scale_factor;
					m_pVisibleWebWnd->m_bWebContentVisible = true;
					if (rc.right <= rc.left || rc.bottom <= rc.top) {
						m_pVisibleWebWnd->m_bWebContentVisible = false;
						rc.right = rc.left + 1;
						rc.bottom = rc.top + 1;
					}
				}
			}
		}
		BrowserLayout();
	};

	LRESULT CBrowserWnd::BrowserLayout() {
		if (m_pVisibleWebWnd == nullptr || m_bTabChange ||
			!::IsWindowVisible(m_hWnd) ||
			g_pTangram->m_bChromeNeedClosed == TRUE)
			return 0;
		if (!::IsWindow(m_hWnd))
			return 0;
		RECT rcBrowser;
		GetClientRect(&rcBrowser);
		if (m_pVisibleWebWnd->m_pCompositor == nullptr) {
			if (rcBrowser.right * rcBrowser.left)
				::SetWindowPos(m_pVisibleWebWnd->m_hExtendWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_SHOWWINDOW);
			::SetWindowRgn(m_hDrawWnd, NULL, true);
			return 0;
		}

		if (!::IsWindowVisible(m_pVisibleWebWnd->m_hWnd))
		{
			if (m_pVisibleWebWnd->m_hExtendWnd)
				::SetParent(m_pVisibleWebWnd->m_hExtendWnd, m_pVisibleWebWnd->m_hWnd);
			auto it = g_pTangram->m_mapHtmlWnd.find(m_pBrowser->GetActiveWebContentWnd());
			if (it != g_pTangram->m_mapHtmlWnd.end())
			{
				m_pVisibleWebWnd = (CHtmlWnd*)it->second;
				if (m_pVisibleWebWnd->m_hExtendWnd)
					::SetParent(m_pVisibleWebWnd->m_hExtendWnd, m_hWnd);
			}
		}

		if (::GetParent(m_pVisibleWebWnd->m_hExtendWnd) != m_hWnd) {
			::SetParent(m_pVisibleWebWnd->m_hExtendWnd, m_hWnd);
		}

		RECT rcWebPage;
		RECT rcExtendWnd;
		::GetWindowRect(m_pVisibleWebWnd->m_hExtendWnd, &rcExtendWnd);
		::ScreenToClient(m_hWnd, (LPPOINT)&rcExtendWnd);
		::ScreenToClient(m_hWnd, ((LPPOINT)&rcExtendWnd) + 1);
		HWND _hWebPage = m_pVisibleWebWnd->m_hWnd;
		if (m_pVisibleWebWnd->m_pDevToolWnd)
		{
			if (::GetParent(m_pVisibleWebWnd->m_hWnd) == ::GetParent(m_pVisibleWebWnd->m_pDevToolWnd->m_hWnd))
			{
				_hWebPage = m_pVisibleWebWnd->m_pDevToolWnd->m_hWnd;
				::ShowWindow(_hWebPage, SW_SHOW);
			}
		}
		::GetWindowRect(_hWebPage, &rcWebPage);
		::ScreenToClient(m_hWnd, (LPPOINT)&rcWebPage);
		::ScreenToClient(m_hWnd, ((LPPOINT)&rcWebPage) + 1);
		//浏览器窗口区域：
		HRGN hGPUWndRgn = ::CreateRectRgn(rcBrowser.left, rcBrowser.top, rcBrowser.right, rcBrowser.bottom);
		//浏览器页面扩展窗口区域：
		HRGN hWebExtendWndRgn = ::CreateRectRgn(rcExtendWnd.left, rcExtendWnd.top, rcExtendWnd.right, rcExtendWnd.bottom);
		//浏览器页面窗口区域：
		HRGN hWebPage = ::CreateRectRgn(rcWebPage.left, rcWebPage.top, rcWebPage.right, rcWebPage.bottom);
		::CombineRgn(hWebExtendWndRgn, hWebExtendWndRgn, hWebPage, RGN_DIFF);
		::CombineRgn(hGPUWndRgn, hGPUWndRgn, hWebExtendWndRgn, RGN_DIFF);
		::DeleteObject(hWebPage);
		::DeleteObject(hWebExtendWndRgn);
		::SetWindowRgn(m_hDrawWnd, hGPUWndRgn, false);

		return 0;
	}

	LRESULT CBrowserWnd::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		if (LOWORD(wParam) != WA_INACTIVE) {
			if (m_pBrowser) {
				g_pTangram->m_pActiveBrowser = m_pBrowser;
				g_pTangram->m_pActiveBrowser->m_pProxy = this;
				//m_pBrowser->LayoutBrowser();
				::InvalidateRect(m_hWnd, nullptr, true);
			}
		}
		else
		{
			if (g_pTangram->m_pCLRProxy)
				g_pTangram->m_pCLRProxy->HideMenuStripPopup();
		}
		return lRes;
	}

	LRESULT CBrowserWnd::OnDeviceScaleFactorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		m_fdevice_scale_factor = (float)lParam / 100;
		return lRes;
	}

	LRESULT CBrowserWnd::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		if (g_pTangram->m_pCLRProxy)
			g_pTangram->m_pCLRProxy->HideMenuStripPopup();
		if (m_pVisibleWebWnd)
		{
			g_pTangram->m_pActiveHtmlWnd = m_pVisibleWebWnd;
			if (g_pTangram->m_pActiveHtmlWnd && g_pTangram->m_pActiveHtmlWnd->m_pChromeRenderFrameHost)
			{
				g_pTangram->m_pCompositor = nullptr;
				g_pTangram->m_bWinFormActived = false;
			}
		}
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CBrowserWnd::OnTangramMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		HWND hWnd = (HWND)lParam;
		switch (wParam) {
		case 0: {
			g_pTangram->m_pHtmlWndCreated = new CComObject<CHtmlWnd>;
			g_pTangram->m_pHtmlWndCreated->SubclassWindow(hWnd);
			if (g_pTangram->m_pCLRProxy)
				g_pTangram->m_pCLRProxy->OnWebPageCreated(hWnd, (CChromeRenderFrameHostProxy*)g_pTangram->m_pHtmlWndCreated, (IChromeWebPage*)g_pTangram->m_pHtmlWndCreated, 0);
			HWND hPWnd = ::GetParent(m_hWnd);
			if (g_pTangram->m_bCreatingDevTool == false)
			{
				g_pTangram->m_pHtmlWndCreated->m_bDevToolWnd = false;
				g_pTangram->m_mapHtmlWnd[hWnd] = g_pTangram->m_pHtmlWndCreated;
				if (hWnd == m_pBrowser->GetActiveWebContentWnd())
					m_pVisibleWebWnd = g_pTangram->m_pHtmlWndCreated;
			}
			else
			{
				g_pTangram->m_bCreatingDevTool = false;
				g_pTangram->m_pHtmlWndCreated->m_bDevToolWnd = true;
				if (m_pVisibleWebWnd) {
					m_pVisibleWebWnd->m_pDevToolWnd = g_pTangram->m_pHtmlWndCreated;
					g_pTangram->m_pHtmlWndCreated->m_pWebWnd = m_pVisibleWebWnd;
				}
			}
			if (hPWnd)
			{
				g_pTangram->m_pActiveHtmlWnd = m_pVisibleWebWnd;// g_pTangram->m_pHtmlWndCreated;
				g_pTangram->m_pCompositor = nullptr;
				g_pTangram->m_bWinFormActived = false;
				::PostMessage(hWnd, WM_TANGRAMMSG, 20190331, 1);
			}
		} break;
		case 1:
		{
			if (lParam == 20200115)
			{
				//m_rcOldBrowser = m_rcOldExtendWnd = m_rcOldBrowser = { 0,0,0,0 };
				::InvalidateRect(m_hWnd, nullptr, true);
				m_pBrowser->LayoutBrowser();
				::PostMessage(m_hWnd, WM_BROWSERLAYOUT, 0, 2);
				::InvalidateRect(m_hWnd, nullptr, true);
			}
		}
		break;
		case 20190527:
			return (LRESULT)((IChromeWebBrowser*)this);
			break;
		case 20200205:
		{
			if (lParam == 1)
			{
				m_bTabChange = false;
			}
		}
		return 1;
		break;
		case 20200215:
			if (lParam < 100)
			{
				m_heightfix = (int)lParam;
				if (lParam == 0)
				{
					auto t = create_task([this]()
						{
							SleepEx(100, true);
							try
							{
								if (m_pVisibleWebWnd)
								{
									::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOREDRAW);
								}
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
			break;
		case 20200214:
		{
			auto t = create_task([this]()
				{
					m_heightfix = 0;
					SleepEx(500, true);
					try
					{
						if (m_pVisibleWebWnd)
						{
							::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOREDRAW);
							BrowserLayout();
						}
					}
					catch (...)
					{
						ATLASSERT(false);
						return 0;
					}
					return 1;
				});
		}
		return 1;
		break;
		case 20200128:
		{
			if (m_pVisibleWebWnd)
			{
				CCompositor* pCompositor = m_pVisibleWebWnd->m_pCompositor;
				if (pCompositor)
				{
					CWndNode* pNode = pCompositor->m_pWorkNode;
					CNodeWnd* pWnd = (CNodeWnd*)(pNode->m_pHostWnd);
					return (LRESULT)(pWnd->m_hWnd);
				}
			}
		}
		break;
		case 1992:
		{
			return (LRESULT)m_pBrowser->GetBrowser();
		}
		break;
		case 20190629:
		{
			switch (lParam)
			{
			case 1:
				return m_pVisibleWebWnd && ::IsWindow(m_pVisibleWebWnd->m_hExtendWnd);
				break;
			}
		}
		break;
		}
		return lRes;
	}

	LRESULT CBrowserWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
	{
		if (g_pTangram->m_pCLRProxy)
		{
			IChromeWebBrowser* pIChromeWebBrowser = nullptr;
			QueryInterface(__uuidof(IChromeWebBrowser), (void**)&pIChromeWebBrowser);
			g_pTangram->m_pCLRProxy->OnDestroyChromeBrowser(pIChromeWebBrowser);
		}

		m_pVisibleWebWnd = nullptr;
		auto it = g_pTangram->m_mapBrowserWnd.find(m_hWnd);
		if (it != g_pTangram->m_mapBrowserWnd.end()) {
			g_pTangram->m_mapBrowserWnd.erase(it);
		}

		if ((g_pTangram->m_hMainWnd == g_pTangram->m_hHostWnd && g_pTangram->m_mapBrowserWnd.size() == 1)|| 
			g_pTangram->m_hHostBrowserWnd == m_hWnd)
		{
			g_pTangram->m_bChromeNeedClosed = true;
			for (auto it : g_pTangram->m_mapBrowserWnd)
			{
				if (((ChromePlus::CBrowserWnd*)it.second)->m_hWnd != m_hWnd)
					((ChromePlus::CBrowserWnd*)it.second)->PostMessageW(WM_CLOSE, 0, 0);
			}
		}

		if ((g_pTangram->m_hMainWnd == NULL && g_pTangram->m_mapBrowserWnd.size() == 0) ||
			g_pTangram->m_hHostBrowserWnd == m_hWnd) {
			if (g_pTangram->m_hHostBrowserWnd == m_hWnd)
				g_pTangram->m_hHostBrowserWnd = NULL;
			if (g_pTangram->m_pCLRProxy)
			{
				if (g_pTangram->m_pTangramCLRAppProxy)
					g_pTangram->m_pTangramCLRAppProxy->OnTangramClose();

				g_pTangram->m_bClose = true;
			}

			if (g_pTangram->m_hCBTHook) {
				UnhookWindowsHookEx(g_pTangram->m_hCBTHook);
				g_pTangram->m_hCBTHook = nullptr;
			}
		}
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);

		if (g_pTangram->m_hMainWnd == NULL &&
			g_pTangram->m_bChromeNeedClosed == false &&
			g_pTangram->m_mapBrowserWnd.size() == 1 &&
			::IsWindow(g_pTangram->m_hHostBrowserWnd) &&
			g_pTangram->m_nAppID == 10000 &&
			g_pTangram->m_bEclipse == false)
		{
			::SendMessageW(g_pTangram->m_hHostBrowserWnd, WM_CLOSE, 0, 0);
		}
		return lRes;
	}

	LRESULT ChromePlus::CBrowserWnd::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&) {
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;
		if (g_pTangram->m_pCLRProxy)
		{
			g_pTangram->m_pCLRProxy->PreWindowPosChanging(m_hWnd, lpwndpos, 0);
		}
		HWND hPWnd = ::GetParent(m_hWnd);
		if (::IsWindow(hPWnd))
		{
			WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;
			RECT rc;
			::GetClientRect(hPWnd, &rc);
			lpwndpos->x = -12;
			lpwndpos->y = -6 - m_heightfix;
			lpwndpos->cx = rc.right + 24;
			lpwndpos->cy = rc.bottom + 18 + 3 * m_heightfix;
		}
		else if (g_pTangram->m_bOMNIBOXPOPUPVISIBLE)
			::SendMessage(m_hWnd, WM_BROWSERLAYOUT, 0, 2);
		return lRes;
	}

	LRESULT CBrowserWnd::OnBrowserLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
	{
		DefWindowProc(uMsg, wParam, lParam);
		if (g_pTangram->m_bChromeNeedClosed == false && m_pVisibleWebWnd)
		{
			switch (lParam)
			{
			case 1:
			{
				if (m_pBrowser)
				{
					BrowserLayout();
					m_pBrowser->LayoutBrowser();
				}
			}
			break;
			case 2:
			case 3:
			{
				if (wParam == 1)
				{
					if (::IsWindow(m_hDrawWnd) == false) {
						m_hDrawWnd = ::FindWindowEx(m_hWnd, nullptr, _T("Intermediate D3D Window"), nullptr);
					}

					if (::IsWindow(m_hDrawWnd) == false) {
						m_hDrawWnd = ::FindWindowEx(m_hWnd, nullptr, _T("Intermediate Software Window"), nullptr);
					}
				}
				else if (m_pBrowser)
				{
					if (lParam == 2 && g_pTangram->m_bOMNIBOXPOPUPVISIBLE)
					{
						BrowserLayout();
					}
					::SetParent(m_pVisibleWebWnd->m_hExtendWnd, m_hWnd);
					::InvalidateRect(m_hWnd, nullptr, true);
					m_pBrowser->LayoutBrowser();
					m_bTabChange = false;
				}
			}
			break;
			}
		}
		return 0;
	}

	void CBrowserWnd::OnFinalMessage(HWND hWnd) {
		CWindowImpl::OnFinalMessage(hWnd);
		delete this;
	}

	STDMETHODIMP CBrowserWnd::AddURLs(BSTR bstrURLs)
	{
		if (m_pVisibleWebWnd)
		{
			CString strDisposition = _T("");
			strDisposition.Format(_T("%d"), NEW_BACKGROUND_TAB);
			if (m_pVisibleWebWnd->m_pChromeRenderFrameHost)
			{
				IPCMsg msg;
				msg.m_strId = L"ADD_URL";
				msg.m_strParam1 = OLE2T(bstrURLs);
				msg.m_strParam2 = strDisposition;
				m_pVisibleWebWnd->m_pChromeRenderFrameHost->SendTangramMessage(&msg);
			}
		}
		return S_OK;
	}

	STDMETHODIMP CBrowserWnd::OpenURL(BSTR bstrURL, BrowserWndOpenDisposition nDisposition, BSTR bstrKey, BSTR bstrXml)
	{
		if (m_pVisibleWebWnd)
		{
			CString strDisposition = _T("");
			strDisposition.Format(_T("%d"), nDisposition);
			if (m_pVisibleWebWnd->m_pChromeRenderFrameHost)
			{
				IPCMsg msg;
				msg.m_strId = L"OPEN_URL";
				msg.m_strParam1 = OLE2T(bstrURL);
				msg.m_strParam2 = strDisposition;
				m_pVisibleWebWnd->m_pChromeRenderFrameHost->SendTangramMessage(&msg);
			}
		}
		return S_OK;
	}
}  // namespace ChromePlus
