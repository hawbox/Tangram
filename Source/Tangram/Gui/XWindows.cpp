#include "../stdafx.h"
#include "XWindows.h"
#include "../TangramApp.h"

extern CTangramApp theApp;

namespace Gui
{
    XWindows::XWindows()
    {
        RegisterWindow(_T("TangramInvisibleWnd"));
    }

    HWND XWindows::CreateInvisibleWnd(HWND hPWnd)
    {
        HWND hWnd = ::CreateWindowEx(
            0,
            _T("TangramInvisibleWnd"),
            _T(""),
            WS_CHILD,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            hPWnd,
            NULL,
            theApp.m_hInstance,
            NULL
        );
        return hWnd;
    }

    LRESULT CALLBACK DefaultWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void XWindows::RegisterWindow(LPWSTR lpszClassName)
    {
        WNDCLASS wc = {};
        wc.lpfnWndProc = DefaultWindowProc;
        wc.hInstance = theApp.m_hInstance;
        wc.lpszClassName = lpszClassName;
        ::RegisterClass(&wc);
    }
}