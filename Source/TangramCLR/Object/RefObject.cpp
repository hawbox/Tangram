#include "../stdafx.h"
#include "../dllmain.h"
#include "RefObject.h"

namespace RefObject
{
    // RefObjectParams

    RefObjectParams::RefObjectParams()
    {
        m_pNativeHandle = theApp.m_pTangramImpl->m_pObjectFactory->CreateParams();
        m_bIsNativeHandleNeedDeleted = true;
    }

    RefObjectParams::RefObjectParams(IRefObjectParams* params)
    {
        m_pNativeHandle = params;
        m_bIsNativeHandleNeedDeleted = false;
    }

    RefObjectParams::~RefObjectParams()
    {
        this->!RefObjectParams();
    }

    RefObjectParams::!RefObjectParams()
    {
        if (m_bIsNativeHandleNeedDeleted)
        {
            //delete m_pNativeHandle;
        }
    }

    void RefObjectParams::AddParam(String^ param)
    {
        BSTR bstrParam = STRING2BSTR(param);
        CString strParam = OLE2T(bstrParam);
        ::SysFreeString(bstrParam);
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
        ::SysFreeString(bstrEventType);
        RefObjectParams^ params = gcnew RefObjectParams(pParams);
        m_pCLRHandle->OnEventHandle(eventType, params);
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
            obj = gcnew RefObject(gcnew ClrHandle(nHandle));
        }
        RefObjectParams^ params = gcnew RefObjectParams(pParams);
        m_pCLRHandle->Invoke(obj, params);
    }

    // RefObject

    RefObject::RefObject(ClrHandle^ clrHandle)
    {
        m_pNativeHandle = clrHandle;
    }

    String^ RefObject::GetFactoryName()
    {
        IRefObject* pObj = GetNativeObjectFromHandle(m_pNativeHandle);
        if (pObj != nullptr)
        {
            CString strFactoryName = pObj->GetFactoryName();
            BSTR bstrFactoryName = strFactoryName.AllocSysString();
            String^ factoryName = BSTR2STRING(bstrFactoryName);
            ::SysFreeString(bstrFactoryName);
            return factoryName;
        }
        return String::Empty;
    }

    ClrHandle^ RefObject::GetHandle()
    {
        return m_pNativeHandle;
    }

    void RefObject::Invoke(String^ method, RefObjectParams^ params, ICLRRefObjectCallback^ callback)
    {
        BSTR bstrMethod = STRING2BSTR(method);
        CString strMethod = OLE2T(bstrMethod);
        ::SysFreeString(bstrMethod);
        IRefObjectParams* pParams = params->m_pNativeHandle;
        RefObjectCallbackWrapper* pCallbackWrapper = new RefObjectCallbackWrapper(callback);
        IRefObject* pObj = GetNativeObjectFromHandle(m_pNativeHandle);
        if (pObj != nullptr)
        {
            pObj->Invoke(strMethod, pParams, pCallbackWrapper);
        }
    }

    IRefObject* RefObject::GetNativeObjectFromHandle(ClrHandle^ clrHandle)
    {
        Handle nHandle = clrHandle->NativeHandle();
        return theApp.m_pTangramImpl->m_pObjectFactory->GetObjectFromHandle(nHandle);
    }
}
