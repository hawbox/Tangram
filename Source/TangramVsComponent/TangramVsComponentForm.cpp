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

// TangramVsComponentForm.cpp : implementation file
//

#include "pch.h"
#include "resource.h"
#include "dllmain.h"
#include "TangramVsComponentForm.h"

using namespace TangramCommon;

// TangramVsComponentForm

IMPLEMENT_DYNCREATE(TangramVsComponentForm, CFormView)

TangramVsComponentForm::TangramVsComponentForm()
	: CFormView(IDD_ITANGRAMVSCOMPONENTFORMVIEW)
{

}

TangramVsComponentForm::~TangramVsComponentForm()
{
}

void TangramVsComponentForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(TangramVsComponentForm, CFormView)
	ON_BN_CLICKED(IDC_BTN_HOWTO, &TangramVsComponentForm::OnBnClickedBtnHowto)
END_MESSAGE_MAP()


// TangramVsComponentForm diagnostics

#ifdef _DEBUG
void TangramVsComponentForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void TangramVsComponentForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

BOOL TangramVsComponentForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

// TangramVsComponentForm message handlers


void TangramVsComponentForm::OnBnClickedBtnHowto()
{
	if (g_pTangramImpl&& g_pTangramImpl->m_pCLRProxy)
	{
		IWndNode* pNode = nullptr;
		theApp.m_pTangram->GetNodeFromHandle((__int64)m_hWnd, &pNode);
		g_pTangramImpl->m_pCLRProxy->TangramAction(_T("ExternAction:test"), pNode);
	}
}
