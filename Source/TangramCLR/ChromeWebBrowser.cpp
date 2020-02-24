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
*
********************************************************************************/

#include "stdafx.h"
#include "dllmain.h"
#include "TangramClrProxy.h"
#include "ChromeWebBrowser.h"
#include "TangramObj.h"

extern CTangramCLRProxy theAppProxy;

using namespace std;
using namespace System;
using namespace System::Windows;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Threading::Tasks;

using System::Runtime::InteropServices::Marshal;

namespace TangramCLR
{
	ChromeWebBrowser::ChromeWebBrowser(IChromeWebBrowser* pChromeWebBrowser)
	{
		m_pChromeWebBrowserHost = pChromeWebBrowser;
	}

	void ChromeWebBrowser::AddURLs(String^ urls)
	{
		BSTR bstrUrl = STRING2BSTR(urls);
		if (m_pChromeWebBrowserHost)
		{
			m_pChromeWebBrowserHost->OpenURL(bstrUrl, BrowserWndOpenDisposition::NEW_FOREGROUND_TAB, L"", L"");
		}
	}

	void ChromeWebBrowser::OpenURL(String^ url, Disposition disposition, String^ key, String^ xml)
	{
		BSTR bstrUrl = STRING2BSTR(url);
		BSTR bstrKey = STRING2BSTR(key);
		BSTR bstrXml = STRING2BSTR(xml);
		if (m_pChromeWebBrowserHost)
		{
			m_pChromeWebBrowserHost->OpenURL(bstrUrl, (BrowserWndOpenDisposition)disposition, bstrKey, bstrXml);
		}
	}

	ChromeWebPage::ChromeWebPage(IChromeWebPage* pChromeWebPage)
	{
		m_pChromeWebPage = pChromeWebPage;
	}
	
	IntPtr ChromeWebPage::Handle::get()
	{
		//if (m_hWnd==NULL&&m_pChromeWebPage)
		//{
		//	__int64 nHandle = 0;
		//	m_pChromeWebPage->get_HostWnd(&nHandle);
		//	m_hWnd = (HWND)nHandle;
		//}
		return (IntPtr)m_hWnd;
	}
	
	WndNode^ ChromeWebPage::ParentNode::get()
	{
		return theAppProxy._createObject<IWndNode, WndNode>(m_pProxy->GetParentNode());
	}
	
	Compositor^ ChromeWebPage::HostCompositor::get()
	{
		return theAppProxy._createObject<ICompositor, Compositor>(m_pProxy->GetCompositor());
	}

	Form^ ChromeWebPage::CreateForm(String^ strFormKey)
	{
		if (m_pChromeWebPage)
		{
			IDispatch* pFormDisp = nullptr;
			pFormDisp = theApp.m_pTangramImpl->m_pCLRProxy->CreateWinForm(m_hWnd, STRING2BSTR(strFormKey));
			return (Form^)Marshal::GetObjectForIUnknown((IntPtr)pFormDisp);
		}
		return nullptr;
	}

	CloudForm::CloudForm(IChromeWebBrowser* pChromeWebBrowser)
	{
		m_hWnd = nullptr;
		m_pChromeWebBrowserHost = pChromeWebBrowser;
	}
}