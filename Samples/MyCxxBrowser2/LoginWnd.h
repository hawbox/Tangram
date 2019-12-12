#pragma once



// CLoginWnd form view

class CLoginWnd : public CFormView
{
	DECLARE_DYNCREATE(CLoginWnd)

protected:
	CLoginWnd();           // protected constructor used by dynamic creation
	virtual ~CLoginWnd();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLoginWnd };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


