#include "../stdafx.h"
#include "ClrFactoryDelegate.h"

#include "RefObject.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::Runtime::Remoting;
using namespace System::Windows::Forms;

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
        if (pNode->GetTagName().CompareNoCase(_T("formwindow")) == 0)
        {
            CString strAssemblyName = pNode->GetAttribute(_T("assemblyname"));
            CString strTypeName = pNode->GetAttribute(_T("typename"));
            CString strTitle = pNode->GetAttribute(_T("title"));
            ObjectHandle^ objHandle = Activator::CreateInstance(BSTR2STRING(strAssemblyName), BSTR2STRING(strTypeName));
            Object^ obj = objHandle->Unwrap();
            if (obj->GetType()->IsSubclassOf(Form::typeid))
            {
                Form^ pForm = (Form^)obj;
                pForm->Text = BSTR2STRING(strTitle);
                pForm->Show();
                IntPtr pUnk = Marshal::GetIUnknownForObject(pForm);
                uint64_t nRawHandle = (uint64_t)pUnk.ToPointer();
                return m_pObjectFactory->Create(GetName(), nRawHandle);
            }
        }
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
        if (IRefObjectInvokeExtension::typeid->IsAssignableFrom(type))
        {
            IRefObjectInvokeExtension^ pIE = (IRefObjectInvokeExtension^)obj;
            pIE->Invoke(BSTR2STRING(strMethod), gcnew RefObjectParams(pParams));
        }
        else
        {
            // Default behavior
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
    }

    void ClrFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
    {
    }
}