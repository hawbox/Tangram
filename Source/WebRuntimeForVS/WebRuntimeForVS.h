
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

class CWebRuntimeForVSApp : public CTangramWinApp
{
public:
	CWebRuntimeForVSApp() noexcept;

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// Add by TangramTeam:
	virtual CString GetNTPXml();

	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CWebRuntimeForVSApp theApp;
