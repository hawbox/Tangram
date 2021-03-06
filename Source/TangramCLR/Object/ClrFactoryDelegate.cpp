#include "../stdafx.h"
#include "ClrFactoryDelegate.h"

#include "RefObject.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Reflection;

namespace RefObject
{
    CString ClrFactoryDelegate::GetName()
    {
        return L"Clr";
    }

    uint8_t ClrFactoryDelegate::GetHeaderOfHandle()
    {
        return 2;
    }

    IRefObject* ClrFactoryDelegate::Create(Gui::INode* pNode)
    {
        return nullptr;
    }

    void ClrFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod)
    {
    }

    void ClrFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams)
    {
        Handle nHandle = pObj->GetHandle();
        uint64_t nRawHandle = nHandle.RawHandle;
        IntPtr pUnk((long long)nRawHandle);
        Object^ obj = Marshal::GetObjectForIUnknown(pUnk);
        Type^ type = obj->GetType();
        BSTR bstrMethod = strMethod.AllocSysString();
        String^ method = BSTR2STRING(bstrMethod);
        ::SysFreeString(bstrMethod);
        MethodInfo^ mi = type->GetMethod(method);
        if (mi != nullptr)
        {
            List<Object^>^ params = gcnew List<Object^>();
            for (int i = 0; i < pParams->Count(); i++)
            {
                CString strVal = pParams->GetParam(i);
                BSTR bstrVal = strVal.AllocSysString();
                String^ val = BSTR2STRING(bstrVal);
                ::SysFreeString(bstrVal);
                params->Add(val);
            }
            mi->Invoke(obj, params->ToArray());
        }
    }

    void ClrFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
    {
    }
}