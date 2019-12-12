// MyFormView.cpp : implementation file
//

#include "pch.h"
#include "MyCxxBrowser.h"
#include "MyFormView.h"


// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView(IDD_CMyFormView)
{

}

CMyFormView::~CMyFormView()
{
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyFormView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyFormView::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyFormView diagnostics

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFormView message handlers


void CMyFormView::OnBnClickedButton1()
{
	IChromeWebBrowser* pChromeWebBrowser = theApp.m_pTangramImpl->GetHostBrowser(m_hWnd);
	if (pChromeWebBrowser != nullptr)
	{
		pChromeWebBrowser->OpenURL(BSTR(_T("https://demo.tangram.dev/mfc.html")),
			BrowserWndOpenDisposition::NEW_FOREGROUND_TAB, BSTR(_T("")), BSTR(_T("")));
	}
}


void CMyFormView::OnBnClickedButton2()
{
	IChromeWebBrowser* pChromeWebBrowser = theApp.m_pTangramImpl->GetHostBrowser(m_hWnd);
	if (pChromeWebBrowser != nullptr)
	{
		pChromeWebBrowser->OpenURL(BSTR(_T("https://demo.tangram.dev/mfc_ipc.html")),
			BrowserWndOpenDisposition::NEW_FOREGROUND_TAB, BSTR(_T("")), BSTR(_T("")));
	}
}
