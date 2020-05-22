
// WebRuntimeForVS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "WebRuntimeForVS.h"
#include <initguid.h>
#include "WebRuntimeForVS_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebRuntimeForVSApp

BEGIN_MESSAGE_MAP(CWebRuntimeForVSApp, CWinApp)
END_MESSAGE_MAP()


// CWebRuntimeForVSApp construction

CWebRuntimeForVSApp::CWebRuntimeForVSApp() noexcept
{
	m_dwThreadID = ::GetCurrentThreadId();
}

// The one and only CWebRuntimeForVSApp object

CWebRuntimeForVSApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {4e77a03b-254d-4956-90d8-a15be84bbcb8}
static const CLSID clsid =
{0x4e77a03b,0x254d,0x4956,{0x90,0xd8,0xa1,0x5b,0xe8,0x4b,0xbc,0xb8}};

const GUID CDECL _tlid = {0x4e0ce9e8,0xcba3,0x48d4,{0x8a,0xf2,0x54,0x8b,0xf8,0x52,0x36,0xe7}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CWebRuntimeForVSApp initialization

BOOL CWebRuntimeForVSApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	if (!__super::InitInstance())
		return false;

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Note: MDI applications register all server objects without regard
	//  to the /Embedding or /Automation on the command line

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// Register class factories via CoRegisterClassObject().
	if (FAILED(theApp.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.  Unregister
	// typelibrary.  Other unregistration occurs in ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		UpdateRegistryAppId(FALSE);
		UnregisterServer(TRUE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		UpdateRegistryAppId(TRUE);
		RegisterServer(TRUE);
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		return false;
	}

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	return TRUE;
}

CString CWebRuntimeForVSApp::GetNTPXml()
{
	return _T("Default_Mfc.xml");
}

HRESULT CWebRuntimeForVSApp::UpdateRegistry(BOOL bRegister)
{
	return theApp.UpdateRegistryFromResource(IDR_CHROMFORVSAPPOBJ, bRegister);
}

HRESULT CWebRuntimeForVSApp::CreateInstance(void* pv, REFIID riid, LPVOID* ppv)
{
	if (g_pTangram)
	{
		DWORD dwID = ::GetCurrentThreadId();
		if (dwID != theApp.m_dwThreadID)
		{
			IStream* pStream = 0;
			HRESULT hr = ::CoMarshalInterThreadInterfaceInStream(IID_IDispatch, (ITangram*)g_pTangram, &pStream);
			if (hr == S_OK)
			{
				IDispatch* pTarget = nullptr;
				hr = ::CoGetInterfaceAndReleaseStream(pStream, IID_IDispatch, (LPVOID*)&pTarget);
				if (hr == S_OK && pTarget)
					return pTarget->QueryInterface(riid, ppv);
			}
		}
		return g_pTangram->QueryInterface(riid, ppv);
	}
	return S_FALSE;
}

int CWebRuntimeForVSApp::ExitInstance()
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	RevokeClassObjects();
#endif
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CWebRuntimeForVSApp message handlers


