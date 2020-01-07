// CXView.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CXView.h"


// CXView

IMPLEMENT_DYNCREATE(CXView, CView)

CXView::CXView()
{

}

CXView::~CXView()
{
}

BEGIN_MESSAGE_MAP(CXView, CView)
    ON_WM_CTLCOLOR()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CXView drawing

void CXView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CXView diagnostics

#ifdef _DEBUG
void CXView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXView message handlers


HBRUSH CXView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    pDC->SetBkColor(RGB(255, 0, 0));
    pDC->SetTextColor(RGB(255, 0, 0));

    // TODO:  Return a different brush if the default is not desired
    return hbr;
}


BOOL CXView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    CBrush brush;
    brush.CreateSolidBrush(RGB(255, 0, 0));
    CRect rect;
    GetClientRect(&rect);
    pDC->FillRect(&rect, &brush);
    return TRUE;
    //return CView::OnEraseBkgnd(pDC);
}


void CXView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: Add your message handler code here
                       // Do not call CView::OnPaint() for painting messages
}
