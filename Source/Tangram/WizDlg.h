
// WizDlg.h : header file
//

#pragma once


// CWizDlg dialog
class CWizDlg : public CDialog
{
// Construction
public:
	CWizDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIZ_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CButton m_OKBtn;
	CListCtrl m_WizListView;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnLvnItemchangedListWiz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemActivateListWiz(NMHDR* pNMHDR, LRESULT* pResult);
};
