#pragma once

#include "../CommonFile/IRefObject.h"

using namespace RefObject;

namespace ChromePlus
{
    class CHtmlWndDelegate : public IRefObjectDelegate
    {
        void Invoke(IRefObject* pObj, CString strMethod) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) override;
    };
}