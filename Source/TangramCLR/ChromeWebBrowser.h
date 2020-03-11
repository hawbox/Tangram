#pragma once

#include "BrowserWndOpenDisposition.h"

using namespace System;
using namespace System::Windows::Forms;

namespace TangramCLR
{
	ref class WndNode;
	ref class Compositor;

	public ref class TangramSession
	{
	public:
		TangramCommon::CTangramSession*	m_pTangramSession;
		TangramSession(CTangramSession* m_pTangramSession);
		Object^ m_pHostObj = nullptr;
		void InsertString(String^ key, String^ value);
		void InsertLong(String^ key, long value);
		void InsertInt64(String^ key, __int64 value);
		void InsertFloat(String^ key, float value);
		String^ GetString(String^ key);
		long GetLong(String^ key);
		float GetFloat(String^ key);
		__int64 GetInt64(String^ key);
		void SendMessage();
	};

	public ref class ChromeWebBrowser
	{
	public:
		IChromeWebBrowser*				m_pChromeWebBrowserHost;
		ChromeWebBrowser(IChromeWebBrowser* pChromeWebBrowser);
		void AddURLs(String^ urls);
		void OpenURL(String^ url, Disposition disposition, String^ key, String^ xml);
	};

	public ref class ChromeWebPage : public IWin32Window
	{
	public:
		HWND							m_hWnd;
		IChromeWebPage	*				m_pChromeWebPage;
		CChromeRenderFrameHostProxy*	m_pProxy;
		ChromeWebPage(IChromeWebPage* m_pChromeWebPage);

		property IntPtr Handle
		{
			virtual IntPtr get();
		}

		property WndNode^ ParentNode
		{
			WndNode^ get();
		}

		property Compositor^ HostCompositor
		{
			Compositor^ get();
		}

		Form^ CreateForm(String^ strFormKey);
	};

	public ref class CloudForm
	{
	public:
		HWND							m_hWnd;
		IChromeWebBrowser*				m_pChromeWebBrowserHost;
		CloudForm(IChromeWebBrowser* pChromeWebBrowser);
	};
}