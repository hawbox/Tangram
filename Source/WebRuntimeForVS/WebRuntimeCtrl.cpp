// WebRuntimeCtrl.cpp : Implementation of CWebRuntimeCtrl
#include "stdafx.h"
#include "WebRuntimeCtrl.h"
#include "WebRuntimeForVS.h"

// CWebRuntimeCtrl
CWebRuntimeCtrl::CWebRuntimeCtrl()
{
	m_bWindowOnly = true;
}

LRESULT CWebRuntimeCtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lr = DefWindowProc(uMsg, wParam, lParam);
	if (theApp.m_pTangramImpl->m_pBrowserFactory)
	{
		CComPtr<IChromeWebBrowser> pWebBrowser;
		m_hBrowser = theApp.m_pTangramImpl->m_pBrowserFactory->CreateBrowser(m_hWnd, _T("http://www.csdn.net|c:/index.html|http://www.tangram.dev|"));
	}

	return lr;
}

LRESULT CWebRuntimeCtrl::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;
	if (::IsWindow(m_hBrowser))
	{
		::SetWindowPos(m_hBrowser, NULL, 0, 0, lpwndpos->cx, lpwndpos->cy, SWP_NOACTIVATE | SWP_NOREDRAW);
	}
	LRESULT hr = DefWindowProc(uMsg, wParam, lParam);
	return hr;
}


