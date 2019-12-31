#pragma once

#include "../CommonFile/IRefObject.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace RefObject
{
    ref class RefObjectParams;
    ref class RefObjectEventListener;
    ref class RefObjectCallback;
    ref class RefObject;

    public ref class RefObjectParams
    {
    public:
        RefObjectParams();
        RefObjectParams(IRefObjectParams* params);
        ~RefObjectParams() {};

        void AddParam(String^ param);
        String^ GetParam(unsigned int index);
        unsigned long long Count();

        IRefObjectParams* m_pNativeHandle;
    };

    public interface class ICLRRefObjectEventListener
    {
    public:
        void OnEventHandle(String^ eventType, RefObjectParams^ params);
    };

    public class RefObjectEventListenerWrapper : public IRefObjectEventListener
    {
    public:
        RefObjectEventListenerWrapper(ICLRRefObjectEventListener^ evtListener);
        ~RefObjectEventListenerWrapper() {};

        void OnEventHandle(CString strEventType, IRefObjectParams* pParams) override;

    protected:
        gcroot<ICLRRefObjectEventListener^> m_pCLRHandle;
    };

    public interface class ICLRRefObjectCallback
    {
    public:
        void Invoke(RefObject^ obj, RefObjectParams^ params);
    };

    public class RefObjectCallbackWrapper : public IRefObjectCallback
    {
    public:
        RefObjectCallbackWrapper(ICLRRefObjectCallback^ callback);
        ~RefObjectCallbackWrapper() {};

        void Invoke(IRefObject* pObj, IRefObjectParams* pParams) override;

    protected:
        gcroot<ICLRRefObjectCallback^> m_pCLRHandle;
    };

    public ref class RefObject
    {
    public:
        RefObject(IRefObject* pObj);
        ~RefObject() {};

        String^ GetFactoryName();
        Handle GetHandle();
        void Invoke(String^ method, RefObjectParams^ params, ICLRRefObjectCallback^ callback);

        IRefObject* m_pNativeHandle;
    };
}

