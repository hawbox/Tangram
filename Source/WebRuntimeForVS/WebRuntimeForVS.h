
// WebRuntimeForVS.h : main header file for the WebRuntimeForVS application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "WebRuntimeForVS_h.h"


// CWebRuntimeForVSApp:
// See WebRuntimeForVS.cpp for the implementation of this class
//

class CWebRuntimeForVSApp : 
	public CTangramWinApp,
	public CComObjectRootBase,
	public CComCoClass<CWebRuntimeForVSApp>,
	public ATL::CAtlMfcModule
{
public:
	CWebRuntimeForVSApp() noexcept;
	DECLARE_LIBID(LIBID_WebRuntimeForVS);

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// Add by TangramTeam:
	virtual CString GetNTPXml();

	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
	static HRESULT WINAPI CreateInstance(void* pv, REFIID riid, LPVOID* ppv);
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwThreadID;
};

TANGRAM_OBJECT_ENTRY_AUTO(CLSID_ChromForVSAppObj, CWebRuntimeForVSApp)

extern CWebRuntimeForVSApp theApp;
