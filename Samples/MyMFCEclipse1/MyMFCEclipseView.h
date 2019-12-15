
// MyMFCEclipseView.h : interface of the CMyMFCEclipseView class
//

#pragma once


class CMyMFCEclipseView : public CView
{
protected: // create from serialization only
	CMyMFCEclipseView() noexcept;
	DECLARE_DYNCREATE(CMyMFCEclipseView)

// Attributes
public:
	CMyMFCEclipseDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMyMFCEclipseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyMFCEclipseView.cpp
inline CMyMFCEclipseDoc* CMyMFCEclipseView::GetDocument() const
   { return reinterpret_cast<CMyMFCEclipseDoc*>(m_pDocument); }
#endif

