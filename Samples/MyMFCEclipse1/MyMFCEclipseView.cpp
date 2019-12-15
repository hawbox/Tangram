
// MyMFCEclipseView.cpp : implementation of the CMyMFCEclipseView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyMFCEclipse.h"
#endif

#include "MyMFCEclipseDoc.h"
#include "MyMFCEclipseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFCEclipseView

IMPLEMENT_DYNCREATE(CMyMFCEclipseView, CView)

BEGIN_MESSAGE_MAP(CMyMFCEclipseView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyMFCEclipseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMyMFCEclipseView construction/destruction

CMyMFCEclipseView::CMyMFCEclipseView() noexcept
{
	// TODO: add construction code here

}

CMyMFCEclipseView::~CMyMFCEclipseView()
{
}

BOOL CMyMFCEclipseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyMFCEclipseView drawing

void CMyMFCEclipseView::OnDraw(CDC* /*pDC*/)
{
	CMyMFCEclipseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMyMFCEclipseView printing


void CMyMFCEclipseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyMFCEclipseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyMFCEclipseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyMFCEclipseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMyMFCEclipseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyMFCEclipseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyMFCEclipseView diagnostics

#ifdef _DEBUG
void CMyMFCEclipseView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMFCEclipseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMFCEclipseDoc* CMyMFCEclipseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFCEclipseDoc)));
	return (CMyMFCEclipseDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFCEclipseView message handlers
