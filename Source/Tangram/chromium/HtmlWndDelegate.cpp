#include "../stdafx.h"
#include "HtmlWndDelegate.h"
#include "HtmlWnd.h"

namespace ChromePlus
{
    void CHtmlWndDelegate::Invoke(IRefObject* pObj, CString strMethod)
    {

    }

    void CHtmlWndDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams)
    {

    }

    void CHtmlWndDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
    {
        if (strMethod.CompareNoCase(_T("getElementById")) == 0)
        {
            CString strId = pParams->GetParam(0);
            uint64_t nRawHandle = pObj->GetHandle().RawHandle;
            CHtmlWnd* pHtmlWnd = (CHtmlWnd*)nRawHandle;
            pHtmlWnd->getElementById(strId, (RefObjectCallback*)pCallback);
        }
    }
}