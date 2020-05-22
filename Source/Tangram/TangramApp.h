/********************************************************************************
*					Tangram Library - version 10.0.0							*
*********************************************************************************
* Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.				*
*
* THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
* BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
* WRITTEN CONSENT OF TANGRAM TEAM.
*
* THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
* OUTLINED IN THE TANGRAM LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
********************************************************************************/

// TangramApp.h : DLL

#pragma once
#include <jni.h>

namespace ChromePlus
{
	class CBrowserWnd;
	class CHtmlWnd;
}

using namespace ChromePlus;

typedef HRESULT(__stdcall* TangramCLRCreateInstance)(REFCLSID clsid, REFIID riid, LPVOID* ppInterface);

class CHelperWnd :
	public CWindowImpl<CHelperWnd, CWindow>
{
public:
	CHelperWnd(void)
	{
		m_strID = _T("");
	};

	~CHelperWnd(void) {};

	CString m_strID;
	DECLARE_WND_CLASS(_T("Tangram Helper Window Class"))
	BEGIN_MSG_MAP(CHelperWnd)
	END_MSG_MAP()
	void OnFinalMessage(HWND hWnd);
};

class CWebHelperWnd :
	public CWindowImpl<CWebHelperWnd, CWindow>
{
public:
	CWebHelperWnd(void)
	{
		m_hWebHost = nullptr;
	};

	~CWebHelperWnd(void) {};

	HWND m_hWebHost;
	BEGIN_MSG_MAP(CHelperWnd)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnWindowPosChanging)
	END_MSG_MAP()
	void OnFinalMessage(HWND hWnd);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

class CGenericPaneWnd :
	public CWindowImpl<CGenericPaneWnd, CWindow>
{
public:
	CGenericPaneWnd(void)
	{
		m_hChild = NULL;
	};

	~CGenericPaneWnd(void) {};
	HWND m_hChild;
	CCompositor* m_pCompositor = nullptr;
	BEGIN_MSG_MAP(CGenericPaneWnd)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_TANGRAMMSG, OnTangramMsg)
		MESSAGE_HANDLER(WM_TANGRAMDATA, OnTangramData)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanging)
	END_MSG_MAP()
	void OnFinalMessage(HWND hWnd);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTangramMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTangramData(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

class CTangramApp :
	public CWinApp,
	public CComObjectRootBase,
	public CComCoClass<CTangramApp>,
	public CAtlDllModuleT< CTangramApp >
{
public:
	CTangramApp();
	~CTangramApp();

	bool				m_bHostCLR;

	CString GetFileVer();
	void SetHook(DWORD ThreadID);

	static LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK TangramWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	static LRESULT CALLBACK TangramMsgWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	static LRESULT CALLBACK TangramExtendedWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

	static LRESULT CALLBACK ForegroundIdleProc(int nCode, WPARAM wParam, LPARAM lParam);

	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

	static HRESULT WINAPI CreateInstance(void* pv, REFIID riid, LPVOID* ppv);

	DECLARE_LIBID(LIBID_Tangram)

private:
	int ExitInstance();
	BOOL InitInstance();

	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
};

TANGRAM_OBJECT_ENTRY_AUTO(CLSID_Tangram, CTangramApp)

extern CTangramApp theApp;
extern CTangram* g_pTangram;
