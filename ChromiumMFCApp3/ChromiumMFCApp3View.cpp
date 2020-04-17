/********************************************************************************
*					Tangram Wizard - version 1.0.0							*
*********************************************************************************
* Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.				*
*
* THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
* BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
* WRITTEN CONSENT OF TANGRAM TEAM.
*
* THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
* OUTLINED IN THE GPL LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
*
********************************************************************************/

// ChromiumMFCApp3View.cpp : implementation of the CChromiumMFCApp3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ChromiumMFCApp3.h"
#endif

#include "ChromiumMFCApp3Doc.h"
#include "ChromiumMFCApp3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChromiumMFCApp3View, CFormView)

BEGIN_MESSAGE_MAP(CChromiumMFCApp3View, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChromiumMFCApp3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CChromiumMFCApp3View

// CChromiumMFCApp3View construction/destruction

CChromiumMFCApp3View::CChromiumMFCApp3View() noexcept
	: CFormView(IDD_CHROMIUMMFCAPP3_FORM)
{
	// TODO: add construction code here

}

CChromiumMFCApp3View::~CChromiumMFCApp3View()
{
}

void CChromiumMFCApp3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CChromiumMFCApp3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	HWND hPWnd = ::GetParent(m_hWnd);
	CWnd* pWnd = CWnd::FromHandlePermanent(hPWnd);
	if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
		ResizeParentToFit();
}

BOOL CChromiumMFCApp3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}



// CChromiumMFCApp3View printing

void CChromiumMFCApp3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChromiumMFCApp3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChromiumMFCApp3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChromiumMFCApp3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChromiumMFCApp3View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CChromiumMFCApp3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChromiumMFCApp3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CChromiumMFCApp3View diagnostics

#ifdef _DEBUG
void CChromiumMFCApp3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CChromiumMFCApp3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChromiumMFCApp3Doc* CChromiumMFCApp3View::GetDocument() const // non-debug version is inline
{
	if (m_pDocument)
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChromiumMFCApp3Doc)));
	}
	return (CChromiumMFCApp3Doc*)m_pDocument;
}
#endif //_DEBUG


// CChromiumMFCApp3View message handlers


BOOL CChromiumMFCApp3View::PreTranslateMessage(MSG* pMsg)
{
	if (IsDialogMessage(pMsg))
		return true;

	return CFormView::PreTranslateMessage(pMsg);
}
