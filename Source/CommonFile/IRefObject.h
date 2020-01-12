#pragma once

namespace Gui
{
	class IDocument;
    class INode;
}

namespace RefObject
{
	class IFactoryDelegate;
	class IObjectFactory;
	class IRefObjectParams;
	class IRefObjectEventListener;
	class IRefObjectCallback;
	class IRefObjectDelegate;
	class IRefObject;

	// Any module should hold a RefObject Handle instead of a RefObject pointer. 
	// RefObject may be deleted, but if using Handle, you can determine whether 
	// the RefObject corresponding to the Handle exists by calling 
	// ObjectFactory::GetObjectFromHandle.
	typedef struct tagHandle
	{
		uint8_t Header;
		uint64_t RawHandle;

		bool operator==(const tagHandle& o) const
		{
			return Header == o.Header && RawHandle == o.RawHandle;
		}

		bool operator<(const tagHandle& o) const
		{
			return Header < o.Header || (Header == o.Header && RawHandle < o.RawHandle);
		}

        bool IsZero()
        {
            return Header == 0 && RawHandle == 0;
        }
	} Handle;

	class IFactoryDelegate
	{
	public:
        IFactoryDelegate() 
        {
            m_pObjectFactory = nullptr;
        };
        virtual ~IFactoryDelegate() {};

        IObjectFactory* m_pObjectFactory;

		virtual CString GetName() = 0;
		virtual uint8_t GetHeaderOfHandle() = 0;
		virtual IRefObject* Create(Gui::INode* pNode) = 0;

		// Invoke method
		virtual void Invoke(IRefObject* pObj, CString strMethod) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) = 0;
	};

	class IObjectFactory
	{
	public:
        IObjectFactory() {};
        virtual ~IObjectFactory() {};

		virtual void AddFactoryDelegate(IFactoryDelegate* pFactoryDelegate) = 0;
		virtual IFactoryDelegate* GetFactoryDelegate(CString strFactoryName) = 0;
		virtual IFactoryDelegate* GetFactoryDelegate(uint8_t nFactoryHeader) = 0;
		virtual IRefObject* GetObjectFromHandle(Handle nHandle) = 0;
		virtual IRefObject* Create(CString strFactoryName, uint64_t nRawHandle) = 0;
		virtual IRefObject* Create(CString strFactoryName, Gui::INode* pNode) = 0;
		virtual bool Delete(CString strFactoryName, uint64_t nRawHandle) = 0;
		virtual IRefObjectParams* CreateParams() = 0;
        virtual void DeleteParams(IRefObjectParams* pParams) = 0;
		virtual uint8_t GenerateNewFactoryId() = 0;
		
		// Gui
		virtual Gui::IDocument* CreateDocument() = 0;
	};

	class IRefObjectParams
	{
	public:
        IRefObjectParams() {};
        virtual ~IRefObjectParams() {};

		virtual void AddParam(CString strParam) = 0;
		virtual CString GetParam(uint32_t nIndex) = 0;
		virtual size_t Count() = 0;
	};

	class IRefObjectEventListener
	{
	public:
        IRefObjectEventListener() {};
        virtual ~IRefObjectEventListener() {};

		virtual void OnEventHandle(CString strEventType, IRefObjectParams* pParams) = 0;
	};

	class IRefObjectCallback
	{
	public:
        IRefObjectCallback() {};
        virtual ~IRefObjectCallback() {};

		virtual void Invoke(IRefObject* pObj, IRefObjectParams* pParams) = 0;
	};

	class IRefObjectDelegate
	{
	public:
        IRefObjectDelegate() {};
        virtual ~IRefObjectDelegate() {};

		virtual void Invoke(IRefObject* pObj, CString strMethod) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) = 0;
		virtual void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) = 0;
	};

	class IRefObject
	{
	public:
        IRefObject() {};
        virtual ~IRefObject() {};

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
