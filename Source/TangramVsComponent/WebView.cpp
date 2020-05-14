// WebView.cpp : implementation file
//

#include "pch.h"
#include "WebView.h"

IMPLEMENT_DYNCREATE(CWebView, CView)

CWebView::CWebView()
{
	m_hWebBrowser = NULL;
	m_pChromForVSAppObj = nullptr;
}

CWebView::~CWebView()
{
}

BEGIN_MESSAGE_MAP(CWebView, CView)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_MESSAGE(WM_DPICHANGED, OnDpiChanged)
END_MESSAGE_MAP()


LRESULT CWebView::OnDpiChanged(WPARAM wParam, LPARAM lParam)
{
	return CWnd::DefWindowProc(WM_DPICHANGED, wParam, lParam);
}

// CWebView drawing

void CWebView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CWebView diagnostics

#ifdef _DEBUG
void CWebView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CWebView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWebView message handlers

int CWebView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (m_pChromForVSAppObj == nullptr)
	{
		CComPtr<IChromForVSAppObj> pDisp;
		pDisp.CoCreateInstance(CComBSTR("WebRuntimeForVs.AppObj.1"));
		if (pDisp)
		{
			m_pChromForVSAppObj = pDisp.Detach();
			m_pChromForVSAppObj->AddRef();
			CComPtr<IChromeWebBrowser> pWebBrowser;
			m_pChromForVSAppObj->CreateBrowser((__int64)m_hWnd, CComBSTR("http://www.csdn.net|c:/index.html|http://www.tangram.dev"), &pWebBrowser);
			if (pWebBrowser)
			{
				__int64 hWnd = 0;
				m_pChromForVSAppObj->GetCreatingBrowserWnd(&hWnd);
				m_hWebBrowser = (HWND)hWnd;
			}
		}
	}
	return 0;
}


void CWebView::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
	if (::IsWindow(m_hWebBrowser))
	{
		::SetWindowPos(m_hWebBrowser, NULL, 0, 0, lpwndpos->cx, lpwndpos->cy, SWP_FRAMECHANGED);
	}
}
