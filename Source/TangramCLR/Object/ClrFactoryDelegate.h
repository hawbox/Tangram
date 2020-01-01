#pragma once

#include <stdint.h>
#include "../CommonFile/IRefObject.h"

namespace RefObject
{
    class ClrFactoryDelegate : public IFactoryDelegate
    {
    public:
        ClrFactoryDelegate() {};
        virtual ~ClrFactoryDelegate() {};

        CString GetName() override;
        uint8_t GetHeaderOfHandle() override;
        IRefObject* Create(CString strConstructString) override;

        void Invoke(IRefObject* pObj, CString strMethod) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) override;
    };
}