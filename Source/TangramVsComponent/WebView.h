#pragma once


// CWebView view

class CWebView : public CView
{
	DECLARE_DYNCREATE(CWebView)

protected:
	CWebView();           // protected constructor used by dynamic creation
	virtual ~CWebView();
	HWND m_hWebBrowser;
	IChromeWebBrowser* m_pChromeWebBrowser = nullptr;
public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	//IChromForVSAppObj* m_pChromForVSAppObj;
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg LRESULT OnDpiChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};


