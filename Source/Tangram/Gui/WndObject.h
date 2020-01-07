#pragma once

#include "../Object/RefObject.h"

namespace Gui
{
    class WndObject : public ::RefObject::RefObject
    {
    public:
        virtual ~WndObject() {};

        HWND GetHWnd();
    };
}