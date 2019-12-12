
// MyCxxBrowser.h : main header file for the MyCxxBrowser application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyCxxBrowserApp:
// See MyCxxBrowser.cpp for the implementation of this class
//

class CMyCxxBrowserApp : public CTangramWinAppEx
{
public:
	CMyCxxBrowserApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CString GetNTPXml();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyCxxBrowserApp theApp;
