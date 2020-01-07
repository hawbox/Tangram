#include "../stdafx.h"
#include "Grid.h"

namespace Gui
{
    // HitTest return values (values and spacing between values is important)
    // Had to adopt this because it has module scope 
    enum HitTestValue
    {
        noHit = 0,
        vSplitterBox = 1,
        hSplitterBox = 2,
        bothSplitterBox = 3, // just for keyboard
        vSplitterBar1 = 101,
        vSplitterBar15 = 115,
        hSplitterBar1 = 201,
        hSplitterBar15 = 215,
        splitterIntersection1 = 301,
        splitterIntersection225 = 525
    };

    IMPLEMENT_DYNAMIC(Grid, CSplitterWnd)

    Grid::Grid()
    {
        m_cxBorder = m_cyBorder = 0;
    }

    Grid::~Grid()
    {
    }


    BEGIN_MESSAGE_MAP(Grid, CSplitterWnd)
        ON_WM_PAINT()
        ON_WM_ERASEBKGND()
        ON_WM_NCHITTEST()
        ON_WM_SIZE()
    END_MESSAGE_MAP()

    CWnd* Grid::GetActivePane(int* pRow, int* pCol)
    {
        ASSERT_VALID(this);
        CWnd* pView = GetFocus();
        // make sure the pane is a child pane of the splitter
        if (pView != NULL && !IsChildPane(pView, pRow, pCol))
            pView = NULL;
        return pView;
    }

    void Grid::SetActivePane(int row, int col, CWnd* pWnd)
    {
        // set the focus to the pane
        CWnd* pPane = pWnd == NULL ? GetPane(row, col) : pWnd;
        pPane->SetFocus();
    }

    void Grid::StartTracking(int ht)
    {
        ASSERT_VALID(this);
        if (ht == noHit)
            return;
        // GetHitRect will restrict 'm_rectLimit' as appropriate
        GetInsideRect(m_rectLimit);
        if (ht >= splitterIntersection1 && ht <= splitterIntersection225)
        {
            // split two directions (two tracking rectangles)
            int row = (ht - splitterIntersection1) / 15;
            int col = (ht - splitterIntersection1) % 15;
            GetHitRect(row + vSplitterBar1, m_rectTracker);
            int yTrackOffset = m_ptTrackOffset.y;
            m_bTracking2 = TRUE;
            GetHitRect(col + hSplitterBar1, m_rectTracker2);
            m_ptTrackOffset.y = yTrackOffset;
        }
        else if (ht == bothSplitterBox)
        {
            // hit on splitter boxes (for keyboard)
            GetHitRect(vSplitterBox, m_rectTracker);
            int yTrackOffset = m_ptTrackOffset.y;
            m_bTracking2 = TRUE;
            GetHitRect(hSplitterBox, m_rectTracker2);
            m_ptTrackOffset.y = yTrackOffset;
            // center it
            m_rectTracker.OffsetRect(0, m_rectLimit.Height() / 2);
            m_rectTracker2.OffsetRect(m_rectLimit.Width() / 2, 0);
        }
        else
        {
            // only hit one bar
            GetHitRect(ht, m_rectTracker);
        }

        // steal focus and capture
        SetCapture();
        SetFocus();
        // make sure no updates are pending
        RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
        // set tracking state and appropriate cursor
        m_bTracking = TRUE;
        OnInvertTracker(m_rectTracker);
        if (m_bTracking2)
            OnInvertTracker(m_rectTracker2);
        m_htTrack = ht;
        SetSplitCursor(ht);
    }

    /////////////////////////////////////////////////////////////////////////////
    // CSplitterWnd command routing 
    BOOL Grid::OnCommand(WPARAM wParam, LPARAM lParam)
    {
        if (CWnd::OnCommand(wParam, lParam))
            return TRUE;
        // route commands to the splitter to the parent frame window
        return GetParent()->SendMessage(WM_COMMAND, wParam, lParam);
    }

    BOOL Grid::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
    {
        if (CWnd::OnNotify(wParam, lParam, pResult))
            return TRUE;
        // route commands to the splitter to the parent frame window
        *pResult = GetParent()->SendMessage(WM_NOTIFY, wParam, lParam);
        return TRUE;
    }

    BOOL Grid::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
    {
        // The code line below is necessary if using CxSplitterWnd in a regular dll
        // AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
        return CWnd::OnWndMsg(message, wParam, lParam, pResult);
    }

    // CxSplitterWnd message handlers

    void Grid::OnPaint()
    {
        CPaintDC dc(this); // device context for painting
                           // TODO: Add your message handler code here
                           // Do not call CSplitterWnd::OnPaint() for painting messages
        OnDraw(&dc);
    }

    void Grid::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
    {
        // TODO: Add your specialized code here and/or call the base class
        if (pDC == NULL)
        {
            CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
        }
        else
        {
            CBrush brush;
            brush.CreateSolidBrush(RGB(0, 255, 0));
            pDC->FillRect(&rect, &brush);
        }
        //CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
    }

    BOOL Grid::OnEraseBkgnd(CDC* pDC)
    {
        // TODO: Add your message handler code here and/or call default

        return TRUE;
        //return CSplitterWnd::OnEraseBkgnd(pDC);
    }

    LRESULT Grid::OnNcHitTest(CPoint point)
    {
        // TODO: Add your message handler code here and/or call default

        return CSplitterWnd::OnNcHitTest(point);
        //return HTNOWHERE;
    }

    void Grid::OnSize(UINT nType, int cx, int cy)
    {
        CSplitterWnd::OnSize(nType, cx, cy);

        // TODO: Add your message handler code here
    }
}
