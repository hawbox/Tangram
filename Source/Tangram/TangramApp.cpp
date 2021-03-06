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
* OUTLINED IN THE GPL LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
********************************************************************************/

// TangramApp.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "TangramApp.h" 
#include <VersionHelpers.h> 
#include <shellscalingapi.h>

#include "fm20.h"
#include "CloudUtilities\TangramDownLoad.h"
#include "VisualStudioPlus\VSAddin.h"
#include "EclipsePlus\EclipseAddin.h"

#include "OfficePlus\WordPlus\WordAddin.h"
#include "OfficePlus\ExcelPlus\ExcelAddin.h"
#include "OfficePlus\VisioPlus\VisioAddin.h"
#include "OfficePlus\AccessPlus\AccessAddin.h"
#include "OfficePlus\OutLookPlus\OutLookAddin.h"
#include "OfficePlus\ProjectPlus\ProjectAddin.h"
#include "OfficePlus\PowerPointPlus\PowerPointAddin.h"

#include "NodeWnd.h"
#include "WndNode.h"
#include "Compositor.h"
#include "Compositor.h"
#include "WPFView.h"
#include <io.h>
#include <stdio.h>

#include "TangramCategory.h"
#include "TangramListView.h"
#include "Psapi.h"

#include "chromium\BrowserWnd.h"
#include "chromium\HtmlWnd.h"

using namespace ChromePlus;
using namespace OfficePlus;
using namespace OfficePlus::WordPlus;
using namespace OfficePlus::ExcelPlus;

// Description  : the unique App object
CTangramApp theApp;
CTangram* g_pTangram = nullptr;

void CHelperWnd::OnFinalMessage(HWND hWnd)
{
	CWindowImpl::OnFinalMessage(hWnd);
	if (m_strID != _T("chromeplus.tangram"))
	{
		auto it = g_pTangram->m_mapRemoteTangramCore.find(m_strID);
		if (it != g_pTangram->m_mapRemoteTangramCore.end())
		{
			ULONG dw = it->second->Release();
			while (dw)
				dw = it->second->Release();
			g_pTangram->m_mapRemoteTangramCore.erase(m_strID);
		}
		auto it2 = g_pTangram->m_mapAppDispDic.find(m_strID);
		if (it2 != g_pTangram->m_mapAppDispDic.end())
		{
			g_pTangram->m_mapAppDispDic.erase(it2);
		}
	}

	delete this;
}

void CWebHelperWnd::OnFinalMessage(HWND hWnd)
{
	CWindowImpl::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CWebHelperWnd::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;
	if (lpwndpos->flags & SWP_HIDEWINDOW)
	{
		ATLTRACE(_T("1\n"));
	}
	else if (lpwndpos->flags & SWP_SHOWWINDOW)
	{
		ATLTRACE(_T("2\n"));
	}
	return lRes;
}

LRESULT CWebHelperWnd::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	if (wParam) {
	}
	else
	{
	}
	return lRes;
}

void CGenericPaneWnd::OnFinalMessage(HWND hWnd)
{
	CWindowImpl::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CGenericPaneWnd::OnTangramMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	switch (lParam)
	{
	case 20200516:
	{
		m_hChild = (HWND)wParam;
		if (g_pTangram->m_pTangramVS&&m_strToolType == _T("TBToolboxPane"))
		{
			CComVariant var;
			g_pTangram->m_pTangramVS->get_AppKeyValue(CComBSTR("appdata"), &var);
			CString strXml = OLE2T(var.bstrVal);
			if (strXml != _T(""))
			{
				CTangramXmlParse m_Parse;
				if (m_Parse.LoadXml(strXml))
				{
					CTangramXmlParse* pVSParse = m_Parse.GetChild(_T("vstoolbox"));
					if (pVSParse)
					{
						ICompositorManager* pManager = nullptr;
						g_pTangram->CreateCompositorManager((LONGLONG)m_hWnd, &pManager);
						if (pManager)
						{
							ICompositor* pICompositor = nullptr;
							pManager->CreateCompositor(CComVariant((LONGLONG)m_hWnd), CComVariant((__int64)m_hChild), CComBSTR("default"), &pICompositor);
							if (pICompositor)
							{
								IWndNode* pNode = nullptr;
								pICompositor->Open(CComBSTR("default"), CComBSTR(pVSParse->xml()), &pNode);
								::GetModuleFileName(::GetModuleHandle(_T("tangramdesigner.dll")),g_pTangram->m_szBuffer,MAX_PATH);
								CString strLib = CString(g_pTangram->m_szBuffer);
								CString strObjName = _T("TangramDesigner.WebRuntimeHelper");
								CString strFunctionName = _T("TangramInit");
								CTangramXmlParse* pVSData = m_Parse.GetChild(_T("vstoolwindow"));
								if (pVSData)
								{
									DWORD dwRetCode = 0;
									HRESULT hrStart = g_pTangram->m_pClrHost->ExecuteInDefaultAppDomain(
										strLib,
										strObjName,
										strFunctionName,
										pVSData->xml(),
										&dwRetCode);
								}
							}
						}
					}
				}
			}
			else
			{
				auto t = create_task([this]()
					{
						SleepEx(500, true);
						::PostMessage(m_hWnd, WM_TANGRAMMSG, 0, 20200516);
						return 1;
					});
			}
		}
	}
	break;
	}
	return lRes;
}

LRESULT CGenericPaneWnd::OnTangramData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	if(wParam==0&&lParam==0)
		return (LRESULT)this;
	return lRes;
}

LRESULT CGenericPaneWnd::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	if (wParam) {
	}
	else
	{
	}
	return lRes;
}

LRESULT CGenericPaneWnd::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	if (m_hChild == NULL)
	{
		m_hChild = ::GetWindow(m_hWnd, GW_CHILD);
	}
	if (m_pCompositor == nullptr)
	{
		ICompositor* pCompositor = nullptr;
		g_pTangram->GetCompositor((__int64)m_hChild, &pCompositor);
		if (pCompositor)
		{
			m_pCompositor=(CCompositor*)pCompositor;
		}
	}
	if (m_pCompositor)
	{
		RECT rc;
		::GetClientRect(m_hChild, &rc);
		if(rc.right*rc.bottom==0)
			m_pCompositor->HostPosChanged();
	}
	return lRes;
}

// Method used for Windows 8.1 and later.
// Since we support versions earlier than 8.1, we must dynamically load this
// function from user32.dll, so it won't fail to load in runtime. For earlier
// Windows versions GetProcAddress will return null and report failure so that
// callers can fall back on the deprecated SetProcessDPIAware.
bool SetProcessDpiAwarenessWrapper(PROCESS_DPI_AWARENESS value) {
	decltype(&::SetProcessDpiAwareness) set_process_dpi_awareness_func =
		reinterpret_cast<decltype(&::SetProcessDpiAwareness)>(GetProcAddress(
			GetModuleHandle(L"user32.dll"), "SetProcessDpiAwarenessInternal"));
	if (set_process_dpi_awareness_func) {
		HRESULT hr = set_process_dpi_awareness_func(value);
		if (SUCCEEDED(hr))
			return true;
		//DLOG_IF(ERROR, hr == E_ACCESSDENIED)
		//	<< "Access denied error from SetProcessDpiAwarenessInternal. Function "
		//	"called twice, or manifest was used.";
		//NOTREACHED()
		//	<< "SetProcessDpiAwarenessInternal failed with unexpected error: "
		//	<< hr;
		//return false;
	}
	return false;
}

CTangramApp::CTangramApp()
{
	m_bHostCLR = false;
}

CTangramApp::~CTangramApp()
{
	if (g_pTangram)
		delete g_pTangram;

	OutputDebugString(_T("******************************Exit CTangramApp******************************\n"));
}

BOOL CTangramApp::InitInstance()
{
	OutputDebugString(_T("******* Start CTangramApp::InitInstance()*************\n"));
	TCHAR m_szBuffer[MAX_PATH];
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	::GetModuleFileName(NULL, m_szBuffer, MAX_PATH);
	CString path(m_szBuffer);
	int nPos = path.ReverseFind('\\');
	CString strName = path.Mid(nPos + 1);
	nPos = strName.Find(_T("."));
	CString strExeName = strName.Left(nPos);
	strExeName.MakeLower();
	if (strExeName == _T("regsvr32"))
		return true;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(824);

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	::OleInitialize(NULL);
	BOOL bOfficeApp = false;

	m_bHostCLR = (BOOL)::GetModuleHandle(_T("mscoreei.dll"));
	CString strExes = _T("");
	HMODULE hModule = ::GetModuleHandle(_T("mso.dll"));
	if (hModule)
	{
		strExes = _T("winword,excel,powerpnt,outlook,msaccess,infopath,winproj,onenote,visio,");
		bOfficeApp = true;
	}
	if (bOfficeApp)
	{
		COfficeAddin* pOfficeAddin = (COfficeAddin*)this;
		nPos = strExes.Find(strExeName);
		if (nPos != -1)
		{
			int nAppID = strExes.Left(nPos).Replace(_T(","), _T(""));
			switch (nAppID)
			{
			case 0:
				new CComObject < WordPlus::CWordAddin >;
				break;
			case 1:
				new CComObject < ExcelPlus::CExcelAddin >;
				break;
			case 2:
				new CComObject < PowerPointPlus::CPowerPntAddin >;
				break;
			case 3:
				new CComObject < OutLookPlus::COutLookAddin >;
				break;
			case 4:
				new CComObject < AccessPlus::CAccessAddin >;
				break;
			case 6:
				new CComObject < ProjectPlus::CProjectAddin >;
				break;
				//case 5:
				//	m_pTangram = new CComObject < InfoPathPlus::CInfoPathCloudAddin >;
				//	break;
			case 7:
				new CComObject < OfficePlus::COfficeAddin >;
				break;
			case 8:
				new CComObject < VisioPlus::CVisioAddin >;
				break;
			}
			g_pTangram->m_nAppID = nAppID;
			}
		}
	else
	{
#ifndef _WIN64
		if (::GetModuleHandle(_T("TangramPackage.dll")))
		{
			CString strVer = theApp.GetFileVer();
			int nPos = strVer.Find(_T("."));
			int nVer = _wtoi(strVer.Left(nPos));
			if (nVer > 9)
			{
				new CComObject < VisualStudioPlus::CVSAddin >;
				g_pTangram->m_nAppID = 9;
			}
		}
		else
		{
			new CComObject < CTangram >;
			g_pTangram->m_strExeName = strExeName;
			g_pTangram->m_dwThreadID = ::GetCurrentThreadId();
			if (g_pTangram->m_hCBTHook == nullptr)
				g_pTangram->m_hCBTHook = SetWindowsHookEx(WH_CBT, CTangramApp::CBTProc, NULL, g_pTangram->m_dwThreadID);
			theApp.SetHook(g_pTangram->m_dwThreadID);
		}
#else
		new CComObject < CTangram >;
		g_pTangram->m_strExeName = strExeName;
		g_pTangram->m_dwThreadID = ::GetCurrentThreadId();
		if (g_pTangram->m_hCBTHook == nullptr)
			g_pTangram->m_hCBTHook = SetWindowsHookEx(WH_CBT, CTangramApp::CBTProc, NULL, g_pTangram->m_dwThreadID);
		g_pTangram->m_bEnableProcessFormTabKey = true;
		theApp.SetHook(g_pTangram->m_dwThreadID);
		if (g_pTangram->m_hForegroundIdleHook == NULL)
			g_pTangram->m_hForegroundIdleHook = SetWindowsHookEx(WH_FOREGROUNDIDLE, CTangramApp::ForegroundIdleProc, NULL, ::GetCurrentThreadId());
#endif	
	}
	if (g_pTangram)
	{
		WNDCLASS wndClass;
		wndClass.style = CS_DBLCLKS;
		wndClass.lpfnWndProc = ::DefWindowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = AfxGetInstanceHandle();
		wndClass.hIcon = 0;
		wndClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = 0;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = _T("Tangram Splitter Class");

		RegisterClass(&wndClass);

		g_pTangram->m_lpszSplitterClass = wndClass.lpszClassName;

		wndClass.lpfnWndProc = CTangramApp::TangramWndProc;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpszClassName = L"Tangram Window Class";

		RegisterClass(&wndClass);

		wndClass.lpfnWndProc = CTangramApp::TangramMsgWndProc;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpszClassName = L"Tangram Message Window Class";

		RegisterClass(&wndClass);

		wndClass.lpfnWndProc = CTangramApp::TangramExtendedWndProc;
		wndClass.lpszClassName = L"Chrome Extended Window Class";

		RegisterClass(&wndClass);

		g_pTangram->m_strExeName = strExeName;
		g_pTangram->m_dwThreadID = ::GetCurrentThreadId();
		g_pTangram->TangramLoad();
		theApp.SetHook(g_pTangram->m_dwThreadID);
		if (bOfficeApp || ::GetModuleHandle(_T("msenv.dll")))
			g_pTangram->Init();
		else
		{
			//#ifdef _WIN64
			g_pTangram->m_strStartupURL = _T("");
			int nPos = path.ReverseFind('.');
			int nPos2 = path.ReverseFind('\\');
			CString strPath = path.Left(nPos + 1);
			CString strPath2 = path.Left(nPos2 + 1) + _T("tangram_chrome_rt.dll");
			BOOL bHasChromeRT = ::PathFileExists(strPath2) && !::PathIsDirectory(strPath2);
			CString strInitWebPage = strPath + _T("index.html");
			CString strInitEclipse = strPath + _T("eclipse");
			bool bSupportBrowser = (::PathFileExists(strInitWebPage) && !::PathIsDirectory(strInitWebPage));
			bool bSupportEclipse = (::PathFileExists(strInitEclipse) && !::PathIsDirectory(strInitEclipse));
			if (bSupportEclipse)
			{
				g_pTangram->m_bEclipse = false;
				CString strplugins = g_pTangram->m_strAppPath + _T("plugins\\");
				if (::PathIsDirectory(strplugins)) {
					CString strPath = strplugins + _T("*.jar");
					_wfinddata_t fd;
					fd.attrib = FILE_ATTRIBUTE_DIRECTORY;
					intptr_t pf = _wfindfirst(strPath, &fd);
					if ((fd.attrib & FILE_ATTRIBUTE_DIRECTORY) == 0) {
						g_pTangram->m_bEclipse = true;
					}
					else {
						while (!_wfindnext(pf, &fd)) {
							if ((fd.attrib & FILE_ATTRIBUTE_DIRECTORY) == 0) {
								g_pTangram->m_bEclipse = true;
								break;
							}
						}
					}
					_findclose(pf);
				}
				bSupportEclipse = g_pTangram->m_bEclipse;
			}
			if (bHasChromeRT && bSupportBrowser && bSupportEclipse)
			{
				g_pTangram->m_strStartupURL = strInitWebPage;
				g_pTangram->m_nAppType = TANGRAM_APP_BROWSER_ECLIPSE;
			}
			if (g_pTangram->m_strStartupURL == _T(""))
			{
				if (bSupportEclipse)
				{
					g_pTangram->m_nAppType = TANGRAM_APP_ECLIPSE;
					g_pTangram->m_strStartupURL = strInitEclipse;
				}
				else
				{
					if (bSupportBrowser)
					{
						if (bHasChromeRT)
						{
							g_pTangram->m_strStartupURL = strInitWebPage;
							g_pTangram->m_nAppType = TANGRAM_APP_BROWSERAPP;
						}
					}
					else
					{
						strPath = strPath + _T("win32");
						if (::PathFileExists(strPath) && !::PathIsDirectory(strPath))
						{
							g_pTangram->m_nAppType = TANGRAM_APP_WIN32;
							g_pTangram->m_strStartupURL = strPath;
						}
						else if (bHasChromeRT)
						{
							g_pTangram->m_nAppType = TANGRAM_APP_BROWSER;
							g_pTangram->m_strStartupURL = _T("");
						}
					}
				}
			}
			//#else
			//#endif
			::PostAppMessage(g_pTangram->m_dwThreadID, WM_TANGRAMINIT, 20191005, 0);
		}
	}

	return true;
	}

int CTangramApp::ExitInstance()
{
	ATLTRACE(_T("Begin Tangram ExitInstance :%p\n"), this);
	if (g_pTangram) {
		g_pTangram->ExitInstance();
	}
	AfxOleTerm(FALSE);
	ATLTRACE(_T("End Tangram ExitInstance :%p\n"), this);

	return CWinApp::ExitInstance();
}

LRESULT CALLBACK CTangramApp::TangramWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		::ShowWindow(g_pTangram->m_hHostWnd, SW_HIDE);
	}
	return 0;
	case WM_DESTROY:
	{
		if (hWnd == g_pTangram->m_hHostWnd)
		{
			g_pTangram->m_pActiveAppProxy = nullptr;
			for (auto it : g_pTangram->m_mapBKFrame)
			{
				HWND hWnd = ::GetParent(it.first);
				ICompositor* pCompositor = nullptr;
				g_pTangram->GetCompositor((__int64)::GetParent(hWnd), &pCompositor);
				CCompositor* _pCompositor = (CCompositor*)pCompositor;
				if (_pCompositor)
					_pCompositor->m_pBKWnd = nullptr;
				::DestroyWindow(::GetParent(it.first));
			}

			if (g_pTangram->m_pCLRProxy)
			{
				if (g_pTangram->m_pTangramCLRAppProxy)
					g_pTangram->m_pTangramCLRAppProxy->OnTangramClose();
				if (g_pTangram->m_pCLRProxy)
					g_pTangram->m_pCLRProxy->TangramAction(_T("<begin_quit_eclipse/>"), nullptr);
			}
			if (g_pTangram->m_mapMDTFrame.size())
			{
				auto it = g_pTangram->m_mapMDTFrame.begin();
				while (it != g_pTangram->m_mapMDTFrame.end())
				{
					if (it->second)
					{
						it->second->DestroyWindow();
					}
					it = g_pTangram->m_mapMDTFrame.begin();
				}
			}
			g_pTangram->m_mapMDTFrame.clear();

			if (g_pTangram->m_mapTangramMDIChildWnd.size())
			{
				auto it = g_pTangram->m_mapTangramMDIChildWnd.begin();
				while (it != g_pTangram->m_mapTangramMDIChildWnd.end())
				{
					if (it->second)
					{
						it->second->DestroyWindow();
					}
					it = g_pTangram->m_mapTangramMDIChildWnd.begin();
				}
			}
			g_pTangram->m_mapTangramMDIChildWnd.clear();

			if (::IsWindow(g_pTangram->m_hHostBrowserWnd))
			{
				::SendMessage(g_pTangram->m_hHostBrowserWnd, WM_CLOSE, 0, 0);
			}

			//while (g_pTangram->m_mapBrowserWnd.size())
			//{
			//	auto it = g_pTangram->m_mapBrowserWnd.begin();
			//	if (it != g_pTangram->m_mapBrowserWnd.end())
			//		::DestroyWindow(it->first);
			//}
			if (g_pTangram->m_hForegroundIdleHook)
				UnhookWindowsHookEx(g_pTangram->m_hForegroundIdleHook);

			g_pTangram->m_pDesignerFrame = nullptr;
			g_pTangram->m_pDesignerCompositorManager = nullptr;
		}
		break;
	}
	break;
	case WM_POWERBROADCAST:
	{
		if (wParam == PBT_APMRESUMEAUTOMATIC)
		{
			//for (auto it : g_pTangram->m_mapWindowPage)
			//{
			//	if (it.second)
			//	{
			//		for (auto it2 : it.second->m_mapCompositor)
			//		{
			//			it2.second->HostPosChanged();
			//			for (auto it3 : it2.second->m_mapWPFView)
			//			{
			//				ATLTRACE(_T("HWND %x, WM_POWERBROADCAST\n"), it3.second->m_hWnd);
			//				::SetWindowLongPtr(it3.second->m_hWnd, GWLP_USERDATA, 1963);
			//			}
			//		}
			//	}
			//}
			for (auto it : g_pTangram->m_mapThreadInfo)
			{
				if (it.second)
				{
					for (auto it2 : it.second->m_mapCompositor)
					{
						it2.second->HostPosChanged();
						for (auto it3 : it2.second->m_mapWPFView)
						{
							ATLTRACE(_T("HWND %x, WM_POWERBROADCAST\n"), it3.second->m_hWnd);
							::SetWindowLongPtr(it3.second->m_hWnd, GWLP_USERDATA, 1963);
						}
					}
				}
			}
		}
	}
	break;
	case WM_WINDOWPOSCHANGED:
		if (hWnd == g_pTangram->m_hHostWnd)
		{
			RECT rc;
			::GetClientRect(g_pTangram->m_hHostWnd, &rc);
			::SetWindowPos(g_pTangram->m_hChildHostWnd, NULL, 0, 0, rc.right, rc.bottom, SWP_NOACTIVATE | SWP_NOREDRAW);
		}
		else if (hWnd == g_pTangram->m_hTemplateWnd)
		{
			RECT rc;
			::GetClientRect(g_pTangram->m_hTemplateWnd, &rc);
			::SetWindowPos(g_pTangram->m_hTemplateChildWnd, NULL, 0, 0, rc.right, rc.bottom, SWP_NOACTIVATE | SWP_NOREDRAW);
		}
		break;
	case WM_OPENDOCUMENT:
	{
		g_pTangram->OnOpenDoc(wParam);
	}
	break;
	case WM_INITOUTLOOK:
	{
		((OfficePlus::OutLookPlus::COutLookAddin*)g_pTangram)->InitOutLook();
	}
	break;
	case WM_OFFICEOBJECTCREATED:
	{
		HWND hWnd = (HWND)wParam;
		if (::IsWindow(hWnd))
			((OfficePlus::COfficeAddin*)g_pTangram)->ConnectOfficeObj(hWnd);
	}
	break;
	case WM_TANGRAMMSG:
		switch (lParam)
		{
		case 20200519:
		{
			if (wParam)
			{
				HWND _hWnd = (HWND)wParam;
				if (::IsWindow(hWnd))
				{
					HWND hWndChild = ::GetWindow(_hWnd, GW_CHILD);
					TCHAR	szBuffer[MAX_PATH];
					::GetClassName(_hWnd, szBuffer, MAX_PATH);
					CString strClassName = CString(szBuffer);
					if (strClassName == _T("GenericPane"))
					{
						::GetClassName(hWndChild, szBuffer, MAX_PATH);
						strClassName = CString(szBuffer);
						if (strClassName == _T("TBToolboxPane"))
						{
							CGenericPaneWnd* pWnd = new CGenericPaneWnd();
							pWnd->m_strToolType = strClassName;
							pWnd->SubclassWindow(_hWnd);
							if (g_pTangram->m_pTangramVS)
							{
								::PostMessage(_hWnd, WM_TANGRAMMSG, 0, 20200516);
							}
						}
					}
				}
			}
		}
		break;
		case 1222:
		{
			if (wParam == 1963)
			{
				OfficePlus::OutLookPlus::COutLookAddin* pAddin = (OfficePlus::OutLookPlus::COutLookAddin*)g_pTangram;
				if (pAddin->m_pActiveOutlookExplorer)
				{
					pAddin->m_pActiveOutlookExplorer->SetDesignState();
				}
			}
		}
		break;
		case TANGRAM_CHROME_APP_INIT:
		{
			if (g_pTangram->m_nAppType == TANGRAM_APP_BROWSER_ECLIPSE)
			{
				ITangramCLRImpl* pProxy = g_pTangram->m_pCLRProxy;
				g_pTangram->InitEclipseApp();
				if (pProxy)
				{
					pProxy->TangramAction(CComBSTR("EndInitEclipseApp"), nullptr);
				}
			}
			else if (g_pTangram->m_hMainWnd == NULL && g_pTangram->m_pTangramAppProxy)
				g_pTangram->m_hMainWnd = g_pTangram->m_pTangramAppProxy->InitTangramApp();
		}
		break;
		case 20200120:
		{
			HWND h = (HWND)wParam;
			if (g_pTangram->m_pCLRProxy)
			{
				g_pTangram->m_pCLRProxy->OnWinFormActivate(h, 4);
			}
		}
		break;
		}
		break;
	case WM_TABCHANGE:
	{
		HWND hwnd = (HWND)wParam;
		ICompositor* pCompositor = nullptr;
		g_pTangram->GetCompositor((LONGLONG)hwnd, &pCompositor);
		if (pCompositor)
		{
			IWndNode* pNode = nullptr;
			pCompositor->Open(CComBSTR(L""), CComBSTR(L""), &pNode);
			LONGLONG h = 0;
			pNode->get_Handle(&h);
			HWND hWnd = (HWND)h;
			::InvalidateRect(hWnd, nullptr, true);
		}
	}
	break;
	case WM_TANGRAMNEWOUTLOOKOBJ:
	{
		using namespace OfficePlus::OutLookPlus;
		int nType = wParam;
		HWND hWnd = ::GetActiveWindow();
		if (nType)
		{
			COutLookExplorer* pOutLookPlusItemWindow = (COutLookExplorer*)lParam;
			COutLookAddin* pAddin = (COutLookAddin*)g_pTangram;
			pOutLookPlusItemWindow->m_strKey = pAddin->m_strCurrentKey;
			pAddin->m_mapOutLookPlusExplorerMap[hWnd] = pOutLookPlusItemWindow;
			pOutLookPlusItemWindow->m_hWnd = hWnd;
		}
	}
	break;
	case WM_TANGRAMACTIVEINSPECTORPAGE:
	{
		using namespace OfficePlus::OutLookPlus;
		COutLookInspector* pOutLookPlusItemWindow = (COutLookInspector*)wParam;
		pOutLookPlusItemWindow->ActivePage();
	}
	break;
	case WM_TANGRAMITEMLOAD:
	{
		using namespace OfficePlus::OutLookPlus;
		COutLookAddin* pAddin = (COutLookAddin*)g_pTangram;
		HWND hWnd = ::GetActiveWindow();
		auto it = pAddin->m_mapOutLookPlusExplorerMap.find(hWnd);
		if (it != pAddin->m_mapOutLookPlusExplorerMap.end())
		{
			COutLookExplorer* pExplorer = it->second;
			if (pExplorer->m_pInspectorContainerWnd == nullptr)
			{
				HWND _hWnd = ::FindWindowEx(hWnd, NULL, _T("rctrl_renwnd32"), NULL);
				if (_hWnd)
				{
					_hWnd = ::FindWindowEx(_hWnd, NULL, _T("AfxWndW"), NULL);
					if (_hWnd)
					{
						pExplorer->m_pInspectorContainerWnd = new CInspectorContainerWnd();
						pExplorer->m_pInspectorContainerWnd->SubclassWindow(_hWnd);
					}
				}
			}

			long nKey = wParam;
			auto it = pAddin->m_mapTangramInspectorItem.find(nKey);
			if (it != pAddin->m_mapTangramInspectorItem.end())
			{
				CInspectorItem* pItem = (CInspectorItem*)wParam;
				if (pExplorer->m_pInspectorContainerWnd)
				{
					pExplorer->m_pInspectorContainerWnd->m_strXml = pItem->m_strXml;
					::PostMessage(pExplorer->m_pInspectorContainerWnd->m_hWnd, WM_TANGRAMITEMLOAD, 0, 0);
				}
			}
		}
	}
	break;
	case WM_TANGRAMAPPINIT:
	{
		if (g_pTangram->m_bEclipse)
		{
			if (wParam == 1963 && lParam == 1222)
			{
				break;
			}

			if (g_pTangram->m_pActiveEclipseWnd)
			{
				IWndNode* pNode = nullptr;
				if (g_pTangram->m_strStartView == _T("TopView"))
				{
					g_pTangram->m_pActiveEclipseWnd->Open(_T("Start"), g_pTangram->m_strStartXml.AllocSysString(), &pNode);
				}
				else if (g_pTangram->m_strStartView == _T("EclipseView"))
				{
					IEclipseCtrl* pCtrl = nullptr;
					g_pTangram->m_pActiveEclipseWnd->get_Ctrl(CComVariant((long)0), &pCtrl);
					if (pCtrl)
					{
						pCtrl->Open(CComBSTR(L"EclipseView"), CComBSTR(L"Start"), g_pTangram->m_strStartXml.AllocSysString(), &pNode);
					}
				}
			}
		}
	}
	break;
	case WM_TANGRAMAPPQUIT:
	{
		::PostAppMessage(::GetCurrentThreadId(), WM_QUIT, 0, 0);
	}
	break;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
//
//LRESULT CTangramApp::ForegroundIdleProc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//	if (g_pTangram->m_pTangramDelegate)
//	{
//		g_pTangram->m_pTangramDelegate->ForegroundIdleProc();
//	}
//	for (auto it : g_pTangram->m_mapTangramAppProxy)
//		it.second->OnForegroundIdleProc();
//	return CallNextHookEx(g_pTangram->m_hForegroundIdleHook, nCode, wParam, lParam);
//}

LRESULT CTangramApp::ForegroundIdleProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	for (auto it : g_pTangram->m_mapBrowserWnd)
	{
		CBrowserWnd* pWnd = (CBrowserWnd*)it.second;
		if (pWnd && ::IsWindowVisible(it.first) && pWnd->m_pVisibleWebWnd)
		{
			HWND hWnd = pWnd->m_pBrowser->GetActiveWebContentWnd();
			if (pWnd->m_pVisibleWebWnd)
			{
				if (pWnd->m_pVisibleWebWnd->m_hWnd != hWnd)
				{
					auto it = g_pTangram->m_mapHtmlWnd.find(hWnd);
					if (it != g_pTangram->m_mapHtmlWnd.end())
					{
						pWnd->m_pVisibleWebWnd = (CHtmlWnd*)it->second;
					}
				}
				//else
				//{
				//	if (::IsChild(pWnd->m_pVisibleWebWnd->m_hWnd, pWnd->m_pVisibleWebWnd->m_hExtendWnd))
				//		::SetParent(pWnd->m_pVisibleWebWnd->m_hExtendWnd, it.first);
				//	//else
				//	//{
				//	//	if (::IsWindow(pWnd->m_pVisibleWebWnd->m_hExtendWnd))
				//	//	{
				//	//		RECT rc;
				//	//		::GetClientRect(pWnd->m_pVisibleWebWnd->m_hExtendWnd, &rc);
				//	//		if (rc.right * rc.bottom == 0)
				//	//		{
				//	//			//::PostMessage(pWnd->m_hWnd, WM_BROWSERLAYOUT, 0, 2);
				//	//		}
				//	//	}
				//	//}
				//}
			}
			if (!::IsChild(it.first, pWnd->m_pVisibleWebWnd->m_hWnd))
				::PostMessage(pWnd->m_pVisibleWebWnd->m_hWnd, WM_TANGRAMMSG, 20200131, 0);
		}
	}

	if (g_pTangram->m_pTangramDelegate)
	{
		g_pTangram->m_pTangramDelegate->ForegroundIdleProc();
	}
	for (auto it : g_pTangram->m_mapTangramAppProxy)
		it.second->OnForegroundIdleProc();
	return CallNextHookEx(g_pTangram->m_hForegroundIdleHook, nCode, wParam, lParam);
}

LRESULT CALLBACK CTangramApp::TangramMsgWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		if (g_pTangram->m_hTangramWnd == NULL)
		{
			g_pTangram->m_hTangramWnd = hWnd;
			//::PostMessage(hWnd, WM_TANGRAMINIT, 0, 20002000);
			g_pTangram->TangramInit();
		}
	}
	break;
	case WM_WINFORMCREATED:
	{
		LRESULT l = ::SendMessage((HWND)wParam, WM_TANGRAMDATA, 0, 20190214);
		if (l == 0)
		{
			CTangramWinFormWnd* pWnd = new CTangramWinFormWnd();
			g_pTangram->m_hFormNodeWnd = NULL;
			g_pTangram->m_hFormNodeWnd = (HWND)wParam;
			pWnd->SubclassWindow((HWND)wParam);
			::PostMessage(g_pTangram->m_hFormNodeWnd, WM_WINFORMCREATED, 0, 0);
		}
	}
	break;
	case WM_MDICLIENTCREATED:
	{
		if (g_pTangram->m_pMDIMainWnd)
		{
			ICompositorManager* pCompositorManager = nullptr;
			g_pTangram->CreateCompositorManager((__int64)g_pTangram->m_pMDIMainWnd->m_hWnd, &pCompositorManager);
			g_pTangram->m_pMDIMainWnd->m_pCompositorManager = (CCompositorManager*)pCompositorManager;
			IWndNode* pNode = nullptr;
			g_pTangram->m_pMDIMainWnd->m_pDocTemplate->m_strKey = _T("default");
			g_pTangram->m_pMDIMainWnd->m_pDocTemplate->m_strClientKey = _T("default");
			g_pTangram->m_pMDIMainWnd->m_pDocTemplate->InitXmlData();
			ICompositor* pCompositor = nullptr;
			g_pTangram->m_pMDIMainWnd->m_pCompositorManager->CreateCompositor(CComVariant(0), CComVariant((LONGLONG)g_pTangram->m_pMDIMainWnd->m_hMDIClient), CComBSTR("mdiclient"), &pCompositor);
			if (pCompositor)
			{
				CCompositor* _pCompositor = (CCompositor*)pCompositor;
				_pCompositor->m_pTangramDocTemplate = g_pTangram->m_pMDIMainWnd->m_pDocTemplate;
				pCompositor->Open(CComBSTR("mdiclient"), CComBSTR(""), &pNode);
				g_pTangram->m_pMDIMainWnd->m_pDocTemplate->m_mapMainPageNode[g_pTangram->m_pMDIMainWnd->m_hMDIClient] = (CWndNode*)pNode;
			}
			for (auto it : g_pTangram->m_pMDIMainWnd->m_mapDesignableWnd)
			{
				HWND h = ::GetParent(it.first);
				::GetWindowText(h, g_pTangram->m_szBuffer, MAX_PATH);
				CString str = CString(g_pTangram->m_szBuffer);
				str.Replace(_T(" "), _T("_"));
				g_pTangram->m_pMDIMainWnd->m_mapDesignableWnd[it.first] = str;
			}
		}
		return 0;
	}
	break;
	case WM_CONTROLBARCREATED:
	{
		HWND hwnd = (HWND)wParam;
		HWND hPWnd = (HWND)lParam;
		HWND hTop = ::GetAncestor(hPWnd, GA_ROOT);
		auto it = g_pTangram->m_mapTangramMDIChildWnd.find(hTop);
		if (it != g_pTangram->m_mapTangramMDIChildWnd.end() || (g_pTangram->m_nAppType == 1965 && g_pTangram->m_pActiveMDIChildWnd))
		{
			return 1;
		}

		if (lParam && ::IsWindow(hwnd))
		{
			HWND hClient = nullptr;
			auto it = g_pTangram->m_mapWorkBenchWnd.find(hPWnd);
			if (it != g_pTangram->m_mapWorkBenchWnd.end())
			{
				hClient = ((CEclipseWnd*)it->second)->m_hClient;
				hPWnd = ::GetParent(hClient);
			}
			else
				hClient = ::GetDlgItem(hPWnd, AFX_IDW_PANE_FIRST);
			BOOL bMDIClientCompositor = FALSE;
			if (::GetWindowLong(hClient, GWL_STYLE) & MDIS_ALLCHILDSTYLES)
			{
				bMDIClientCompositor = TRUE;
			}
			CTangramAFXHelperWnd* pCtrlBar = new CTangramAFXHelperWnd();
			pCtrlBar->m_hParent = hPWnd;
			pCtrlBar->SubclassWindow(hwnd);
			g_pTangram->m_mapTangramAFXHelperWnd[hwnd] = pCtrlBar;
			HWND hFrame = ::GetDlgItem(hwnd, AFX_IDW_PANE_FIRST);
			if (::IsWindow(hFrame))
			{
				pCtrlBar->m_hFrame = hFrame;
				if (::IsWindow(hPWnd))
				{
					CCompositorManager* pCompositorManager = nullptr;
					auto it = g_pTangram->m_mapWindowPage.find(hPWnd);
					if (it == g_pTangram->m_mapWindowPage.end())
					{
						HWND hPWnd = (HWND)lParam;
						IWndNode* pNode = nullptr;
						pCompositorManager = new CComObject<CCompositorManager>;
						pCompositorManager->m_hWnd = hPWnd;
						g_pTangram->m_mapWindowPage[hPWnd] = pCompositorManager;
						pCompositorManager->put_ConfigName(CComBSTR(L""));
						for (auto it : g_pTangram->m_mapTangramAppProxy)
						{
							CCompositorManagerProxy* pTangramProxy = it.second->OnCompositorManagerCreated(pCompositorManager);
							if (pTangramProxy)
								pCompositorManager->m_mapCompositorManagerProxy[it.second] = pTangramProxy;
						}
					}
					else
					{
						pCompositorManager = (CCompositorManager*)it->second;
					}
					if (g_pTangram->m_pMDIMainWnd && g_pTangram->m_pMDIMainWnd->m_pDocTemplate)
						pCompositorManager->m_pTangramDocTemplate = g_pTangram->m_pMDIMainWnd->m_pDocTemplate;
					auto it2 = pCompositorManager->m_mapCtrlBarCompositor.find(hFrame);
					if (it2 == pCompositorManager->m_mapCtrlBarCompositor.end())
					{
						CString strCaption = _T("");
						::GetWindowText(hFrame, g_pTangram->m_szBuffer, MAX_PATH);
						strCaption = CString(g_pTangram->m_szBuffer);
						strCaption.Trim();
						if (strCaption == _T(""))
						{
							::GetWindowText(hwnd, g_pTangram->m_szBuffer, MAX_PATH);
							strCaption = CString(g_pTangram->m_szBuffer);
							strCaption.Trim();
						}
						strCaption.Replace(_T(" "), _T("_"));
						//strCaption += _T("_default");
						IWndNode* pNode = nullptr;
						bool bSavetocfg = (pCompositorManager->m_pTangramDocTemplate == nullptr);
						pCompositorManager->CreateCompositorWithDefaultNode((LONGLONG)hFrame, CComBSTR(strCaption), CComBSTR(L""), CComBSTR(L""), bSavetocfg, &pNode);
						if (pNode)
						{
							if (pCompositorManager->m_pTangramDocTemplate)
							{
								pCompositorManager->m_pTangramDocTemplate->m_mapMainPageNode[hFrame] = (CWndNode*)pNode;
							}
							ICompositor* pCompositor = nullptr;
							pNode->get_Compositor(&pCompositor);
							((CCompositor*)pCompositor)->m_nCompositorType = CtrlBarCompositor;
							pCompositorManager->m_mapCtrlBarCompositor[hFrame] = (CCompositor*)pCompositor;
						}
					}
				}
			}
		}
		return 1;
	}
	break;
	case WM_TANGRAMMSG:
	{
		if (wParam)
		{
			switch (lParam)
			{
			case 19631963:
			{
				DocTemplateInfo* pDocTemplateInfo = (DocTemplateInfo*)wParam;
				CString strPath = g_pTangram->m_strAppCommonDocPath + _T("Tangramdoctemplate.xml");
				if (::PathFileExists(strPath))
				{
					CTangramXmlParse m_Parse;
					m_Parse.LoadFile(strPath);
					CString _strKey = pDocTemplateInfo->strProxyID + pDocTemplateInfo->strExt;
					if (m_Parse.GetChild(_strKey) == nullptr)
					{
						CTangramXmlParse* pParse = m_Parse.AddNode(_strKey);
						CString strVal = _T("");
						strVal += pDocTemplateInfo->strFileTypeID;
						strVal += _T("|");
						strVal += pDocTemplateInfo->strfilterName;
						strVal += _T("|");
						strVal += _T("*") + pDocTemplateInfo->strExt;
						strVal += _T("|");
						strVal += pDocTemplateInfo->strProxyName;
						strVal += _T("|");
						if (pDocTemplateInfo->nResID != -1)
						{
							CString strID = _T("");
							strID.Format(_T("%d"), pDocTemplateInfo->nResID);
							pParse->put_attr(_T("ResID"), strID);
						}
						pParse->put_text(strVal);
						m_Parse.SaveFile(strPath);
						if (pDocTemplateInfo->bDll)
						{
							TCHAR	m_szBuffer[MAX_PATH];
							HRESULT hr = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, m_szBuffer);
							CString strPath = CString(m_szBuffer);
							strPath += _T("\\TangramCommonDocTemplate\\TangramReg.xml");
							CTangramXmlParse m_Parse2;
							if (::PathFileExists(strPath) == FALSE)
							{
								m_Parse2.LoadXml(_T("<TangramDocReg />"));
								m_Parse2.SaveFile(strPath);
							}
							else
							{
								m_Parse2.LoadFile(strPath);
							}
							if (m_Parse2.GetChild(pDocTemplateInfo->strProxyID) == false)
							{
								m_Parse2.AddNode(pDocTemplateInfo->strProxyID);
								m_Parse2.SaveFile(strPath);
							}
						}
					}
				}
				//delete pDocTemplateInfo;
			}
			break;
			case 19651963:
			{
				if (g_pTangram->m_bEclipse == false &&
					::GetModuleHandle(_T("tangram_clr_rt.dll")) == nullptr &&
					g_pTangram->m_bOfficeApp == false &&
					g_pTangram->m_strStartupCLRObj != _T(""))
				{
					g_pTangram->LoadCLR();

					CComPtr<IDispatch> pFormDisp;
					g_pTangram->CreateCLRObj(g_pTangram->m_strStartupCLRObj.AllocSysString(), &pFormDisp);
					if (pFormDisp)
					{
						g_pTangram->m_bEnableProcessFormTabKey = true;
						g_pTangram->m_pMainFormDisp = pFormDisp.Detach();
						g_pTangram->m_strStartupCLRObj = _T("");
					}
				}
				else
				{
					if (g_pTangram->m_nAppID != 9 &&
						g_pTangram->m_nTangramObj == 0 &&
						::GetModuleHandle(_T("tangram_clr_rt.dll")) == nullptr &&
						g_pTangram->m_bEclipse == false &&
						g_pTangram->m_bOfficeApp == false &&
						g_pTangram->m_mapMDTFrame.size() == 0 &&
						g_pTangram->m_mapWindowPage.size() == 0)
					{
						if (g_pTangram->m_pActiveMDIChildWnd == nullptr)
						{
							CString strPath = g_pTangram->m_strAppDataPath + _T("default.tangramdoc");
							if (::PathFileExists(strPath))
							{
								ITangramDoc* pDoc = nullptr;
								BSTR bstrPath = strPath.AllocSysString();
								g_pTangram->OpenTangramDocFile(bstrPath, &pDoc);
								::SysFreeString(bstrPath);
							}
						}
					}
				}
			}
			break;
			case 20170907:
				if (::IsWindow(g_pTangram->m_pTangramPackageProxy->m_hPropertyWnd))
				{
					::SetWindowLongPtr(g_pTangram->m_pTangramPackageProxy->m_hPropertyWnd, GWL_STYLE, ::GetWindowLongPtr(g_pTangram->m_pTangramPackageProxy->m_hPropertyWnd, GWL_STYLE) | WS_VISIBLE);
				}

				return ::DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			default:
			{
				if (g_pTangram->m_mapTangramDocTemplateInfo.size() == 0)
					g_pTangram->InitTangramDocManager();

				CString strFile = _T("");
				CFileDialog openFileDlg(true, _T(""), _T(""), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, g_pTangram->m_strDocFilters, NULL);
				openFileDlg.m_ofn.nMaxCustFilter++;
				if (openFileDlg.DoModal() == IDOK)
				{
					CString filePath = openFileDlg.GetPathName();
					ITangramDoc* pDoc = nullptr;
					g_pTangram->OpenTangramDocFile(filePath.AllocSysString(), &pDoc);
					if (pDoc != nullptr)
					{
						CTangramDoc* _pDoc = (CTangramDoc*)pDoc;
						return (LRESULT)_pDoc;
					}
				}
			}
			break;
			}
			return 0;
		}
	}
	switch (lParam)
	{
	case 19651963:
	{
		CString _strPathReg = g_pTangram->m_strAppCommonDocPath + _T("TangramReg.xml");
		CTangramXmlParse m_ParseReg;
		if (m_ParseReg.LoadFile(_strPathReg) == FALSE)
		{
			m_ParseReg.LoadXml(_T("<TangramDocReg />"));
			m_ParseReg.SaveFile(_strPathReg);
		}
		if (g_pTangram->m_strLibs != _T(""))
		{
			int nPos = g_pTangram->m_strLibs.Find(_T("|"));
			while (nPos != -1)
			{
				CString strLib = g_pTangram->m_strLibs.Left(nPos);
				g_pTangram->m_strLibs = g_pTangram->m_strLibs.Mid(nPos + 1);
				nPos = g_pTangram->m_strLibs.Find(_T("|"));
				::LoadLibrary(strLib);
			}
		}
	}
	break;
	case 10001000:
	{
		if (g_pTangram->m_nAppID != 9 && g_pTangram->m_bEclipse == false && g_pTangram->m_bOfficeApp == false)
		{
			int nCount = g_pTangram->m_mapMDTFrame.size();
			if (nCount == 0)
			{
				::PostMessage(g_pTangram->m_hTangramWnd, WM_TANGRAMAPPQUIT, 0, 0);
			}
		}
	}
	break;
	case 20170907:
		if (g_pTangram->m_pTangramPackageProxy->m_hVSGridView)
		{
			::SetParent(g_pTangram->m_pTangramPackageProxy->m_hPropertyWnd, hWnd);
			::SetWindowPos(g_pTangram->m_pTangramPackageProxy->m_hPropertyWnd, HWND_TOP, -1000, -1000, 0, 0, SWP_NOACTIVATE);
			::PostMessage(hWnd, WM_TANGRAMMSG, 1, 20170907);
		}
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	default:
		break;
	}
	return 1;
	break;
	case WM_TANGRAMINIT:
		ATLTRACE(_T("Tangram Message Window WM_TANGRAMINIT :%p\n"), g_pTangram->m_hTangramWnd);
		if (lParam == 20002000)
		{
			g_pTangram->TangramInit();
		}
		break;
		//case WM_TANGRAMDATA:
		//{
		//	if (lParam == 20200204)
		//	{
		//		BindWebObj* pObj = (BindWebObj*)wParam;
		//		CWndNode* pNode = (CWndNode*)pObj->m_pNode;
		//		if (pNode)
		//		{
		//			HWND hWnd = pNode->m_pHostWnd->m_hWnd;
		//			::SendMessage(hWnd, WM_TANGRAMDATA, wParam, lParam);
		//		}
		//	}
		//}
		break;
	case WM_TANGRAMAPPQUIT:
	{
		if (g_pTangram->m_bEclipse == false && g_pTangram->m_bOfficeApp == false)
		{
			if (g_pTangram->m_pMDIMainWnd == NULL && g_pTangram->m_mapMDTFrame.size() == 0)
			{
				::PostAppMessage(::GetCurrentThreadId(), WM_QUIT, 0, 0);
			}
		}
	}
	break;
	case WM_ECLIPSEWORKBENCHCREATED:
	{
		HWND hEclipseWorkBench = (HWND)lParam;
		if (wParam || ::IsMenu(::GetMenu(hEclipseWorkBench)))
		{
			auto it = g_pTangram->m_mapWorkBenchWnd.find(hEclipseWorkBench);
			if (it == g_pTangram->m_mapWorkBenchWnd.end())
			{
				if (g_pTangram->m_hEclipseHideWnd == nullptr)
				{
					for (auto it : g_pTangram->m_vecEclipseHideTopWnd)
					{
						::GetWindowText(it, g_pTangram->m_szBuffer, MAX_PATH);
						CString strText = CString(g_pTangram->m_szBuffer);
						if (strText.CompareNoCase(_T("PartRenderingEngine's limbo")) == 0)
						{
							g_pTangram->m_hEclipseHideWnd = it;
							::PostAppMessage(::GetCurrentThreadId(), WM_TANGRAMMSG, 0, 20191117);
							break;
						}
					}
				}

				CEclipseWnd* pEclipseWnd = new CComObject<CEclipseWnd>;
				HWND hParent = GetWindow(hEclipseWorkBench, GW_CHILD);
				HWND hClient = GetWindow(hParent, GW_CHILD);
				pEclipseWnd->m_hClient = hClient;
				if (hClient)
					::SetWindowLongPtr(pEclipseWnd->m_hClient, GWLP_ID, AFX_IDW_PANE_FIRST);

				g_pTangram->m_mapWorkBenchWnd[hEclipseWorkBench] = pEclipseWnd;
				pEclipseWnd->SubclassWindow(hEclipseWorkBench);
				::PostMessage(hEclipseWorkBench, WM_TANGRAMMSG, 19820911, 0);
				pEclipseWnd->CreatePage(true);
			}
		}
	}

	break;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK CTangramApp::TangramExtendedWndProc(_In_ HWND hWnd, UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_WINDOWPOSCHANGED:
	{
		WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;
		LRESULT lRes = ::DefWindowProc(hWnd, msg, wParam, lParam);
		HWND m_hChildWnd = (HWND)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (::IsWindow(m_hChildWnd)) {
			if (::IsWindowVisible(hWnd))
			{
				RECT rc;
				::GetClientRect(m_hChildWnd, &rc);
				if (rc.right != lpwndpos->cx || rc.bottom != lpwndpos->cy)
					::SetWindowPos(m_hChildWnd, HWND_BOTTOM, 0, 0, lpwndpos->cx, lpwndpos->cy, /*SWP_FRAMECHANGED |*/SWP_NOREDRAW | SWP_NOACTIVATE);
			}
		}
		return lRes;
	}
	break;
	case WM_TANGRAMDATA:
	{
		switch (lParam)
		{
		case 20200202:
		{
			LRESULT lRes = ::DefWindowProc(hWnd, msg, wParam, lParam);
			CHtmlWnd* m_pHtmlWnd = (CHtmlWnd*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
			BindWebObj* pObj = (BindWebObj*)wParam;
			auto it = m_pHtmlWnd->m_mapBindWebObj.find(pObj->m_strBindObjName);
			if (it != m_pHtmlWnd->m_mapBindWebObj.end())
			{
				delete it->second;
				m_pHtmlWnd->m_mapBindWebObj.erase(it);
			}
			m_pHtmlWnd->m_mapBindWebObj[pObj->m_strBindObjName] = pObj;
		}
		break;
		case 20200203:
		{
			LRESULT lRes = ::DefWindowProc(hWnd, msg, wParam, lParam);
			CHtmlWnd* m_pHtmlWnd = (CHtmlWnd*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (m_pHtmlWnd->m_pChromeRenderFrameHost)
			{
				IPCMsg* pMsg = (IPCMsg*)wParam;
				m_pHtmlWnd->m_pChromeRenderFrameHost->SendTangramMessage(pMsg);
				g_pTangram->m_pCurrentIPCMsg = nullptr;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

extern HWND    topWindow;

LRESULT CTangramApp::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (g_pTangram == nullptr)
		return 0;
	LRESULT hr = CallNextHookEx(g_pTangram->m_hCBTHook, nCode, wParam, lParam);
	//TangramCBT(nCode, wParam, lParam);
	HWND hWnd = (HWND)wParam;
	switch (nCode)
	{
	case HCBT_CREATEWND:
	{
		//g_pTangram->Init();
		CBT_CREATEWND* pCreateWnd = (CBT_CREATEWND*)lParam;
		LPCTSTR lpszName = pCreateWnd->lpcs->lpszName;
		HWND hPWnd = pCreateWnd->lpcs->hwndParent;
		DWORD dwID = (DWORD)pCreateWnd->lpcs->hMenu;
		if (::GetWindowLongPtr(hPWnd, GWL_EXSTYLE) & WS_EX_MDICHILD && ::SendMessage(hPWnd, WM_TANGRAMMSG, 0, 19631222) == 0)
		{
			if (g_pTangram->m_nAppType == 0 || g_pTangram->m_nAppType == 1992)
			{
				LRESULT lRes = ::SendMessage(hPWnd, WM_TANGRAMMSG, (WPARAM)pCreateWnd->lpcs->lpCreateParams, TANGRAM_CONST_PANE_FIRST);
				if (g_pTangram->m_nAppType == 0)
					g_pTangram->m_nAppType = lRes;
				if (lRes == 1992 || g_pTangram->m_nAppType == 1992)
				{
					CTangramMDIChildWnd* pMDIChildWnd = new CTangramMDIChildWnd();
					pMDIChildWnd->m_hChild = hWnd;
					pMDIChildWnd->SubclassWindow(hPWnd);
					g_pTangram->m_pActiveMDIChildWnd = pMDIChildWnd;
					pMDIChildWnd->m_bNoDocView = (pCreateWnd->lpcs->lpCreateParams == 0);
					::PostMessage(hPWnd, WM_TANGRAMMSG, 0, 19922017);
				}
			}
		}

		::GetClassName(hWnd, g_pTangram->m_szBuffer, MAX_PATH);
		CString strClassName = CString(g_pTangram->m_szBuffer);
		::GetClassName(hPWnd, g_pTangram->m_szBuffer, MAX_PATH);
		CString strPClassName = CString(g_pTangram->m_szBuffer);

		if (dwID == AFX_IDW_PANE_FIRST)
		{
			int lRes = (int)::SendMessage(hPWnd, WM_TANGRAMMSG, (WPARAM)pCreateWnd->lpcs->lpCreateParams, TANGRAM_CONST_PANE_FIRST);

			switch (lRes)
			{
			case TANGRAM_APP_SDI://for SDI Child
			case TANGRAM_APP_MDT://for MDT Child
			{
				if (g_pTangram->m_pTangramDelegate)
					g_pTangram->m_pTangramDelegate->HookAppDocTemplateInfo();
			}
			case TANGRAM_APP_MDI://for MDI Child
			{
				CTangramMDIChildWnd* pMDIChildWnd = new CTangramMDIChildWnd();
				pMDIChildWnd->m_hChild = hWnd;
				pMDIChildWnd->SubclassWindow(hPWnd);
				g_pTangram->m_pActiveMDIChildWnd = pMDIChildWnd;
				pMDIChildWnd->m_bNoDocView = (pCreateWnd->lpcs->lpCreateParams == 0);
				if (g_pTangram->m_nAppType == 1963)
					g_pTangram->m_mapTangramMDIChildWnd[hPWnd] = pMDIChildWnd;
				::PostMessage(hPWnd, WM_TANGRAMMSG, 0, 19922017);
			}
			break;
			default:
			{
				if (g_pTangram->m_pMDIMainWnd)
				{
					CString strClsName = CString(pCreateWnd->lpcs->lpszClass);
					if (strClsName.CompareNoCase(_T("Tangram Window Class")) && strClsName.CompareNoCase(_T("Tangram Splitter Class")))
						::SendMessage(g_pTangram->m_pMDIMainWnd->m_hWnd, WM_CONTROLBARCREATED, (WPARAM)hPWnd, (LPARAM)hWnd);
				}
				else
				{
					if (g_pTangram->m_pActiveMDIChildWnd && ::IsWindow(g_pTangram->m_pActiveMDIChildWnd->m_hWnd))
					{
						CString strClsName = CString(pCreateWnd->lpcs->lpszClass);
						if (strClsName.CompareNoCase(_T("Tangram Window Class")) && strClsName.CompareNoCase(_T("Tangram Splitter Class")))
							::PostMessage(g_pTangram->m_pActiveMDIChildWnd->m_hWnd, WM_CONTROLBARCREATED, (WPARAM)hPWnd, (LPARAM)hWnd);
					}
				}
			}
			break;
			}
		}

		if (strClassName.Find(_T("WindowsForms10."), 0) == 0) {
			::PostMessage(hWnd, WM_DOTNETCONTROLCREATED, (WPARAM)hWnd, (LPARAM)hPWnd);
		}

		if (strClassName == _T("MDIClient"))
		{
			if (::IsWindow(g_pTangram->m_hHostWnd) == false)
			{
				auto it = g_pTangram->m_mapValInfo.find(_T("designertoolcaption"));
				if (it != g_pTangram->m_mapValInfo.end())
					g_pTangram->m_strDesignerToolBarCaption = OLE2T(it->second.bstrVal);
				g_pTangram->m_hHostWnd = ::CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, _T("Tangram Window Class"), g_pTangram->m_strDesignerToolBarCaption, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 400, 400, NULL, 0, theApp.m_hInstance, NULL);
				g_pTangram->m_hChildHostWnd = ::CreateWindowEx(NULL, _T("Tangram Window Class"), _T(""), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, g_pTangram->m_hHostWnd, 0, theApp.m_hInstance, NULL);
			}
			if (::SendMessage(hPWnd, WM_QUERYAPPPROXY, (WPARAM)pCreateWnd->lpcs->lpCreateParams, TANGRAM_CONST_PANE_FIRST) == 1992)
			{
				if (g_pTangram->m_pMDIMainWnd == nullptr)
				{
					g_pTangram->m_pMDIMainWnd = new CTangramMDIMainWnd();
					g_pTangram->m_pMDIMainWnd->m_hMDIClient = hWnd;
					g_pTangram->m_pMDIMainWnd->SubclassWindow(hPWnd);
					if (g_pTangram->m_pTangramDelegate)
						g_pTangram->m_pTangramDelegate->HookAppDocTemplateInfo();
				}
			}
			::PostMessage(g_pTangram->m_hTangramWnd, WM_MDICLIENTCREATED, (WPARAM)hWnd, (LPARAM)hPWnd);
		}
		else if (strClassName.Find(_T("Afx:ControlBar:")) == 0)
		{
			HWND h = ::GetAncestor(hPWnd, GA_ROOT);
			if (::IsWindow(h))
			{
				::PostMessage(g_pTangram->m_hTangramWnd, WM_CONTROLBARCREATED, (WPARAM)hWnd, (LPARAM)h);
			}
		}
		else if (strClassName.Find(_T("Afx:MiniFrame:")) == 0)
		{
			::PostMessage(hWnd, WM_QUERYAPPPROXY, (WPARAM)hWnd, (LPARAM)19650601);
		}
		else if (strClassName.Find(_T("Afx:RibbonBar:")) == 0)
		{
			CTangramAFXHelperWnd* pRibbonBar = new CTangramAFXHelperWnd();
			pRibbonBar->SubclassWindow(hWnd);
		}
		else if (strClassName == _T("Chrome_RenderWidgetHostHWND"))
		{
			if ((::GetWindowLong(hPWnd, GWL_STYLE) & WS_POPUP) == 0)
			{
				auto it = g_pTangram->m_mapBrowserWnd.find(hPWnd);
				if (it == g_pTangram->m_mapBrowserWnd.end()) {
					ChromePlus::CBrowserWnd* pChromeBrowserWnd = new CComObject<ChromePlus::CBrowserWnd>();
					pChromeBrowserWnd->SubclassWindow(hPWnd);
					g_pTangram->m_mapBrowserWnd[hPWnd] = pChromeBrowserWnd;
					pChromeBrowserWnd->m_pBrowser = g_pTangram->m_pActiveBrowser;
					if (pChromeBrowserWnd->m_pBrowser)
						pChromeBrowserWnd->m_pBrowser->m_pProxy = pChromeBrowserWnd;
					if (g_pTangram->m_pTangramDelegate)
						g_pTangram->m_pTangramDelegate->m_bBrowserWndCreated = true;
				}
				::PostMessage(hPWnd, WM_TANGRAMMSG, 0, (LPARAM)hWnd);
			}
		}
		else if (strClassName.Find(_T("SysTreeView32")) == 0 || strClassName.Find(_T("SysTabControl32")) == 0 || strClassName.Find(_T("SysListView32")) == 0)
		{
			g_pTangram->m_mapTangramCommonCtrl[hWnd] = nullptr;
			::PostMessage(hWnd, WM_TANGRAMMSG, 0, 19820911);
		}
		else if (strClassName.Find(_T("Afx:")) == 0 && (pCreateWnd->lpcs->style & WS_POPUP))
		{
			auto it = g_pTangram->m_mapMDTFrame.find(hPWnd);
			if (it != g_pTangram->m_mapMDTFrame.end())
			{
				ATLTRACE(_T("%x\n"), hWnd);
				::SendMessage(hPWnd, WM_CONTROLBARCREATED, (WPARAM)hWnd, 0);
			}
		}

		if (strPClassName == _T("GenericPane"))
		{
			HWND hWnd = (HWND)wParam;
			if (::IsWindow(hWnd))
			{
				if (::SendMessageW(hPWnd, WM_TANGRAMDATA, 0, 0) == 0)
				{
					CGenericPaneWnd* pWnd = new CGenericPaneWnd();
					pWnd->SubclassWindow(hPWnd);
					pWnd->m_hChild = hWnd;
					::GetWindowText(hWnd, g_pTangram->m_szBuffer, MAX_PATH);
					pWnd->m_strToolType = CString(g_pTangram->m_szBuffer);
					if (pWnd->m_strToolType == _T("WebRuntimeToolBox"))
					{
						g_pTangram->m_mapValInfo[_T("WebRuntimeToolBox")] = CComVariant((__int64)hWnd);
					}
				}
			}

			break;
		}
		if (strClassName == _T("SWT_Window0"))
		{
			if (::IsMenu(::GetMenu(hPWnd)))
				::SendMessage(g_pTangram->m_hTangramWnd, WM_ECLIPSEWORKBENCHCREATED, 1, (LPARAM)hPWnd);
			else if (hPWnd == nullptr)
			{
				if (g_pTangram->m_hEclipseHideWnd == nullptr)
					g_pTangram->m_vecEclipseHideTopWnd.push_back(hWnd);
				::PostMessage(g_pTangram->m_hTangramWnd, WM_ECLIPSEWORKBENCHCREATED, 0, (LPARAM)hWnd);
			}
		}
		else if (HIWORD(pCreateWnd->lpcs->lpszClass))
		{
			g_pTangram->WindowCreated(strClassName, lpszName, hPWnd, hWnd);
			if (g_pTangram->m_pCLRProxy)
			{
				g_pTangram->m_pCLRProxy->WindowCreated(strClassName, lpszName, hPWnd, hWnd);
			}
		}
		if ((pCreateWnd->lpcs->style & WS_CHILD) == 0)
		{
			LRESULT lRes = ::SendMessage(hWnd, WM_QUERYAPPPROXY, 0, 0);
			if (lRes > 0)
			{
				g_pTangram->m_pActiveAppProxy = (ITangramAppProxy*)lRes;
			}
		}
	}
	break;
	case HCBT_DESTROYWND:
	{
		if (g_pTangram && g_pTangram->m_bOfficeApp)
			g_pTangram->WindowDestroy(hWnd);
		else if (/*g_pTangram->m_bChromeShutdown==false&&*/g_pTangram->m_pCLRProxy)
			g_pTangram->m_pCLRProxy->WindowDestroy(hWnd);

		auto it = g_pTangram->m_mapFramePage.find(hWnd);
		if (it != g_pTangram->m_mapFramePage.end())
			g_pTangram->m_mapFramePage.erase(it);
		auto it2 = g_pTangram->m_mapTangramAFXHelperWnd.find(hWnd);
		if (it2 != g_pTangram->m_mapTangramAFXHelperWnd.end())
		{
			g_pTangram->m_mapTangramAFXHelperWnd.erase(it2);
		}
		auto it3 = g_pTangram->m_mapTangramCommonCtrl.find(hWnd);
		if (it3 != g_pTangram->m_mapTangramCommonCtrl.end())
			g_pTangram->m_mapTangramCommonCtrl.erase(it3);
		if (g_pTangram->m_pTangramPackageProxy)
		{
			auto it = g_pTangram->m_pTangramPackageProxy->m_mapWinFormCompositor.find(hWnd);
			if (it != g_pTangram->m_pTangramPackageProxy->m_mapWinFormCompositor.end())
				g_pTangram->m_pTangramPackageProxy->m_mapWinFormCompositor.erase(it);
		}
		if (hWnd == g_pTangram->m_hMainWnd)
		{
			if (theApp.m_bHostCLR && g_pTangram->m_nAppType == TANGRAM_APP_BROWSERAPP)
				g_pTangram->m_nAppType = TANGRAM_APP_BROWSER;

			//while (g_pTangram->m_mapBrowserWnd.size())
			//{
			//	auto it = g_pTangram->m_mapBrowserWnd.begin();
			//	if(it!= g_pTangram->m_mapBrowserWnd.end())
			//		::DestroyWindow(it->first);
			//}
			::DestroyWindow(g_pTangram->m_hHostWnd);
			if (theApp.m_bHostCLR && g_pTangram->m_nAppType == 0)
				::PostQuitMessage(20191116);
		}
	}
	break;
	case HCBT_MINMAX:
		switch (lParam)
		{
		case SW_MINIMIZE:
		{
			if (::GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_MDICHILD)
				::PostMessage(hWnd, WM_MDICHILDMIN, 0, 0);
		}
		break;
		case SW_RESTORE:
		case SW_MAXIMIZE:
		{
			::PostMessage(hWnd, WM_TANGRAMMSG, 1, 20200115);
		}
		break;
		}
		break;
	case HCBT_SETFOCUS:
		if (g_pTangram->m_bOfficeApp && g_pTangram->m_nAppID != -1)
			((COfficeAddin*)g_pTangram)->SetFocus(hWnd);
		break;
	case HCBT_ACTIVATE:
	{
		g_pTangram->m_hActiveWnd = hWnd;
		if (g_pTangram->m_pCLRProxy)
		{
			g_pTangram->m_bWinFormActived = g_pTangram->m_pCLRProxy->IsWinForm(hWnd);
			if (g_pTangram->m_bWinFormActived)
			{
				g_pTangram->m_pCompositor = nullptr;
			}
		}
		LRESULT lRes = ::SendMessage(hWnd, WM_QUERYAPPPROXY, 0, 0);
		if (lRes > 0)
		{
			g_pTangram->m_pActiveAppProxy = (ITangramAppProxy*)lRes;
			auto it = g_pTangram->m_mapMDTFrame.find(hWnd);
			if (it != g_pTangram->m_mapMDTFrame.end())
			{
				g_pTangram->m_pActiveAppProxy->OnActiveMainFrame(hWnd);
			}
			else
			{
				auto it = g_pTangram->m_mapWorkBenchWnd.find(hWnd);
				if (it != g_pTangram->m_mapWorkBenchWnd.end())
				{
					CEclipseWnd* pWnd = (CEclipseWnd*)it->second;
					g_pTangram->m_pActiveAppProxy->OnActiveMainFrame(::GetParent(pWnd->m_hClient));
				}
			}
		}
		else
			g_pTangram->m_pActiveAppProxy = nullptr;
	}
	break;
	}
	return hr;
}

static bool g_bRecturnPressed = false;

LRESULT CALLBACK CTangramApp::GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSG lpMsg = (LPMSG)lParam;
	DWORD dwID = ::GetCurrentThreadId();
	TangramThreadInfo* pThreadInfo = g_pTangram->GetThreadInfo(dwID);
	if (lpMsg->message == WM_TIMER)
		return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
	if (nCode >= 0)
	{
		switch (wParam)
		{
		case PM_NOREMOVE:
		{
			switch (lpMsg->message)
			{
			case WM_QUIT:
			{
				if (::GetCurrentThreadId() == g_pTangram->m_dwThreadID)
				{
					if (::IsWindow(g_pTangram->m_hHostWnd))
						::DestroyWindow(g_pTangram->m_hHostWnd);
					if (::IsWindow(g_pTangram->m_hTangramWnd))
						::DestroyWindow(g_pTangram->m_hTangramWnd);
				}
				if (g_pTangram->m_pTangramCLRAppProxy)
					g_pTangram->m_pTangramCLRAppProxy->OnTangramClose();
			}
			break;
			default:
				break;
			}
		}
		break;
		case PM_REMOVE:
		{
			switch (lpMsg->message)
			{
			case WM_SYSKEYDOWN:
			{
				if (::GetAsyncKeyState(VK_MENU) < 0 &&
					g_pTangram->m_pTangramDelegate &&
					g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
				{
					return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
				}
			}
			break;
			case WM_KEYDOWN:
			{
				CNodeWnd* pWnd = nullptr;
				CWPFView* pView = nullptr;
				if (g_pTangram->m_bOMNIBOXPOPUPVISIBLE && lpMsg->wParam == VK_RETURN)
				{
					g_bRecturnPressed = true;
				}
				if (g_pTangram->m_pActiveNode)
				{
					if (g_pTangram->m_pActiveNode->m_nViewType != Splitter)
					{
						if (g_pTangram->m_pActiveNode->m_nViewType == TangramWPFCtrl)
							pView = (CWPFView*)g_pTangram->m_pActiveNode->m_pHostWnd;
						else
							pWnd = (CNodeWnd*)g_pTangram->m_pActiveNode->m_pHostWnd;
						if (pWnd && ::IsChild(pWnd->m_hWnd, lpMsg->hwnd) == false)
						{
							g_pTangram->m_pActiveNode = nullptr;
							if (lpMsg->wParam != VK_TAB)
								break;
							else if (g_pTangram->m_bWinFormActived == false)
							{
								if (pWnd->m_bBKWnd)
								{
									if (pWnd->PreTranslateMessage(lpMsg))
									{
										lpMsg->hwnd = NULL;
										lpMsg->lParam = 0;
										lpMsg->wParam = 0;
										lpMsg->message = 0;
										break;
									}
								}
								else if (pView)
								{
									if (pView->PreTranslateMessage(lpMsg))
									{
										lpMsg->hwnd = NULL;
										lpMsg->lParam = 0;
										lpMsg->wParam = 0;
										lpMsg->message = 0;
										break;
									}
								}
								else
									g_pTangram->m_pCompositor = nullptr;
							}
						}
					}
					//else
					//	break;
				}

				switch (lpMsg->wParam)
				{
				case VK_TAB:
					if (g_pTangram->m_bWinFormActived && g_pTangram->m_bEnableProcessFormTabKey && g_pTangram->m_pCLRProxy->ProcessFormMsg(g_pTangram->m_hActiveWnd, lpMsg, 0))
					{
						break;
					}
					if (g_pTangram->m_pCompositor && g_pTangram->m_pActiveNode && pWnd && pWnd->PreTranslateMessage(lpMsg))
					{
						lpMsg->hwnd = NULL;
						lpMsg->lParam = 0;
						lpMsg->wParam = 0;
						lpMsg->message = 0;
					}
					else
					{
						HWND hwnd = lpMsg->hwnd;
						if ((pView && pView->PreTranslateMessage(lpMsg))/*|| IsDialogMessage(lpMsg->hwnd, lpMsg)*/)
						{
							::DispatchMessage(lpMsg);
							TranslateMessage(lpMsg);
							lpMsg->hwnd = NULL;
							lpMsg->lParam = 0;
							lpMsg->wParam = 0;
							lpMsg->message = 0;
						}
						else
						{
							if (::GetModuleHandle(_T("chrome.dll")))
							{
								TRACE(_T("======== CTangramApp=========:%x,MSG:%x\n"), lpMsg->hwnd, lpMsg->message);
								if (g_pTangram->m_pActiveHtmlWnd)
								{
									HWND hWnd = ::GetParent(::GetParent(g_pTangram->m_pActiveHtmlWnd->m_hWnd));
									if (hWnd)
									{
										TranslateMessage(lpMsg);
										::DispatchMessage(lpMsg);
										lpMsg->hwnd = NULL;
										lpMsg->lParam = 0;
										lpMsg->wParam = 0;
										lpMsg->message = 0;
										return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
									}
								}
							}
							if (pWnd && pWnd->PreTranslateMessage(lpMsg))
							{
								::DispatchMessage(lpMsg);
								TranslateMessage(lpMsg);
								lpMsg->hwnd = NULL;
								lpMsg->lParam = 0;
								lpMsg->wParam = 0;
								lpMsg->message = 0;
							}

							//g_pTangram->ProcessMsg(lpMsg);
						}
						if (((__int64)g_pTangram->m_pActiveAppProxy) > 1)
							g_pTangram->m_pActiveAppProxy->TangramPreTranslateMessage(lpMsg);
						//else if (((__int64)g_pTangram->m_pTangramAppProxy) > 1)
						//{
						//	g_pTangram->m_pTangramAppProxy->TangramPreTranslateMessage(lpMsg);
						//}
					}
					break;
				case VK_PRIOR:
				case VK_NEXT:
				case VK_HOME:
				case VK_END:
				case VK_LEFT:
				case VK_UP:
				case VK_RIGHT:
				case VK_DOWN:
				case VK_BACK:
					if (g_pTangram->m_bWinFormActived && g_pTangram->m_bEnableProcessFormTabKey && g_pTangram->m_pCLRProxy->ProcessFormMsg(g_pTangram->m_hActiveWnd, lpMsg, 0))
					{
						TranslateMessage(lpMsg);
						::DispatchMessage(lpMsg);
						lpMsg->hwnd = NULL;
						lpMsg->lParam = 0;
						lpMsg->wParam = 0;
						lpMsg->message = 0;
						return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
						break;
					}
					if (g_pTangram->m_pCompositor && g_pTangram->m_pActiveNode && pWnd && pWnd->PreTranslateMessage(lpMsg))
					{
						if (g_pTangram->m_pCLRProxy && g_pTangram->m_pCLRProxy->IsWinForm(pWnd->m_hWnd))
						{
							//TranslateMessage(lpMsg);
							::DispatchMessage(lpMsg);
							//lpMsg->hwnd = NULL;
							//lpMsg->lParam = 0;
							//lpMsg->wParam = 0;
							//lpMsg->message = 0;
							return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
						}
						lpMsg->hwnd = NULL;
						lpMsg->lParam = 0;
						lpMsg->wParam = 0;
						lpMsg->message = 0;
						return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
					}
					if (pView)
					{
						TranslateMessage(lpMsg);
						::DispatchMessage(lpMsg);
						lpMsg->hwnd = NULL;
						lpMsg->lParam = 0;
						lpMsg->wParam = 0;
						lpMsg->message = 0;
					}
					if (g_pTangram->m_pTangramDelegate)
					{
						if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
							break;
					}
					break;
				case VK_DELETE:
					if (g_pTangram->m_pActiveNode)
					{
						if (g_pTangram->m_pActiveNode->m_nViewType == ActiveX)
						{
							pWnd->PreTranslateMessage(lpMsg);
							lpMsg->hwnd = NULL;
							lpMsg->wParam = 0;
							break;
						}
						DispatchMessage(lpMsg);
						lpMsg->hwnd = NULL;
						lpMsg->wParam = 0;
					}

					break;
				case VK_RETURN:
				{
					if (g_pTangram->m_pTangramDelegate)
					{
						if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
							break;
					}
					if (g_pTangram->m_pCompositor && g_pTangram->m_pActiveNode)
					{
						if (pWnd && ::IsChild(pWnd->m_hWnd, lpMsg->hwnd) == false)
						{
							g_pTangram->m_pActiveNode = nullptr;
							g_pTangram->m_pCompositor = nullptr;
						}
						else if (pWnd)
						{
							TranslateMessage(lpMsg);
							lpMsg->hwnd = NULL;
							lpMsg->lParam = 0;
							lpMsg->wParam = 0;
							lpMsg->message = 0;
							break;
						}
					}
					if (g_pTangram->m_bOfficeApp)
						return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
					TranslateMessage(lpMsg);
					if (g_pTangram->m_strExeName != _T("devenv"))
					{
						DispatchMessage(lpMsg);
						lpMsg->hwnd = NULL;
						lpMsg->lParam = 0;
						lpMsg->wParam = 0;
						lpMsg->message = 0;
						return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
					}
				}
				break;
				case 0x41://Ctrl+A
				case 0x43://Ctrl+C
				case 0x56://Ctrl+V
				case 0x58://Ctrl+X
				case 0x5a://Ctrl+Z
					if (::GetKeyState(VK_CONTROL) < 0)  // control pressed
					{
						if (g_pTangram->m_pActiveNode && pWnd && !::IsWindow(pWnd->m_hWnd))
						{
							g_pTangram->m_pActiveNode = nullptr;
						}
						if (g_pTangram->m_pActiveNode)
						{
							HWND hWnd = nullptr;
							if (pWnd)
								hWnd = pWnd->m_hWnd;
							else if (pView)
								hWnd = pView->m_hWnd;
							if ((g_pTangram->m_pActiveNode->m_nViewType == ActiveX || g_pTangram->m_pActiveNode->m_strID.CompareNoCase(_T("hostview")) == 0))
							{
								if (pWnd)
									pWnd->PreTranslateMessage(lpMsg);
								lpMsg->hwnd = NULL;
								lpMsg->wParam = 0;
								break;
							}
							if (pView)
							{
								TranslateMessage(lpMsg);
								::DispatchMessage(lpMsg);
								lpMsg->hwnd = NULL;
								lpMsg->lParam = 0;
								lpMsg->wParam = 0;
								lpMsg->message = 0;
								break;
							}
							if (g_pTangram->m_pActiveHtmlWnd)
							{
								HWND hwnd = lpMsg->hwnd;
								HWND hWnd = ::GetParent(::GetParent(g_pTangram->m_pActiveHtmlWnd->m_hWnd));
								if (hWnd)
								{
									TranslateMessage(lpMsg);
									::DispatchMessage(lpMsg);
									lpMsg->hwnd = NULL;
									lpMsg->lParam = 0;
									lpMsg->wParam = 0;
									lpMsg->message = 0;
									return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
								}
							}
							TranslateMessage(lpMsg);
							lpMsg->wParam = 0;
						}
						else
						{
							//if (g_pTangram->m_pTangramDelegate && theApp.m_bHostCLR == false)
							//{
							//	TranslateMessage(lpMsg);
							//	::DispatchMessage(lpMsg);
							//	break;
							//}
						}
					}
					break;
				}
			}
			break;
			case WM_TANGRAMINIT:
			{
				if (lpMsg->wParam == 20191005)
					g_pTangram->Init();
			}
			break;
			case WM_MOUSEMOVE:
				//if (g_pTangram->m_bEclipse)
			{
				//if (MK_LBUTTON == lpMsg->wParam)
				//{
				//	CWnd* pWnd = nullptr;
				//	if (g_pTangram->m_pActiveNode)
				//		pWnd = (CNodeWnd*)g_pTangram->m_pActiveNode->m_pHostWnd;
				//	if (g_pTangram->m_pCompositor && g_pTangram->m_pActiveNode && pWnd && pWnd->PreTranslateMessage(lpMsg))
				//	{
				//		if (g_pTangram->m_pCLRProxy->IsWinForm(pWnd->m_hWnd))
				//		{
				//			TranslateMessage(lpMsg);
				//			::DispatchMessage(lpMsg);
				//		}
				//		return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
				//	}
				//}
				if (lpMsg->hwnd == topWindow || ::IsChild(topWindow, lpMsg->hwnd))
				{
					static CPoint PrePoint = CPoint(0, 0);
					if (MK_LBUTTON == lpMsg->wParam)
					{
						CPoint point = CPoint(GET_X_LPARAM(lpMsg->lParam), GET_Y_LPARAM(lpMsg->lParam));
						if (point != PrePoint)
						{
							CPoint ptTemp = point - PrePoint;
							CRect rcWindow;
							::GetWindowRect(topWindow, &rcWindow);
							rcWindow.OffsetRect(ptTemp.x, ptTemp.y);
							::MoveWindow(topWindow, rcWindow.left, rcWindow.top, rcWindow.Width(), rcWindow.Height(), true);
						}
						PrePoint = point;
					}
					break;
				}
				if ((long)(g_pTangram->m_pActiveAppProxy) > 1)
				{
					g_pTangram->m_pActiveAppProxy->MouseMoveProxy(lpMsg->hwnd);
				}
				else if (g_pTangram->m_pTangramAppProxy)
				{
					g_pTangram->m_pTangramAppProxy->MouseMoveProxy(lpMsg->hwnd);
				}
				if (g_pTangram->m_pTangramDelegate)
				{
					if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
						break;
				}
				if ((long)(g_pTangram->m_pActiveAppProxy) > 1)
					g_pTangram->m_pActiveAppProxy->TangramPreTranslateMessage(lpMsg);
				else if (g_pTangram->m_pTangramAppProxy)
					g_pTangram->m_pTangramAppProxy->TangramPreTranslateMessage(lpMsg);
			}
			break;
			case WM_NCLBUTTONDOWN:
			case WM_NCRBUTTONDOWN:
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
				//case WM_POINTERDOWN:
				//case WM_POINTERUP:
			case WM_SETWNDFOCUSE:
			{
				g_pTangram->ProcessMsg(lpMsg);
				//::DispatchMessage(lpMsg);
				//for m_strStartupCLRObj support
				//if (g_pTangram->m_pActiveTangramWinFormWnd && g_pTangram->m_bEnableProcessFormTabKey && g_pTangram->m_pCLRProxy->ProcessFormMsg(g_pTangram->m_pActiveTangramWinFormWnd->m_hWnd, lpMsg, 0))
				//{
				//	TranslateMessage(lpMsg);
				//	::DispatchMessage(lpMsg);
				//	//lpMsg->hwnd = NULL;
				//	//lpMsg->lParam = 0;
				//	//lpMsg->wParam = 0;
				//	//lpMsg->message = 0;
				//	return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
				//	break;
				//}
				if (lpMsg->message == WM_LBUTTONDOWN || lpMsg->message == WM_LBUTTONUP)
				{
					if (g_pTangram->m_pActiveTangramWinFormWnd)
					{
						//::SendMessage(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
						g_pTangram->m_pCLRProxy->ProcessFormMsg(g_pTangram->m_pActiveTangramWinFormWnd->m_hWnd, lpMsg, 0);
					}
				}
				if ((long)(g_pTangram->m_pActiveAppProxy) > 1)
					g_pTangram->m_pActiveAppProxy->TangramPreTranslateMessage(lpMsg);
				else if (g_pTangram->m_pTangramAppProxy)
					g_pTangram->m_pTangramAppProxy->TangramPreTranslateMessage(lpMsg);
				if (g_pTangram->m_pTangramDelegate)
				{
					if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
						break;
				}
				return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
			}
			break;
			case WM_MDICHILDMIN:
				::BringWindowToTop(lpMsg->hwnd);
				break;
			case WM_CHROMEAPPINIT:
			{
				if (lpMsg->lParam == TANGRAM_APP_WIN32 ||
					lpMsg->lParam == TANGRAM_APP_ECLIPSE)
					break;
				typedef int(__stdcall* _InitApp)(bool bSupportCrashReporting);
				_InitApp FuncInitApp;
				HMODULE hModule = ::GetModuleHandle(L"tangram_chrome_rt.dll");
				if (hModule == nullptr)
					hModule = ::LoadLibrary(L"tangram_chrome_rt.dll");
				if (hModule) {
					FuncInitApp = (_InitApp)GetProcAddress(hModule, "InitApp");
					if (FuncInitApp != NULL) {
						HWND hWnd = g_pTangram->m_pTangramDelegate->GetMainWnd();
						if (::IsWindow(hWnd))
						{
							g_pTangram->m_hMainWnd = hWnd;
						}
						g_pTangram->m_pTangramDelegate->BeginBrowserSession();
						FuncInitApp(false);
						g_pTangram->m_pTangramDelegate->EndBrowserSession();
						::PostQuitMessage(0);
					}
				}
			}
			break;
			case WM_DOWNLOAD_MSG:
			{
				Utilities::CDownLoadObj* pObj = (Utilities::CDownLoadObj*)lpMsg->wParam;
				if (pObj)
					delete pObj;
			}
			break;
			case WM_NAVIXTML:
			{
				RECT rc;
				HWND hWnd = ::GetParent(lpMsg->hwnd);
				::GetClientRect(hWnd, &rc);
				::SetWindowPos(lpMsg->hwnd, HWND_BOTTOM, rc.left, rc.top, rc.right + 1, rc.bottom, SWP_NOZORDER | SWP_FRAMECHANGED);
				::SetWindowPos(lpMsg->hwnd, HWND_BOTTOM, rc.left, rc.top, rc.right, rc.bottom, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			break;
			case WM_TANGRAM_WEBNODEDOCCOMPLETE:
			{
				auto it = g_pTangram->m_mapWindowPage.find((HWND)lpMsg->wParam);
				if (it != g_pTangram->m_mapWindowPage.end())
					((CCompositorManager*)it->second)->OnNodeDocComplete(lpMsg->wParam);
			}
			break;
			case WM_CHROMEDEVTOOLMSG:
			{
				switch (lpMsg->wParam)
				{
				case 1:
				{
					g_pTangram->m_bCreatingDevTool = true;
					auto it = g_pTangram->m_mapBrowserWnd.find(::GetActiveWindow());
					if (it != g_pTangram->m_mapBrowserWnd.end())
					{
						ATLTRACE(_T("\n"));
					}
				}
				break;
				}
			}
			break;
			case WM_TANGRAMMSG:
			{
				switch (lpMsg->lParam)
				{
				case 20191114:
				{
					if (g_pTangram->m_mapCreatingWorkBenchInfo.size())
					{
						g_pTangram->InitEclipseApp();
					}
				}
				break;
				case 20191004:
				{
					if (g_pTangram->m_pCLRProxy)
					{
						g_pTangram->m_pCLRProxy->TangramAction(CComBSTR("setmainform"), nullptr);
					}
				}
				break;
				case 20190511:
				{
					if (lpMsg->wParam && g_pTangram->m_bEclipse == false)
						::DestroyWindow(g_pTangram->m_hHostWnd);
				}
				break;
				case 20191117:
				{
					if (g_pTangram->m_pTangramDelegate)
						g_pTangram->m_pTangramDelegate->EclipseAppInit();
				}
				break;
				case 2019111701:
				{
					if (g_pTangram->m_mapNodeForHtml.size())
					{
						for (auto it : g_pTangram->m_mapNodeForHtml)
						{
							it.first->put_URL(CComBSTR(it.second));
						}
						g_pTangram->m_mapNodeForHtml.erase(g_pTangram->m_mapNodeForHtml.begin(), g_pTangram->m_mapNodeForHtml.end());
					}
					CString strHelper = g_pTangram->m_strAppPath + _T("tangramhelper.xml");
					if (::PathFileExists(strHelper))
					{
						CTangramXmlParse m_Parse;
						if (m_Parse.LoadFile(strHelper))
						{
							switch (g_pTangram->m_nAppType)
							{
							case TANGRAM_APP_BROWSER:
							case TANGRAM_APP_BROWSERAPP:
							case TANGRAM_APP_BROWSER_ECLIPSE:
							{
								CTangramXmlParse* pChild = nullptr;
								if (g_pTangram->m_nAppType == TANGRAM_APP_BROWSERAPP)
									pChild = m_Parse.GetChild(_T("browser_app"));
								else if (g_pTangram->m_nAppType == TANGRAM_APP_BROWSER)
									pChild = m_Parse.GetChild(_T("browser"));
								else
									pChild = m_Parse.GetChild(_T("browser_eclipse"));
								if (pChild)
								{
									int nCount = pChild->GetCount();
									CString strUrls = _T("");
									for (int i = 0; i < nCount; i++)
									{
										CString strUrl = pChild->GetChild(i)->text();
										int nPos2 = strUrl.Find(_T(":"));
										if (nPos2 != -1)
										{
											CString strURLHeader = strUrl.Left(nPos2);
											if (strURLHeader.CompareNoCase(_T("host")) == 0)
											{
												strUrl = g_pTangram->m_strAppPath + strUrl.Mid(nPos2 + 1);
											}
										}
										strUrls += strUrl;
										strUrls += _T("|");
									}
									if (nCount)
										g_pTangram->m_pBrowserFactory->CreateBrowser(NULL, strUrls);
								}
							}
							break;
							case TANGRAM_APP_WIN32:
							case TANGRAM_APP_ECLIPSE:
							{
								//HMODULE hModule = ::GetModuleHandle(L"tangram_chrome_rt.dll");
								//if (hModule == nullptr)
								//	hModule = ::LoadLibrary(L"tangram_chrome_rt.dll");
								//if (hModule) {
								//	typedef int(__stdcall* _InitApp)(bool bSupportCrashReporting);
								//	_InitApp _pInitAppFunction;
								//	_pInitAppFunction = (_InitApp)GetProcAddress(hModule, "InitApp");
								//	if (_pInitAppFunction != NULL) {
								//		_pInitAppFunction(false);
								//	}
								//}
							}
							break;
							}
						}
					}
				}
				break;
				case 20191022:
				{
					if (g_pTangram->m_pCLRProxy)
					{
						g_pTangram->m_pCLRProxy->TangramAction(CComBSTR("startclrapp"), nullptr);
					}
				}
				break;
				}
			}
			break;
			case WM_TANGRAMAPPQUIT:
			{
				TRACE(_T("======== WM_TANGRAMAPPQUIT=========\n"));
				if (g_pTangram->m_bEclipse == false && g_pTangram->m_bOfficeApp == false)
				{
					if (g_pTangram->m_pMDIMainWnd == NULL && g_pTangram->m_mapMDTFrame.size() == 0)
					{
						if (g_pTangram->m_mapBrowserWnd.size())
						{
							g_pTangram->m_bChromeNeedClosed = true;
							auto it = g_pTangram->m_mapBrowserWnd.begin();
							((ChromePlus::CBrowserWnd*)it->second)->SendMessageW(WM_CLOSE, 0, 0);
						}
					}
				}
			}
			break;
			case WM_CHROMEOMNIBOXPOPUPVISIBLE:
			{
				g_pTangram->m_bOMNIBOXPOPUPVISIBLE = lpMsg->lParam ? true : false;
				auto it = g_pTangram->m_mapBrowserWnd.find((HWND)lpMsg->wParam);
				if (it != g_pTangram->m_mapBrowserWnd.end())
				{
					CHtmlWnd* pWnd = ((CBrowserWnd*)it->second)->m_pVisibleWebWnd;
					if (pWnd && ::IsWindow(pWnd->m_hWnd) && pWnd->m_pCompositor)
					{
						IWndNode* pNode = nullptr;
						if (g_bRecturnPressed == false)
						{
							pWnd->m_pCompositor->Open(CComBSTR(lpMsg->lParam ? _T("__default__key__for__chrome__") : pWnd->m_strCurKey), CComBSTR(lpMsg->lParam ? g_pTangram->m_strDefaultXml : _T("")), &pNode);
							::SendMessage(it->first, WM_BROWSERLAYOUT, 0, 2);
						}
						g_bRecturnPressed = false;
					}
				}
			}
			break;
			case WM_DOTNETCONTROLCREATED:
			{
				g_pTangram->DotNetControlCreated(lpMsg);
			}
			break;
			}

			//if (lpMsg->message != WM_TIMER)
			//{
			//	//ITangramAppProxy* pProxy = g_pTangram->m_pActiveAppProxy;
			//	//if (pProxy == nullptr)
			//	//	pProxy = g_pTangram->m_pTangramAppProxy;
			//	//if (pProxy)
			//	{
			//		switch (lpMsg->message)
			//		{
			//		case WM_CHAR:
			//			if (g_pTangram->m_pTangramDelegate)
			//			{
			//				if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
			//					break;
			//			}
			//		case WM_KEYDOWN:
			//		{
			//			switch (lpMsg->wParam)
			//			{
			//			case VK_TAB:
			//			case VK_PRIOR:
			//			case VK_NEXT:
			//			case VK_HOME:
			//			case VK_END:
			//			case VK_LEFT:
			//			case VK_UP:
			//			case VK_RIGHT:
			//			case VK_DOWN:
			//			case VK_DELETE:
			//			case VK_BACK:
			//			case VK_RETURN:
			//			case 0x41://Ctrl+A
			//			case 0x43://Ctrl+C
			//			case 0x56://Ctrl+V
			//			case 0x58://Ctrl+X
			//			case 0x5a://Ctrl+Z
			//				break;
			//			}
			//		}
			//		break;
			//		//case WM_LBUTTONDOWN:
			//		////case WM_RBUTTONUP:
			//		//case WM_LBUTTONUP:
			//		//case WM_LBUTTONDBLCLK:
			//		//{
			//		//	if (g_pTangram->m_pTangramDelegate)
			//		//	{
			//		//		if (g_pTangram->m_pTangramDelegate->OnTangramPreTranslateMessage(lpMsg))
			//		//			break;
			//		//	}
			//		//	if (g_pTangram->m_pActiveNode && g_pTangram->m_pActiveNode->m_nViewType == TangramListView)
			//		//	{
			//		//		((CTangramListView*)g_pTangram->m_pActiveNode->m_pHostWnd)->PreTranslateMessage(lpMsg);
			//		//	}
			//		//}
			//		//break;
			//		default:
			//		{
			//			if (g_pTangram->m_bOfficeApp == false)
			//			{
			//				if (g_pTangram->m_pActiveNode && g_pTangram->m_pActiveNode->m_nViewType == TangramListView)
			//					((CTangramListView*)g_pTangram->m_pActiveNode->m_pHostWnd)->PreTranslateMessage(lpMsg);
			//				else if ((long)(g_pTangram->m_pActiveAppProxy) > 1)
			//					g_pTangram->m_pActiveAppProxy->TangramPreTranslateMessage(lpMsg);
			//			}
			//		}
			//		break;
			//		}
			//	}
			//}
		}
		break;
		default:
			break;
		}
	}

	return CallNextHookEx(pThreadInfo->m_hGetMessageHook, nCode, wParam, lParam);
}

void CTangramApp::SetHook(DWORD ThreadID)
{
	TangramThreadInfo* pThreadInfo = g_pTangram->GetThreadInfo(ThreadID);
	if (pThreadInfo && pThreadInfo->m_hGetMessageHook == NULL)
	{
		pThreadInfo->m_hGetMessageHook = SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, NULL, ThreadID);
	}
}

CString CTangramApp::GetFileVer()
{
	DWORD dwHandle, InfoSize;
	CString strVersion;

	struct LANGANDCODEPAGE
	{
		WORD wLanguage;
		WORD wCodePage;
	}*lpTranslate;
	unsigned int cbTranslate = 0;

	TCHAR cPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, cPath, MAX_PATH);
	InfoSize = GetFileVersionInfoSize(cPath, &dwHandle);


	char* InfoBuf = new char[InfoSize];

	GetFileVersionInfo(cPath, 0, InfoSize, InfoBuf);
	VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &cbTranslate);

	TCHAR SubBlock[300] = { 0 };

	//ProductVersion
	//FileVersion

	wsprintf(SubBlock, TEXT("\\StringFileInfo\\%04x%04x\\ProductVersion"), lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);

	TCHAR* lpBuffer = NULL;
	unsigned int dwBytes = 0;
	VerQueryValue(InfoBuf, SubBlock, (void**)&lpBuffer, &dwBytes);
	if (lpBuffer != NULL)
	{
		strVersion.Format(_T("%s"), (TCHAR*)lpBuffer);
	}

	delete[] InfoBuf;
	return strVersion;
}

HRESULT CTangramApp::UpdateRegistry(BOOL bRegister)
{
	return theApp.UpdateRegistryFromResource(IDR_TANGRAM, bRegister);
}

HRESULT CTangramApp::CreateInstance(void* pv, REFIID riid, LPVOID* ppv)
{
	if (g_pTangram)
	{
		DWORD dwID = ::GetCurrentThreadId();
		if (dwID != g_pTangram->m_dwThreadID)
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

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (g_pTangram)
	{
		bool bCanUnLoad = false;
		if (g_pTangram->m_bOfficeApp)
			bCanUnLoad = g_pTangram->m_bOfficeAddinUnLoad;
		if (::GetModuleHandle(L"chrome_elf.dll"))
			bCanUnLoad = false;
		if (bCanUnLoad && g_pTangram && g_pTangram->m_nTangramObj == 0)
		{
			g_pTangram->ExitInstance();
			delete g_pTangram;
			g_pTangram = nullptr;
			return S_OK;
		}
	}
	//return (theApp.DllCanUnloadNow() == S_OK && theApp.GetLockCount() == 0) ? S_OK : S_FALSE;
	return (AfxDllCanUnloadNow() == S_OK && theApp.GetLockCount() == 0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return theApp.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
	//theApp.m_bRegisterServer = true;
	return theApp.DllRegisterServer();
}

STDAPI DllUnregisterServer(void)
{
	return theApp.DllUnregisterServer();
}

JNIEXPORT void JNICALL Java_Tangram_Host_Tangram_InitTangram(JNIEnv* env, jobject obj, jobject jTangram, jobject jCompositorManager, jobject jCompositor, jobject jWndNode)
{
	jclass cls = env->GetObjectClass(obj);

	return;
}

//查找指定进程  
DWORD FindProcess(TCHAR* strProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cbMNeeded;
	HMODULE hMods[1024];
	HANDLE hProcess;
	TCHAR szProcessName[MAX_PATH];

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return 0;
	for (int i = 0; i < (int)(cbNeeded / sizeof(DWORD)); i++)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		GetModuleFileNameEx(hProcess, hMods[0], szProcessName, sizeof(szProcessName));

		CString strPrcFullName(szProcessName);
		CString strPrcName(strProcessName);
		if (_tcsstr(strPrcFullName, strPrcName) || _tcsstr(strPrcFullName, strPrcName.MakeLower()))
		{
			CString strNameFull;
			strNameFull.Format(_T("Process full name：\n%s;"), szProcessName);
			return(aProcesses[i]);
		}
	}

	return 0;
}

// 此函数利用上面的 FindProcess 函数获得你的目标进程的ID  
// 用WIN API OpenPorcess 获得此进程的句柄，再以TerminateProcess强制结束这个进程  
VOID KillProcess(TCHAR* strProcessName)
{
	// When the all operation fail this function terminate the "winlogon" Process for force exit the system.  
	HANDLE hTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION | // Required by Alpha  
		PROCESS_CREATE_THREAD | // For CreateRemoteThread  
		PROCESS_VM_OPERATION | // For VirtualAllocEx/VirtualFreeEx  
		PROCESS_VM_WRITE | // For WriteProcessMemory  
		PROCESS_TERMINATE, //Required to terminate a process using TerminateProcess function  
		FALSE, FindProcess(strProcessName));

	if (hTargetProcess == NULL)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(L"OpenProcess failed,error code:%ld", ulErrCode);
		AfxMessageBox(strError);
	}

	BOOL result = TerminateProcess(hTargetProcess, 0);
	if (!result)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(L"TerminateProcess failed,error code:%ld", ulErrCode);
		AfxMessageBox(strError);
	}
	return;
}


