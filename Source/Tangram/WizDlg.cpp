
// WizDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WizDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizDlg dialog



CWizDlg::CWizDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_WIZ_DIALOG, pParent)
{
}

void CWizDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WIZ, m_WizListView);
	DDX_Control(pDX, IDOK, m_OKBtn);
}

BEGIN_MESSAGE_MAP(CWizDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WIZ, &CWizDlg::OnLvnItemchangedListWiz)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_WIZ, &CWizDlg::OnLvnItemActivateListWiz)
END_MESSAGE_MAP()


// CWizDlg message handlers

BOOL CWizDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWizDlg::OnPaint()
{
	if (IsIconic())
	{
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWizDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWizDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);
	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	::SetWindowPos(m_WizListView.m_hWnd, HWND_BOTTOM, 10, 10, rc.right-20, rc.bottom-60, SWP_NOACTIVATE);
	::SetWindowPos(m_OKBtn.m_hWnd, HWND_BOTTOM, rc.right - 100, rc.bottom - 40, 90, 30, SWP_NOACTIVATE);
	// TODO: Add your message handler code here
}


void CWizDlg::OnLvnItemchangedListWiz(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CWizDlg::OnLvnItemActivateListWiz(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
