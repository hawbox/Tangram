#pragma once

#include "../CommonFile/IGui.h"

namespace Gui
{
    class XWindows : public IXWindows
    {
    public:
        XWindows();
        virtual ~XWindows() {};

        HWND CreateInvisibleWnd(HWND hPWnd) override;
    protected:
        void RegisterWindow(LPWSTR lpszClassName);
    };
}