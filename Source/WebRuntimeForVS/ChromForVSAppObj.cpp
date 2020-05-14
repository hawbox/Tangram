// ChromForVSAppObj.cpp : Implementation of CChromForVSAppObj

#include "stdafx.h"
#include "WebRuntimeForVS.h"
#include "ChromForVSAppObj.h"


// CChromForVSAppObj
HRESULT CChromForVSAppObj::GetCreatingBrowserWnd(LONGLONG* retHandle)
{
	*retHandle = (__int64)m_hCreatingWnd;
	return S_OK;
}

HRESULT CChromForVSAppObj::CreateBrowser(ULONGLONG hParentWnd, BSTR bstrUrls, IChromeWebBrowser** ppRet)
{
	HWND hPWnd = (HWND)hParentWnd;
	CString strUrls = OLE2T(bstrUrls);
	if (theApp.m_pTangramImpl->m_pBrowserFactory)
	{
		strUrls += _T("|");
		strUrls.Replace(_T("||"), _T("|"));
		m_hCreatingWnd = theApp.m_pTangramImpl->m_pBrowserFactory->CreateBrowser(hPWnd, strUrls);
		*ppRet = (IChromeWebBrowser*)::SendMessage(m_hCreatingWnd, WM_TANGRAMMSG, 20190527, 0);
		//auto it = theAppProxy.m_mapChromeWebBrowser.find(pBrowser);
		//if (it != theAppProxy.m_mapChromeWebBrowser.end())
		//	return it->second;
		//else
		//	return gcnew ChromeWebBrowser(pBrowser);
	}
	return S_OK;
}
