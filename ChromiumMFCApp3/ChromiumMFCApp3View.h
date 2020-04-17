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

// ChromiumMFCApp3View.h : interface of the CChromiumMFCApp3View class
//

#pragma once


class CChromiumMFCApp3View : public CFormView
{
protected: // create from serialization only
	CChromiumMFCApp3View() noexcept;
	DECLARE_DYNCREATE(CChromiumMFCApp3View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CHROMIUMMFCAPP3_FORM };
#endif

// Attributes
public:
	CChromiumMFCApp3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo); 

// Implementation
public:
	virtual ~CChromiumMFCApp3View();
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
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // debug version in ChromiumMFCApp3View.cpp
inline CChromiumMFCApp3Doc* CChromiumMFCApp3View::GetDocument() const
   { return reinterpret_cast<CChromiumMFCApp3Doc*>(m_pDocument); }
#endif