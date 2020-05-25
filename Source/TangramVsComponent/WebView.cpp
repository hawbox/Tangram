// WebView.cpp : implementation file
//

#include "pch.h"
#include "WebView.h"
#include "dllmain.h"

IMPLEMENT_DYNCREATE(CWebView, CView)

CWebView::CWebView()
{
	m_hWebBrowser = NULL;
	//m_pChromForVSAppObj = nullptr;
}

CWebView::~CWebView()
{
}

BEGIN_MESSAGE_MAP(CWebView, CView)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_MESSAGE(WM_DPICHANGED, OnDpiChanged)
	ON_WM_SIZE()
	ON_WM_DESTROY()
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
	CComBSTR bstrUrl;
	if (theApp.m_pTangram)
	{
		IWndNode* pNode = nullptr;
		theApp.m_pTangram->get_CreatingNode(&pNode);
		pNode->get_Attribute(CComBSTR("url"), &bstrUrl);
		if (theApp.m_pTangramFromWebRuntime && bstrUrl.Length())
		{
			CComPtr<IChromeWebBrowser> pWebBrowser;
			theApp.m_pTangramFromWebRuntime->CreateBrowser((__int64)m_hWnd, bstrUrl, &pWebBrowser);
			if (pWebBrowser)
			{
				m_pChromeWebBrowser = pWebBrowser.Detach();
				m_pChromeWebBrowser->AddRef();
				__int64 hWnd = 0;
				theApp.m_pTangramFromWebRuntime->GetCreatingBrowserWnd(&hWnd);
				m_hWebBrowser = (HWND)hWnd;
			}
		}
	}
	return 0;
}


void CWebView::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	// TODO: Add your message handler code here
	if (::IsWindow(m_hWebBrowser))
	{
		::SetWindowPos(m_hWebBrowser, NULL, 0, 0, lpwndpos->cx, lpwndpos->cy, SWP_NOACTIVATE | SWP_NOREDRAW);
	}
	CView::OnWindowPosChanged(lpwndpos);
}


void CWebView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	// TODO: Add your message handler code here
}


void CWebView::OnDestroy()
{
	m_pChromeWebBrowser->Release();
	::DestroyWindow(m_hWebBrowser);
	CView::OnDestroy();
}
