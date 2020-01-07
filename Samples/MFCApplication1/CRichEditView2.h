#pragma once


// CRichEditView2 view

class CRichEditView2 : public CRichEditView
{
	DECLARE_DYNCREATE(CRichEditView2)

protected:
	CRichEditView2();           // protected constructor used by dynamic creation
	virtual ~CRichEditView2();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


