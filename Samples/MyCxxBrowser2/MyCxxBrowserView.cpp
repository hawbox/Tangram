
// MyCxxBrowserView.cpp : implementation of the CMyCxxBrowserView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyCxxBrowser.h"
#endif

#include "MyCxxBrowserDoc.h"
#include "MyCxxBrowserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCxxBrowserView

IMPLEMENT_DYNCREATE(CMyCxxBrowserView, CView)

BEGIN_MESSAGE_MAP(CMyCxxBrowserView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyCxxBrowserView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMyCxxBrowserView construction/destruction

CMyCxxBrowserView::CMyCxxBrowserView() noexcept
{
	// TODO: add construction code here

}

CMyCxxBrowserView::~CMyCxxBrowserView()
{
}

BOOL CMyCxxBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyCxxBrowserView drawing

void CMyCxxBrowserView::OnDraw(CDC* /*pDC*/)
{
	CMyCxxBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMyCxxBrowserView printing


void CMyCxxBrowserView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyCxxBrowserView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCxxBrowserView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCxxBrowserView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMyCxxBrowserView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyCxxBrowserView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyCxxBrowserView diagnostics

#ifdef _DEBUG
void CMyCxxBrowserView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCxxBrowserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCxxBrowserDoc* CMyCxxBrowserView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCxxBrowserDoc)));
	return (CMyCxxBrowserDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyCxxBrowserView message handlers
