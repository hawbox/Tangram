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
