#include "../stdafx.h"
#include "../dllmain.h"
#include "Gui.h"
#include "../Object/RefObject.h"

namespace Gui
{
    // Document

    Document::Document()
    {
        m_pNativeHandle = theApp.m_pTangramImpl->m_pObjectFactory->CreateDocument();
    }

    void Document::Load(String^ xcml)
    {
        BSTR bstrXcml = STRING2BSTR(xcml);
        CString strXcml = OLE2T(bstrXcml);
        ::SysFreeString(bstrXcml);
        m_pNativeHandle->Load(strXcml);
    }

    void Document::CreateWnd(IntPtr^ hPWnd)
    {
        HWND hWnd = (HWND)hPWnd->ToPointer();
        m_pNativeHandle->CreateWnd(hWnd);
    }

}