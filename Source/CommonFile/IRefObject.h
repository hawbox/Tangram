#pragma once

namespace RefObject
{
	class IObjectFactory;
	class IRefObjectParams;
	class IRefObjectEventListener;
	class IRefObjectCallback;
	class IRefObjectDelegate;
	class IRefObject;

	typedef struct tagHandle
	{
		uint8_t Header;
		uint64_t RawHandle;
	} Handle;

	class IObjectFactory
	{
	public:
		virtual IRefObject* Create(CString strFactoryName, CString strConstructString) = 0;
		virtual IRefObjectParams* CreateParams() = 0;
	};

	class IRefObjectParams
	{
	public:
		virtual void AddParam(CString strParam) = 0;
		virtual CString GetParam(uint32_t nIndex) = 0;
		virtual size_t Count() = 0;
	};

	class IRefObjectEventListener
	{
	public:
		virtual void OnEventHandle(CString strEventType, IRefObjectParams* pParams) = 0;
	};

	class IRefObjectCallback
	{
	public:
		virtual void Invoke(IRefObject* pObj, IRefObjectParams* pParams) = 0;
	};

	class IRefObjectDelegate
	{
	public:
		virtual void Invoke(IRefObject* pObj, CString strMethod) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) = 0;
	};

	class IRefObject
	{
	public:
		virtual CString GetFactoryName() = 0;
		virtual Handle GetHandle() = 0;
		virtual void AddDelegate(IRefObjectDelegate* pDelegate) = 0;
		virtual IRefObjectDelegate* GetDelegate() = 0;

		virtual void Invoke(CString strMethod) = 0;
		virtual void Invoke(CString strMethod, IRefObjectParams* pParams) = 0;
		virtual void Invoke(CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) = 0;
		virtual void AddEventListener(IRefObjectEventListener* pEvtListener) = 0;
		virtual void RemoveEventListener(IRefObjectEventListener* pEvtListener) = 0;
		virtual void DispatchEvent(CString strEventType, IRefObjectParams* pParams) = 0;
	};
}
