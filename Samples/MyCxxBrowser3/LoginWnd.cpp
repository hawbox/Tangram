// LoginWnd.cpp : implementation file
//

#include "pch.h"
#include "resource.h"
#include "LoginWnd.h"


// CLoginWnd

IMPLEMENT_DYNCREATE(CLoginWnd, CFormView)

CLoginWnd::CLoginWnd()
	: CFormView(IDD_CLoginWnd)
{
}

CLoginWnd::~CLoginWnd()
{
}

void CLoginWnd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoginWnd, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginWnd::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLoginWnd diagnostics

#ifdef _DEBUG
void CLoginWnd::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLoginWnd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLoginWnd message handlers

void CLoginWnd::OnBnClickedButton1()
{
	IWndNode* pThisNode = nullptr;
	g_pTangram->GetNodeFromHandle((LONGLONG)m_hWnd, &pThisNode);
	if (pThisNode != nullptr)
	{
		CString strUsername;
		GetDlgItemTextW(IDC_EDIT1, strUsername);
		BSTR bstrUsername = strUsername.AllocSysString();
		BSTR bstrMsgId;
		pThisNode->SendIPCMessage(BSTR(_T("web")), bstrUsername, BSTR(_T("")), BSTR(_T("")), &bstrMsgId);
		::SysFreeString(bstrUsername);
		::SysFreeString(bstrMsgId);
	}
}


