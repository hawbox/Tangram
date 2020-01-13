#pragma once

#include "../CommonFile/IGui.h"

using namespace System;

namespace Gui
{
    public ref class Document
    {
    public:
        Document();
        virtual ~Document() {};

        void Load(String^ pszXcml);
        void CreateWnd(IntPtr^ hPWnd);

        IDocument* m_pNativeHandle;
    };
}