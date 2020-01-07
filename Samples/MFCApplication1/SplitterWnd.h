#pragma once


// CxSplitterWnd

class CxSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CxSplitterWnd)

public:
	CxSplitterWnd();
	virtual ~CxSplitterWnd();

	virtual void StartTracking(int ht);
	virtual CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	virtual void SetActivePane(int row, int col, CWnd* pWnd = NULL);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


