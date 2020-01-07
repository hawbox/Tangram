// CRichEditView2.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CRichEditView2.h"


// CRichEditView2

IMPLEMENT_DYNCREATE(CRichEditView2, CRichEditView)

CRichEditView2::CRichEditView2()
{

}

CRichEditView2::~CRichEditView2()
{
}

BEGIN_MESSAGE_MAP(CRichEditView2, CRichEditView)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CRichEditView2 diagnostics

#ifdef _DEBUG
void CRichEditView2::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CRichEditView2::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRichEditView2 message handlers


HBRUSH CRichEditView2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CRichEditView::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    pDC->SetBkColor(RGB(255, 0, 0));
    pDC->SetTextColor(RGB(255, 0, 0));

    // TODO:  Return a different brush if the default is not desired
    return hbr;
}
