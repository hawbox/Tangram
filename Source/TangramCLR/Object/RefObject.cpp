#include "../stdafx.h"
#include "../dllmain.h"
#include "RefObject.h"

namespace RefObject
{
    // RefObjectParams

    RefObjectParams::RefObjectParams()
    {
        m_pNativeHandle = theApp.m_pTangramImpl->m_pObjectFactory->CreateParams();
    }

    RefObjectParams::RefObjectParams(IRefObjectParams* params)
    {
        m_pNativeHandle = params;
    }

    void RefObjectParams::AddParam(String^ param)
    {
        BSTR bstrParam = STRING2BSTR(param);
        CString strParam = OLE2T(bstrParam);
        m_pNativeHandle->AddParam(strParam);
    }

    String^ RefObjectParams::GetParam(unsigned int index)
    {
        CString strParam = m_pNativeHandle->GetParam(index);
        BSTR bstrParam = strParam.AllocSysString();
        String^ param = BSTR2STRING(bstrParam);
        ::SysFreeString(bstrParam);
        return param;
    }

    unsigned long long RefObjectParams::Count()
    {
        return m_pNativeHandle->Count();
    }

    // RefObjectEventListener

    RefObjectEventListenerWrapper::RefObjectEventListenerWrapper(ICLRRefObjectEventListener^ evtListener)
    {
        m_pCLRHandle = evtListener;
    }

    void RefObjectEventListenerWrapper::OnEventHandle(CString strEventType, IRefObjectParams* pParams)
    {
        BSTR bstrEventType = strEventType.AllocSysString();
        String^ eventType = BSTR2STRING(bstrEventType);
        RefObjectParams^ params = gcnew RefObjectParams(pParams);
        m_pCLRHandle->OnEventHandle(eventType, params);
        ::SysFreeString(bstrEventType);
    }

    // RefObjectCallback

    RefObjectCallbackWrapper::RefObjectCallbackWrapper(ICLRRefObjectCallback^ callback)
    {
        m_pCLRHandle = callback;
    }

    void RefObjectCallbackWrapper::Invoke(IRefObject* pObj, IRefObjectParams* pParams)
    {
        RefObject^ obj = nullptr;
        if (pObj != nullptr)
        {
            Handle nHandle = pObj->GetHandle();
            obj = gcnew RefObject(nHandle);
        }
        RefObjectParams^ params = gcnew RefObjectParams(pParams);
        m_pCLRHandle->Invoke(obj, params);
    }

    // RefObject

    RefObject::RefObject(Handle nHandle)
    {
        m_pNativeHandle = nHandle;
    }

    String^ RefObject::GetFactoryName()
    {
        CString strFactoryName = m_pNativeHandle->GetFactoryName();
        BSTR bstrFactoryName = strFactoryName.AllocSysString();
        String^ factoryName = BSTR2STRING(bstrFactoryName);
        ::SysFreeString(bstrFactoryName);
        return factoryName;
    }

    Handle RefObject::GetHandle()
    {
        return m_pNativeHandle->GetHandle();
    }

    void RefObject::Invoke(String^ method, RefObjectParams^ params, ICLRRefObjectCallback^ callback)
    {
        BSTR bstrMethod = STRING2BSTR(method);
        CString strMethod = OLE2T(bstrMethod);
        IRefObjectParams* pParams = params->m_pNativeHandle;
        RefObjectCallbackWrapper* pCallbackWrapper = new RefObjectCallbackWrapper(callback);
        m_pNativeHandle->Invoke(strMethod, pParams, pCallbackWrapper);
    }
}
