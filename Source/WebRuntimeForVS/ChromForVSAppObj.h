// ChromForVSAppObj.h : Declaration of the CChromForVSAppObj

#pragma once
#include "resource.h"       // main symbols



#include "WebRuntimeForVS_h.h"
#include "_IChromForVSAppObjEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CChromForVSAppObj

class ATL_NO_VTABLE CChromForVSAppObj :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CChromForVSAppObj, &CLSID_ChromForVSAppObj>,
	public IConnectionPointContainerImpl<CChromForVSAppObj>,
	public CProxy_IChromForVSAppObjEvents<CChromForVSAppObj>,
	public IDispatchImpl<IChromForVSAppObj, &IID_IChromForVSAppObj, &LIBID_WebRuntimeForVS, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CChromForVSAppObj()
	{
		m_hCreatingWnd = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(313)

DECLARE_NOT_AGGREGATABLE(CChromForVSAppObj)

BEGIN_COM_MAP(CChromForVSAppObj)
	COM_INTERFACE_ENTRY(IChromForVSAppObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CChromForVSAppObj)
	CONNECTION_POINT_ENTRY(__uuidof(_IChromForVSAppObjEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	HWND m_hCreatingWnd;
public:
	 HRESULT GetCreatingBrowserWnd(LONGLONG* retHandle);
	 HRESULT CreateBrowser(ULONGLONG hParentWnd, BSTR strUrls, IChromeWebBrowser** ppRet);
};

OBJECT_ENTRY_AUTO(__uuidof(ChromForVSAppObj), CChromForVSAppObj)
